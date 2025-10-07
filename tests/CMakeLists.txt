cmake_minimum_required(VERSION 3.11)

project(Tests LANGUAGES C)

include(CTest)
enable_testing()

set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(MOCK_AVR_SYSTEM_DIR ${TESTS_DIR}/mocks)
set(UNIT_DIR ${TESTS_DIR}/unit)
set(INTEGRATION_DIR ${TESTS_DIR}/integration)

# Specify mock AVR as the overwrite system library. Then, define real library as
# a system library too, to specify missing ones. Please note that these include
# directories are for a limited number of OS'es and your system might need to be
# added to this list.
target_include_directories(atmega328p_hal_driver SYSTEM PUBLIC ${MOCK_AVR_SYSTEM_DIR})
target_include_directories(atmega328p_hal_driver SYSTEM PUBLIC /usr/lib/avr/include)
target_include_directories(atmega328p_hal_driver SYSTEM PUBLIC /usr/avr/include)

# Test framework.
# TODO: fetch this dynamically?
add_subdirectory(Unity)

# Helper to add test targets.
function(add_test_target target_name srcs src_includes)
    add_executable(${target_name} ${srcs})

    target_include_directories(${target_name}
        PRIVATE
            ${src_includes}
        SYSTEM PUBLIC
            ${MOCK_AVR_SYSTEM_DIR}
    )
    target_link_libraries(${target_name} PRIVATE hal_driver_mock)

    add_test(NAME ${target_name} COMMAND ${target_name})
endfunction()

# Tests.
add_test_target(
    "test_hal"
    "${UNIT_DIR}/hal/hal.c"
    ${UNIT_DIR}/hal/
)
