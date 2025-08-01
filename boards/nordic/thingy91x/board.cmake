# Copyright (c) 2024 Nordic Semiconductor
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause

if(CONFIG_BOARD_THINGY91X_NRF9151 OR CONFIG_BOARD_THINGY91X_NRF9151_NS)
  board_runner_args(nrfjprog)
  board_runner_args(nrfutil "--nrf-family=NRF91")
  board_runner_args(jlink "--device=nRF9151_xxCA" "--speed=4000")
elseif(CONFIG_BOARD_THINGY91X_NRF5340_CPUAPP OR CONFIG_BOARD_THINGY91X_NRF5340_CPUAPP_NS)
  board_runner_args(nrfjprog)
  board_runner_args(nrfutil "--nrf-family=NRF53")
  board_runner_args(jlink "--device=nrf5340_xxaa_app" "--speed=4000")
elseif(CONFIG_BOARD_THINGY91X_NRF5340_CPUNET)
  board_runner_args(nrfjprog)
  board_runner_args(nrfutil "--nrf-family=NRF53")
  board_runner_args(jlink "--device=nrf5340_xxaa_net" "--speed=4000")
endif()

include(${ZEPHYR_BASE}/boards/common/nrfutil.board.cmake)
include(${ZEPHYR_BASE}/boards/common/nrfjprog.board.cmake)
include(${ZEPHYR_BASE}/boards/common/jlink.board.cmake)
