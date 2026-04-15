#
# Copyright (c) 2026 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(smp_svr)

set(smp_srv_dir ${ZEPHYR_BASE}/samples/subsys/mgmt/mcumgr/smp_svr)

target_sources(app PRIVATE ${smp_srv_dir}/src/main.c)
target_sources_ifdef(CONFIG_MCUMGR_TRANSPORT_BT app PRIVATE ${smp_srv_dir}/src/bluetooth.c)
