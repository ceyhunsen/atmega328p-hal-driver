/**
 * @file
 * @author Ceyhun Şen
 * @brief Unit tests for GPIO module.
 */

// SPDX-FileCopyrightText: 2025 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include "hal_io.h"
#include "unity.h"

#include <avr/io.h>
#include <test_mock_up.h>

#include <stdint.h>

void test_errors() {
    enum hal_result_io result;
    struct hal_io_pin io_pin;
    struct hal_io_pin_configuration configuration;
    enum hal_io_pin_state state;

    // Set valid values first.
    io_pin.pin = 0;
    io_pin.port = hal_io_port_b;
    configuration.direction = hal_io_direction_input;
    configuration.is_pull_up = 0;

    result = hal_io_configure(io_pin, configuration);
    TEST_ASSERT_EQUAL(hal_result_io_ok, result);

    io_pin.pin = 9;
    result = hal_io_configure(io_pin, configuration);
    TEST_ASSERT_EQUAL(hal_result_io_error_invalid_pin, result);

    io_pin.pin = 0;
    io_pin.port = hal_io_port_d + 1;
    result = hal_io_configure(io_pin, configuration);
    TEST_ASSERT_EQUAL(hal_result_io_error_invalid_port, result);

    io_pin.port = hal_io_port_d;
    configuration.direction = hal_io_direction_input + 1;
    result = hal_io_configure(io_pin, configuration);
    TEST_ASSERT_EQUAL(hal_result_io_error_invalid_direction, result);

    state = hal_io_state_high;
    result = hal_io_write(io_pin, state);
    TEST_ASSERT_EQUAL(hal_result_io_ok, result);

    state = hal_io_state_high + 1;
    result = hal_io_write(io_pin, state);
    TEST_ASSERT_EQUAL(hal_result_io_error_invalid_state, result);
}

void test_direction_output_single() {
    enum hal_result_io result;
    struct hal_io_pin io_pin;
    struct hal_io_pin_configuration configuration;
    enum hal_io_port port;
    uint8_t i;

    for (port = hal_io_port_b; port <= hal_io_port_d; port++) {
        for (i = 0; i < 8; i++) {
            configuration.direction = hal_io_direction_output;
            io_pin.port = port;
            io_pin.pin = i;

            result = hal_io_configure(io_pin, configuration);

            TEST_ASSERT_EQUAL(hal_result_io_ok, result);
            switch (port) {
            default:
            case hal_io_port_b:
                TEST_ASSERT_EQUAL(1 << i, DDRB);
                break;
            case hal_io_port_c:
                TEST_ASSERT_EQUAL(1 << i, DDRC);
                break;
            case hal_io_port_d:
                TEST_ASSERT_EQUAL(1 << i, DDRD);
                break;
            }

            reset_registers();
        }
    }
}

void test_direction_output_multi() {
    enum hal_result_io result;
    struct hal_io_pin io_pin;
    struct hal_io_pin_configuration configuration;
    enum hal_io_port port;
    uint8_t i, register_value;

    for (port = hal_io_port_b; port <= hal_io_port_d; port++) {
        register_value = 0;

        for (i = 0; i < 8; i++) {
            configuration.direction = hal_io_direction_output;
            io_pin.port = port;
            io_pin.pin = i;

            result = hal_io_configure(io_pin, configuration);

            // Every iteration, pin i should be set to ouput.
            register_value |= 1 << i;

            TEST_ASSERT_EQUAL(hal_result_io_ok, result);
            switch (port) {
            default:
            case hal_io_port_b:
                TEST_ASSERT_EQUAL(register_value, DDRB);
                break;
            case hal_io_port_c:
                TEST_ASSERT_EQUAL(register_value, DDRC);
                break;
            case hal_io_port_d:
                TEST_ASSERT_EQUAL(register_value, DDRD);
                break;
            }
        }
    }
}

void test_read_single() {
    enum hal_result_io result;
    struct hal_io_pin io_pin;
    enum hal_io_pin_state state;
    enum hal_io_port port;
    uint8_t i;

    for (port = hal_io_port_b; port <= hal_io_port_d; port++) {
        for (i = 0; i < 8; i++) {
            io_pin.port = port;
            io_pin.pin = i;

            result = hal_io_read(io_pin, &state);

            TEST_ASSERT_EQUAL(hal_result_io_ok, result);
            TEST_ASSERT_EQUAL(hal_io_state_low, state);
            switch (port) {
            default:
            case hal_io_port_b:
                PINB = 1 << i;
                break;
            case hal_io_port_c:
                PINC = 1 << i;
                break;
            case hal_io_port_d:
                PIND = 1 << i;
                break;
            }

            result = hal_io_read(io_pin, &state);
            TEST_ASSERT_EQUAL(hal_result_io_ok, result);
            TEST_ASSERT_EQUAL(hal_io_state_high, state);
        }
    }
}

void test_read_multi() {
    enum hal_result_io result;
    struct hal_io_pin io_pin;
    enum hal_io_pin_state state;
    enum hal_io_port port;
    uint8_t i;

    for (port = hal_io_port_b; port <= hal_io_port_d; port++) {
        for (i = 0; i < 8; i++) {
            io_pin.port = port;
            io_pin.pin = i;

            result = hal_io_read(io_pin, &state);

            TEST_ASSERT_EQUAL(hal_result_io_ok, result);
            TEST_ASSERT_EQUAL(hal_io_state_low, state);
            switch (port) {
            default:
            case hal_io_port_b:
                PINB = 1 << i;
                break;
            case hal_io_port_c:
                PINC = 1 << i;
                break;
            case hal_io_port_d:
                PIND = 1 << i;
                break;
            }

            result = hal_io_read(io_pin, &state);

            TEST_ASSERT_EQUAL(hal_result_io_ok, result);
            TEST_ASSERT_EQUAL(hal_io_state_high, state);
        }
    }
}

void test_toggle_single() {
    enum hal_result_io result;
    struct hal_io_pin io_pin;
    enum hal_io_port port;
    uint8_t i;

    for (port = hal_io_port_b; port <= hal_io_port_d; port++) {
        for (i = 0; i < 8; i++) {
            io_pin.port = port;
            io_pin.pin = i;

            result = hal_io_toggle(io_pin);

            TEST_ASSERT_EQUAL(hal_result_io_ok, result);
            switch (port) {
            default:
            case hal_io_port_b:
                TEST_ASSERT_EQUAL(1 << i, PINB);
                break;
            case hal_io_port_c:
                TEST_ASSERT_EQUAL(1 << i, PINC);
                break;
            case hal_io_port_d:
                TEST_ASSERT_EQUAL(1 << i, PIND);
                break;
            }

            reset_registers();
        }
    }
}

void test_toggle_multi() {
    enum hal_result_io result;
    struct hal_io_pin io_pin;
    enum hal_io_port port;
    uint8_t i, register_value;

    for (port = hal_io_port_b; port <= hal_io_port_d; port++) {
        register_value = 0;
        reset_registers();

        for (i = 0; i < 8; i++) {
            io_pin.port = port;
            io_pin.pin = i;

            result = hal_io_toggle(io_pin);

            // Every iteration, pin i should be set to ouput.
            register_value |= 1 << i;
            TEST_ASSERT_EQUAL(hal_result_io_ok, result);
            switch (port) {
            default:
            case hal_io_port_b:
                TEST_ASSERT_EQUAL(register_value, PINB);
                break;
            case hal_io_port_c:
                TEST_ASSERT_EQUAL(register_value, PINC);
                break;
            case hal_io_port_d:
                TEST_ASSERT_EQUAL(register_value, PIND);
                break;
            }
        }
    }
}

void test_write_single() {
    enum hal_result_io result;
    struct hal_io_pin io_pin;
    enum hal_io_pin_state state;
    enum hal_io_port port;
    uint8_t i;

    for (port = hal_io_port_b; port <= hal_io_port_d; port++) {
        for (i = 0; i < 8; i++) {
            io_pin.port = port;
            io_pin.pin = i;

            state = hal_io_state_low;
            result = hal_io_write(io_pin, state);

            TEST_ASSERT_EQUAL(hal_result_io_ok, result);
            switch (port) {
            default:
            case hal_io_port_b:
                TEST_ASSERT_EQUAL(0 << i, PORTB);
                break;
            case hal_io_port_c:
                TEST_ASSERT_EQUAL(0 << i, PORTC);
                break;
            case hal_io_port_d:
                TEST_ASSERT_EQUAL(0 << i, PORTD);
                break;
            }

            state = hal_io_state_high;
            result = hal_io_write(io_pin, state);

            TEST_ASSERT_EQUAL(hal_result_io_ok, result);
            switch (port) {
            default:
            case hal_io_port_b:
                TEST_ASSERT_EQUAL(1 << i, PORTB);
                break;
            case hal_io_port_c:
                TEST_ASSERT_EQUAL(1 << i, PORTC);
                break;
            case hal_io_port_d:
                TEST_ASSERT_EQUAL(1 << i, PORTD);
                break;
            }

            reset_registers();
        }
    }
}

void test_write_multi() {
    enum hal_result_io result;
    struct hal_io_pin io_pin;
    enum hal_io_pin_state state;
    enum hal_io_port port;
    uint8_t i, register_value;

    for (port = hal_io_port_b; port <= hal_io_port_d; port++) {
        register_value = 0;

        for (i = 0; i < 8; i++) {
            io_pin.port = port;
            io_pin.pin = i;

            state = hal_io_state_low;
            result = hal_io_write(io_pin, state);

            TEST_ASSERT_EQUAL(hal_result_io_ok, result);
            switch (port) {
            default:
            case hal_io_port_b:
                TEST_ASSERT_EQUAL(register_value, PORTB);
                break;
            case hal_io_port_c:
                TEST_ASSERT_EQUAL(register_value, PORTC);
                break;
            case hal_io_port_d:
                TEST_ASSERT_EQUAL(register_value, PORTD);
                break;
            }

            state = hal_io_state_high;
            result = hal_io_write(io_pin, state);

            register_value |= 1 << i;
            TEST_ASSERT_EQUAL(hal_result_io_ok, result);
            switch (port) {
            default:
            case hal_io_port_b:
                TEST_ASSERT_EQUAL(register_value, PORTB);
                break;
            case hal_io_port_c:
                TEST_ASSERT_EQUAL(register_value, PORTC);
                break;
            case hal_io_port_d:
                TEST_ASSERT_EQUAL(register_value, PORTD);
                break;
            }

            result = hal_io_toggle(io_pin);
            TEST_ASSERT_EQUAL(hal_result_io_ok, result);
        }
    }
}

int main() {
    RUN_TEST(test_errors);

    RUN_TEST(test_direction_output_single);
    RUN_TEST(test_direction_output_multi);

    RUN_TEST(test_toggle_single);
    RUN_TEST(test_toggle_multi);

    RUN_TEST(test_read_single);
    RUN_TEST(test_read_multi);

    RUN_TEST(test_write_single);
    RUN_TEST(test_write_multi);

    return UnityEnd();
}

void setUp() { reset_registers(); }

void tearDown() { reset_registers(); }
