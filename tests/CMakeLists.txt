# SPDX-FileCopyrightText: 2025 Ceyhun Şen <ceyhuusen@gmail.com>
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.11)

project(tests LANGUAGES C)

set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(MOCK_AVR_SYSTEM_DIR ${TESTS_DIR}/mocks)
set(UNIT_DIR ${TESTS_DIR}/unit)
set(INTEGRATION_DIR ${TESTS_DIR}/integration)
set(UNITY_DIR ${TESTS_DIR}/Unity)

# Specify mock AVR as the overwrite system library. Then, define real library as
# a system library too, to specify missing ones. Please note that these include
# directories are for a limited number of OS'es and your system might need to be
# added to this list.
target_include_directories(atmega328p_hal_driver SYSTEM PUBLIC ${MOCK_AVR_SYSTEM_DIR})
if(UNIX)
    target_include_directories(atmega328p_hal_driver SYSTEM PUBLIC /usr/lib/avr/include)
    target_include_directories(atmega328p_hal_driver SYSTEM PUBLIC /usr/avr/include)
endif()

add_library(mocks ${MOCK_AVR_SYSTEM_DIR}/test_mock_up.c)
target_include_directories(mocks SYSTEM PRIVATE ${MOCK_AVR_SYSTEM_DIR})

# Test framework.
add_subdirectory(${UNITY_DIR})

# Adds a test for given source files.
function(add_test_target test_file)
    get_filename_component(TARGET_NAME ${test_file} NAME_WE)

    add_executable(${TARGET_NAME} ${test_file})

    target_link_libraries(${TARGET_NAME} PRIVATE atmega328p_hal_driver unity mocks)

    add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
endfunction()

# Tests.
add_test_target("${UNIT_DIR}/hal.c")
add_test_target("${UNIT_DIR}/mock.c")

add_test_target("${UNIT_DIR}/clock.c")
add_test_target("${UNIT_DIR}/power.c")
# add_test_target("${UNIT_DIR}/system.c")
# add_test_target("${UNIT_DIR}/io.c")
# add_test_target("${UNIT_DIR}/usart.c")
