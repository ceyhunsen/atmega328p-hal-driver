# SPDX-FileCopyrightText: 2025 Ceyhun Şen <ceyhuusen@gmail.com>
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.11)
project(atmega328p_hal_driver VERSION 0.4.0 LANGUAGES C)

add_library(
  atmega328p_hal_driver
  src/hal_clock.c
  src/hal_power.c
  src/hal_power_extra.c
  src/hal_system.c
  src/hal_io.c
)
target_include_directories(atmega328p_hal_driver PUBLIC include)
target_compile_definitions(atmega328p_hal_driver PUBLIC __AVR_ATmega328P__)

set_property(TARGET atmega328p_hal_driver PROPERTY C_STANDARD 99)

# Optional examples.
option(BUILD_EXAMPLES "Build example programs" OFF)
if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

# Unit and integration tests.
option(BUILD_TESTING "Build tests" OFF)
if(BUILD_TESTING)
  include(CTest)
  enable_testing()

  add_subdirectory(tests)
endif()
