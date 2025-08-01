# Copyright (c) 2025 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause

'''Runner for flashing with nrfutil.'''

import os
import sys

FILE_PATH = os.path.dirname(os.path.abspath(__file__))
sys.path.append(f"{FILE_PATH}")

import json
import subprocess
from pathlib import Path

from runners.core import _DRY_RUN
from nrf_common_next import NrfBinaryRunnerNext


class NrfUtilBinaryRunner(NrfBinaryRunnerNext):
    '''Runner front-end for nrfutil.'''

    def __init__(self, cfg, family, softreset, pinreset, dev_id, erase=False,
                 erase_mode=None, ext_erase_mode=None, reset=True, tool_opt=None,
                 force=False, recover=False, suit_starter=False,
                 ext_mem_config_file=None):

        super().__init__(cfg, family, softreset, pinreset, dev_id, erase,
                         erase_mode, ext_erase_mode, reset, tool_opt, force,
                         recover)

        self.suit_starter = suit_starter
        self.ext_mem_config_file = ext_mem_config_file

        self._ops = []
        self._op_id = 1

    @classmethod
    def name(cls):
        return 'nrfutil_next'

    @classmethod
    def capabilities(cls):
        return NrfBinaryRunnerNext._capabilities(mult_dev_ids=True)

    @classmethod
    def dev_id_help(cls) -> str:
        return NrfBinaryRunnerNext._dev_id_help() + \
               '''.\n This option can be specified multiple times'''

    @classmethod
    def tool_opt_help(cls) -> str:
        return 'Additional options for nrfutil, e.g. "--log-level"'

    @classmethod
    def do_create(cls, cfg, args):
        return NrfUtilBinaryRunner(cfg, args.nrf_family, args.softreset,
                                   args.pinreset, args.dev_id, erase=args.erase,
                                   erase_mode=args.erase_mode,
                                   ext_erase_mode=args.ext_erase_mode,
                                   reset=args.reset, tool_opt=args.tool_opt,
                                   force=args.force, recover=args.recover,
                                   suit_starter=args.suit_manifest_starter,
                                   ext_mem_config_file=args.ext_mem_config_file)

    @classmethod
    def do_add_parser(cls, parser):
        super().do_add_parser(parser)
        parser.add_argument('--suit-manifest-starter', required=False,
                            action='store_true',
                            help='Use the SUIT manifest starter file')
        parser.add_argument('--ext-mem-config-file', required=False,
                            dest='ext_mem_config_file',
                            help='path to an JSON file with external memory configuration')

    def _exec(self, args):
        jout_all = []

        cmd = ['nrfutil', '--json', 'device'] + args
        self._log_cmd(cmd)

        if _DRY_RUN:
            return {}

        with subprocess.Popen(cmd, stdout=subprocess.PIPE) as p:
            for line in iter(p.stdout.readline, b''):
                # https://github.com/ndjson/ndjson-spec
                jout = json.loads(line.decode(sys.getdefaultencoding()))
                jout_all.append(jout)

                if 'x-execute-batch' in args:
                    if jout['type'] == 'batch_update':
                        pld = jout['data']['data']
                        if (
                            pld['type'] == 'task_progress' and
                            pld['data']['progress']['progressPercentage'] == 0
                        ):
                            self.logger.info(pld['data']['progress']['description'])
                    elif jout['type'] == 'batch_end' and jout['data']['error']:
                        raise subprocess.CalledProcessError(
                            jout['data']['error']['code'], cmd
                        )
        if p.returncode != 0:
            raise subprocess.CalledProcessError(p.returncode, cmd)

        return jout_all

    def do_get_boards(self):
        out = self._exec(['list'])
        devs = []
        for o in out:
            if o['type'] == 'task_end':
                devs = o['data']['data']['devices']
        snrs = [dev['serialNumber'] for dev in devs if dev['traits']['jlink']]

        self.logger.debug(f'Found boards: {snrs}')
        return snrs

    def do_require(self):
        self.require('nrfutil')

    def _insert_op(self, op):
        op['operationId'] = f'{self._op_id}'
        self._op_id += 1
        self._ops.append(op)

    def _format_dev_ids(self):
        if isinstance(self.dev_id, list):
            return ','.join(self.dev_id)
        else:
            return self.dev_id

    def _append_batch(self, op, json_file):
        _op = op['operation']
        op_type = _op['type']

        cmd = [f'{op_type}']

        if op_type == 'program':
            cmd += ['--firmware', _op['firmware']['file']]
            opts = _op['options']
            # populate the options
            cmd.append('--options')
            cli_opts = f"chip_erase_mode={opts['chip_erase_mode']}"
            if opts.get('ext_mem_erase_mode'):
                cli_opts += f",ext_mem_erase_mode={opts['ext_mem_erase_mode']}"
            if opts.get('verify'):
                cli_opts += f",verify={opts['verify']}"
            cmd.append(cli_opts)
        elif op_type == 'reset':
            cmd += ['--reset-kind', _op['kind']]
        elif op_type == 'erase':
            cmd.append(f'--{_op["kind"]}')
        elif op_type == 'x-provision-keys':
            cmd += ['--key-file', _op['keyfile']]

        cmd += ['--core', op['core']] if op.get('core') else []
        cmd += ['--x-family', f'{self.family}']
        cmd += ['--x-append-batch', f'{json_file}']
        self._exec(cmd)

    def _exec_batch(self):
        # Use x-append-batch to get the JSON from nrfutil itself
        json_file = Path(self.hex_).parent / 'generated_nrfutil_batch.json'
        json_file.unlink(missing_ok=True)
        for op in self._ops:
            self._append_batch(op, json_file)

        # reset first in case an exception is thrown
        self._ops = []
        self._op_id = 1
        self.logger.debug(f'Executing batch in: {json_file}')
        precmd = []
        if self.ext_mem_config_file:
            # This needs to be prepended, as it's a global option
            precmd = ['--x-ext-mem-config-file', self.ext_mem_config_file]

        self._exec(precmd + ['x-execute-batch', '--batch-path', f'{json_file}',
                             '--serial-number', self._format_dev_ids()])

    def do_exec_op(self, op, force=False):
        self.logger.debug(f'Executing op: {op}')
        if force:
            if len(self._ops) != 0:
                raise RuntimeError(f'Forced exec with {len(self._ops)} ops')
            self._insert_op(op)
            self._exec_batch()
            return True
        # Defer by default
        return False

    def flush_ops(self, force=True):
        if not force:
            return
        while self.ops:
            self._insert_op(self.ops.popleft())
        self._exec_batch()
