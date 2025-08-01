.. _ug_nrf54h20_logging:

nRF54H20 logging
################
.. contents::
   :local:
   :depth: 2

To read logs on the nRF54H20 DK, you can use the following methods:

* A direct UART connection to a specific core.
* Local domain logging with System Trace Macrocell (STM).
  STM has two modes:

  * Standalone logging
  * Assisted multicore logging

For general information on how logging works in the |NCS|, consult the :ref:`ug_logging` and :ref:`zephyr:logging_api` documentation pages.



nRF54H20 logging using a direct UART connection
***********************************************

Similarly to other SoCs from Nordic Semiconductor, to use a UART connection for reading logs, follow the :ref:`ug_logging_backends_uart` logging guide in the application development section.

nRF54H20 logging using System Trace Macrocell (STM)
***************************************************

nRF54H20 domains include ARM Coresight System Trace Macrocell (STM) hardware, which collects trace data from multiple domains using standalone or assisted multicore logging.
The STM writes trace data generated by the domains using memory-mapped registers.
The STM multiplexes trace protocol data, formatted according to the MIPI System Trace Protocol (STP) v2, and sends it to a single output, like a UART.
This approach has a minimal cost on performance and code size, allowing for a non-intrusive collection of system debug-and-trace information.

The STM implements a frontend of the Zephyr logging subsystem, allowing you to use the standard Zephyr logging API.
For more information on STM, see :ref:`zephyr:logging_cs_stm`.

.. note::
   The STM logging feature for the nRF54H20 SoC underwent testing with the J-Trace PRO V2 Cortex-M, using firmware compiled on ``Mar 28 2024 15:14:04``.
   Using this feature also requires ``nrfutil-trace`` version 2.10.0 or later.

Embedded Trace Router (ETR)
===========================

The Embedded Trace Router (ETR) is a hardware feature that provides a circular buffer in RAM for trace data.
For more information on ETR, see :ref:`zephyr:logging_cs_stm`.

When using ETR on the nRF54H20 SoC, one of the cores acts as a *proxy* to manage the trace data.

.. note::
   Currently, only the Application core can act as a proxy.

The proxy core is responsible for handling the data from the ETR and outputting it through the desired transport mechanism (like UART or USB).
The proxy core approach allows for on-chip data processing, offering more flexibility than the Trace Port Interface Unit (TPIU).
However, the limited size of the ETR buffer poses a risk of data loss if not handled appropriately.

Standalone logging
==================

The standalone logging mode with STM on the nRF54H20 SoC works as follows:

1. All domains write the raw encoded log data to their own STM peripheral called the STM Extended Stimulus Port (STMESP).
#. The STMESP generates a data stream based on the register writes.
#. The STM multiplexes the data stream with streams from other domains, and it places them in the single memory buffer provided by the ETR.
#. The application core, acting as the ETR-designated proxy, reads the buffer and decodes the raw encoded log data.
#. The SDFW outputs the logging data in a human-readable format over UART.

Standalone logging leverages the frontend API of the Zephyr logging subsystem to select the stimulus ports and writes log messages directly to memory-mapped registers.
This method bypasses the need for string formatting functions and peripheral drivers, as the core writes directly to the STM port.

Configuring logging
-------------------

To show the logs for a given domain in the UART output, you must enable the STM for both the application core (as the ETR buffer processing proxy) and that domain's CPU.
To do so, use the :ref:`zephyr:nordic-log-stm` snippet when building the application for the related cores:
For example, the following command uses the snippet when building for the application core::

   west build -b nrf54h20dk/nrf54h20/cpuapp -S nordic-log-stm

All cores must use the same logging configuration.

Reading the logs
----------------

To read the STM log output on the UART, consult the following documentation pages:

* If you want to use the *nRF Serial Terminal* from the |nRFVSC|, see the `nRF Terminal documentation`_ on the `nRF Connect for Visual Studio Code`_ documentation site.
* If you want to use PuTTY, see :ref:`putty`.

.. note::
   To use UART in your application, define the UART node in the devicetree.
   For more details, see :ref:`zephyr:devicetree-intro`.

The following is an example log output::

   [00:00:00.154,790] <inf> app/spsc_pbuf: alloc in 0x2f0df800
   [00:00:00.163,319] <inf> app/spsc_pbuf: alloc 0x2f0df800 wr_idx:20
   [00:00:00.181,112] <inf> app/spsc_pbuf: commit in 0x2f0df800
   [00:00:00.189,090] <inf> app/spsc_pbuf: commit 0x2f0df800, len:20 wr_idx: 44
   [00:00:00.202,577] <inf> rad/icmsg: mbox_callback
   [00:00:00.214,750] <inf> rad/spsc_pbuf: claim 0x2f0df800 rd_idx:20
   [00:00:00.235,823] <inf> rad/spsc_pbuf: free 0x2f0df800 len:20 rd_idx: 44
   [00:00:00.244,507] <inf> rad/spsc_pbuf: read done 0x2f0df800 len:20
   [00:00:00.272,444] <inf> rad/host: ep recv 0x330021f0, len:20
   [00:00:00.283,939] <inf> rad/host: rx:00 exp:00
   [00:00:00.292,200] <inf> rad/icmsg: read 0
   [00:00:05.077,026] <inf> rad/spsc_pbuf: alloc in 0x2f0df000
   [00:00:05.077,068] <inf> rad/spsc_pbuf: alloc 0x2f0df000 wr_idx:44
   [00:00:05.077,098] <inf> rad/spsc_pbuf: commit in 0x2f0df000
   [00:00:05.077,134] <inf> rad/spsc_pbuf: commit 0x2f0df000, len:20 wr_idx

Each log line contains a domain-related or core-related prefix between the log level and the module name, indicating the core that generated the log entry.
The following are the prefixes used to indicate the cores:

.. csv-table:: nRF54H20 log prefixes
   :header: "Core", "Prefix"

   Secure Domain, ``sec``
   Application core, ``app``
   Radio core, ``rad``
   System Controller (SysCtrl), ``sys``
   Fast Lightweight Processor (FLPR), ``flpr``
   Peripheral Processor (PPR), ``ppr``

Assisted multicore logging
==========================

Assisted multicore logging uses dictionary-based logging to send messages without redundant strings to STM.
It is based on the :ref:`zephyr:logging_guide_dictionary` feature of the Zephyr logging API.
For more information on assisted multicore logging, see :ref:`zephyr:logging_cs_stm`.

Configuring logging
-------------------

To show the logs for a given domain in the UART output, you must enable the STM for both the application core (as the ETR buffer processing proxy) and that domain's CPU.
To do so, use the :ref:`zephyr:nordic-log-stm-dict` snippet when building the application for the related cores.
For example, the following command uses the snippet when building for the application core::

   west build -b nrf54h20dk/nrf54h20/cpuapp -S nordic-log-stm-dict

All cores must use the same logging configuration.

After building your application, the build directories for each core (:file:`build/<app_name>/zephyr/`, where ``<app_name>`` is the application name for each core) will contain a dictionary database file named :file:`log_database.json`.
This file is crucial for decoding the logs and updates with every build.

Reading the logs
----------------

To read the dictionary-based STM log output, do the following:

1. Set up the log capture.

   Use the ``nrfutil trace stm`` command to start capturing logs from the device, specifying the database configuration for each domain ID, along with the serial port, baud rate, and output type::

      nrfutil trace stm --database-config <domain_id>:build/<app_name>/zephyr/log_dictionary.json --input-serialport <port> --baudrate 115200 --stdout ascii

   This command contains the following parameters:

   * ``<domain_id>`` is the ID of the domain which the application is running on.
     It should be in decimals, not in hexadecimals.
     When using several domains, use a comma (`,`) to separate each domain in the list.
   * ``<app_name>`` is the application name.
   * ``<port>`` is the serial port used for output.
     |serial_port_number_list|
   * The output can be either the console (``--stdout ascii``) or a file (the :file:`out.txt` file if ``--output-ascii out.txt``).

#. Capture and decode the logs.

   nrfutil will capture the log data from the specified UART port and use the provided dictionary databases to decode the logs into a human-readable format.
   The tool sends the decoded logs to the specified output (either the console or the :file:`out.txt` file in the example).

#. Read the terminal or open the output file to review the decoded log messages.

   The output contains timestamps and the log messages in a human-readable format.

If the log capture fails to find a sync, rerun the capture process.

.. note::
   Decoding artifacts or incorrect timestamps might occur when rerunning the process.

Each log line contains a domain-related or core-related prefix between the log level and the module name, indicating the core that generated the log entry.
The following are the prefixes used to indicate the cores:

.. csv-table:: nRF54H20 log prefixes
   :header: "Core", "Prefix", "ID"

   Secure Domain, ``sec``, 0x21
   Application core, ``app``, 0x22
   Radio core, ``rad``, 0x23
   System Controller (SysCtrl), ``sys``, 0x2c
   Fast Lightweight Processor (FLPR), ``flpr``, 0x2d
   Peripheral Processor (PPR), ``ppr``, 0x2e

For more information on ``nrfutil trace``, see `nrfutil-trace`_.

Additional considerations
-------------------------

When using assisted multicore logging, consider the following:

* Use optimized log macros (having up to 2 word size numeric arguments, like ``LOG_INF("%d %c", (int)x, (char)y)``) to improve the size and speed of logging.
* For memory constrained applications (for example, when running on the PPR or FLPR cores), disable the ``printk()`` function by setting both the :kconfig:option:`CONFIG_PRINTK` and :kconfig:option:`CONFIG_BOOT_BANNER` Kconfig options to ``n`` in your project configuration.
* When working with multiple domains, such as the Secure Domain and Application core, ensure that each database has the correct domain ID prefix.
* The limited size of the RAM buffer storing STM logs may cause some log messages to drop.
