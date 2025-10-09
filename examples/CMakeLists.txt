# SPDX-FileCopyrightText: 2025 Ceyhun Şen <ceyhuusen@gmail.com>
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.11)

add_executable(power_example power.c)
target_link_libraries(power_example PRIVATE atmega328p_hal_driver)

add_executable(system_example system.c)
target_link_libraries(system_example PRIVATE atmega328p_hal_driver)
