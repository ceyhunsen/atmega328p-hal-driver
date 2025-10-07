cmake_minimum_required(VERSION 3.11)
project(Tests LANGUAGES C)

set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(MOCK_AVR_SYSTEM_DIR ${TESTS_DIR}/mocks)
set(UNIT_DIR ${TESTS_DIR}/unit)
set(INTEGRATION_DIR ${TESTS_DIR}/integration)

add_library(hal_driver_mock INTERFACE)
target_link_libraries(hal_driver_mock INTERFACE atmega328p_hal_driver)
target_include_directories(hal_driver_mock SYSTEM INTERFACE ${MOCK_AVR_SYSTEM_DIR})

enable_testing()

add_subdirectory(Unity)

# Helper to add test targets.
function(add_test_target target_name srcs src_includes)
    message(srcs="${srcs}")
    message(src_includes="${src_includes}")

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

add_test_target(
    "test_hal"
    "${UNIT_DIR}/hal/hal.c"
    ${UNIT_DIR}/hal/
)
