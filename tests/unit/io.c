/**
 * @file
 * @author Ceyhun Şen
 * @brief Unit tests for GPIO module.
 */

/*
 * MIT License
 *
 * Copyright (c) 2023 Ceyhun Şen
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * */

#include "hal_io.h"
#include "unity.h"

#include <avr/io.h>
#include <stdint.h>
#include <test_mock_up.h>

/**
 * Tests setting GPIO direction to output, for port b while setting one port
 * at a time.
 */
void test_direction_output_b_single() {
    enum io_result result;
    struct io_pin io_pin;
    struct io_pin_configuration configuration;
    uint8_t i;

    for (i = 0; i < 8; i++) {
        configuration.direction = io_direction_output;
        io_pin.port = io_port_b;
        io_pin.pin = i;
        result = io_configure(io_pin, configuration);

        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(1 << i, DDRB);

        reset_registers();
    }
}

/**
 * Tests setting GPIO direction to output, for port b while setting ports
 * sequentially.
 */
void test_direction_output_b_multi() {
    enum io_result result;
    struct io_pin io_pin;
    struct io_pin_configuration configuration;
    uint8_t i, register_value;

    register_value = 0;

    for (i = 0; i < 8; i++) {
        configuration.direction = io_direction_output;
        io_pin.port = io_port_b;
        io_pin.pin = i;
        result = io_configure(io_pin, configuration);

        // Every iteration, pin i should be set to ouput.
        register_value |= 1 << i;

        TEST_ASSERT_EQUAL(io_success, result);
        TEST_ASSERT_EQUAL(register_value, DDRB);
    }
}

/**
 * Tests setting GPIO direction to output, for port c while setting one port
 * at a time.
 */
void test_direction_output_c_single() {
    enum io_result result;
    struct io_pin io_pin;
    struct io_pin_configuration configuration;
    uint8_t i;

    for (i = 0; i < 8; i++) {
        configuration.direction = io_direction_output;
        io_pin.port = io_port_c;
        io_pin.pin = i;
        result = io_configure(io_pin, configuration);

        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(1 << i, DDRC);

        reset_registers();
    }
}

/**
 * Tests setting GPIO direction to output, for port c while setting ports
 * sequentially.
 */
void test_direction_output_c_multi() {
    enum io_result result;
    struct io_pin io_pin;
    struct io_pin_configuration configuration;
    uint8_t i, register_value;

    register_value = 0;

    for (i = 0; i < 8; i++) {
        configuration.direction = io_direction_output;
        io_pin.port = io_port_c;
        io_pin.pin = i;
        result = io_configure(io_pin, configuration);

        // Every iteration, pin i should be set to ouput.
        register_value |= 1 << i;

        TEST_ASSERT_EQUAL(io_success, result);
        TEST_ASSERT_EQUAL(register_value, DDRC);
    }
}

/**
 * Tests setting GPIO direction to output, for port d while setting one port
 * at a time.
 */
void test_direction_output_d_single() {
    enum io_result result;
    struct io_pin io_pin;
    struct io_pin_configuration configuration;
    uint8_t i;

    for (i = 0; i < 8; i++) {
        configuration.direction = io_direction_output;
        io_pin.port = io_port_d;
        io_pin.pin = i;
        result = io_configure(io_pin, configuration);

        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(1 << i, DDRD);

        reset_registers();
    }
}

/**
 * Tests setting GPIO direction to output, for port b while setting ports
 * sequentially.
 */
void test_direction_output_d_multi() {
    enum io_result result;
    struct io_pin io_pin;
    struct io_pin_configuration configuration;
    uint8_t i, register_value;

    register_value = 0;

    for (i = 0; i < 8; i++) {
        configuration.direction = io_direction_output;
        io_pin.port = io_port_d;
        io_pin.pin = i;
        result = io_configure(io_pin, configuration);

        // Every iteration, pin i should be set to ouput.
        register_value |= 1 << i;

        TEST_ASSERT_EQUAL(io_success, result);
        TEST_ASSERT_EQUAL(register_value, DDRD);
    }
}

void test_read_b_single() {
    enum io_result result;
    struct io_pin io_pin;
    enum io_pin_state state;
    uint8_t i;

    for (i = 0; i < 8; i++) {
        io_pin.port = io_port_b;
        io_pin.pin = i;

        result = io_read(io_pin, &state);
        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(io_state_low, state);

        PINB = 1 << i;

        result = io_read(io_pin, &state);
        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(io_state_high, state);

        reset_registers();
    }
}

void test_read_b_multi() {
    enum io_result result;
    struct io_pin io_pin;
    enum io_pin_state state;
    uint8_t i;

    for (i = 0; i < 8; i++) {
        io_pin.port = io_port_b;
        io_pin.pin = i;

        result = io_read(io_pin, &state);
        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(io_state_low, state);

        PINB |= 1 << i;

        result = io_read(io_pin, &state);
        TEST_ASSERT_EQUAL(io_success, result);
        TEST_ASSERT_EQUAL(io_state_high, state);
    }
}

void test_read_c_single() {
    enum io_result result;
    struct io_pin io_pin;
    enum io_pin_state state;
    uint8_t i;

    for (i = 0; i < 8; i++) {
        io_pin.port = io_port_c;
        io_pin.pin = i;

        result = io_read(io_pin, &state);
        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(io_state_low, state);

        PINC = 1 << i;

        result = io_read(io_pin, &state);
        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(io_state_high, state);

        reset_registers();
    }
}

void test_read_c_multi() {
    enum io_result result;
    struct io_pin io_pin;
    enum io_pin_state state;
    uint8_t i;

    for (i = 0; i < 8; i++) {
        io_pin.port = io_port_c;
        io_pin.pin = i;

        result = io_read(io_pin, &state);
        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(io_state_low, state);

        PINC |= 1 << i;

        result = io_read(io_pin, &state);
        TEST_ASSERT_EQUAL(io_success, result);
        TEST_ASSERT_EQUAL(io_state_high, state);
    }
}

void test_read_d_single() {
    enum io_result result;
    struct io_pin io_pin;
    enum io_pin_state state;
    uint8_t i;

    for (i = 0; i < 8; i++) {
        io_pin.port = io_port_d;
        io_pin.pin = i;

        result = io_read(io_pin, &state);
        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(io_state_low, state);

        PIND = 1 << i;

        result = io_read(io_pin, &state);
        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(io_state_high, state);

        reset_registers();
    }
}

void test_read_d_multi() {
    enum io_result result;
    struct io_pin io_pin;
    enum io_pin_state state;
    uint8_t i;

    for (i = 0; i < 8; i++) {
        io_pin.port = io_port_d;
        io_pin.pin = i;

        result = io_read(io_pin, &state);
        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(io_state_low, state);

        PIND |= 1 << i;

        result = io_read(io_pin, &state);
        TEST_ASSERT_EQUAL(io_success, result);
        TEST_ASSERT_EQUAL(io_state_high, state);
    }
}

void test_toggle_b_single() {
    enum io_result result;
    struct io_pin io_pin;
    uint8_t i;

    for (i = 0; i < 8; i++) {
        io_pin.port = io_port_b;
        io_pin.pin = i;
        result = io_toggle(io_pin);

        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(1 << i, PINB);

        reset_registers();
    }
}

void test_toggle_b_multi() {
    enum io_result result;
    struct io_pin io_pin;
    uint8_t i, register_value;

    register_value = 0;

    for (i = 0; i < 8; i++) {
        io_pin.port = io_port_b;
        io_pin.pin = i;
        result = io_toggle(io_pin);

        // Every iteration, pin i should be set to ouput.
        register_value |= 1 << i;

        TEST_ASSERT_EQUAL(io_success, result);
        TEST_ASSERT_EQUAL(register_value, PINB);
    }
}

void test_toggle_c_single() {
    enum io_result result;
    struct io_pin io_pin;
    uint8_t i;

    for (i = 0; i < 8; i++) {
        io_pin.port = io_port_c;
        io_pin.pin = i;
        result = io_toggle(io_pin);

        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(1 << i, PINC);

        reset_registers();
    }
}

void test_toggle_c_multi() {
    enum io_result result;
    struct io_pin io_pin;
    uint8_t i, register_value;

    register_value = 0;

    for (i = 0; i < 8; i++) {
        io_pin.port = io_port_c;
        io_pin.pin = i;
        result = io_toggle(io_pin);

        // Every iteration, pin i should be set to ouput.
        register_value |= 1 << i;

        TEST_ASSERT_EQUAL(io_success, result);
        TEST_ASSERT_EQUAL(register_value, PINC);
    }
}

void test_toggle_d_single() {
    enum io_result result;
    struct io_pin io_pin;
    uint8_t i;

    for (i = 0; i < 8; i++) {
        io_pin.port = io_port_d;
        io_pin.pin = i;
        result = io_toggle(io_pin);

        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(1 << i, PIND);

        reset_registers();
    }
}

void test_toggle_d_multi() {
    enum io_result result;
    struct io_pin io_pin;
    uint8_t i, register_value;

    register_value = 0;

    for (i = 0; i < 8; i++) {
        io_pin.port = io_port_d;
        io_pin.pin = i;
        result = io_toggle(io_pin);

        // Every iteration, pin i should be set to ouput.
        register_value |= 1 << i;

        TEST_ASSERT_EQUAL(io_success, result);
        TEST_ASSERT_EQUAL(register_value, PIND);
    }
}

void test_write_b_single() {
    enum io_result result;
    struct io_pin io_pin;
    enum io_pin_state state;
    uint8_t i;

    for (i = 0; i < 8; i++) {
        io_pin.port = io_port_b;
        io_pin.pin = i;

        state = io_state_low;
        result = io_write(io_pin, state);
        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(0 << i, PORTB);

        state = io_state_high;
        result = io_write(io_pin, state);
        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(1 << i, PORTB);

        reset_registers();
    }
}

void test_write_b_multi() {
    enum io_result result;
    struct io_pin io_pin;
    enum io_pin_state state;
    uint8_t i, register_value;

    register_value = 0;

    for (i = 0; i < 8; i++) {
        io_pin.port = io_port_b;
        io_pin.pin = i;

        state = io_state_low;
        result = io_write(io_pin, state);
        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(register_value, PORTB);

        register_value |= 1 << i;

        state = io_state_high;
        result = io_write(io_pin, state);
        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(register_value, PORTB);
        result = io_toggle(io_pin);
    }
}

void test_write_c_single() {
    enum io_result result;
    struct io_pin io_pin;
    enum io_pin_state state;
    uint8_t i;

    for (i = 0; i < 8; i++) {
        io_pin.port = io_port_c;
        io_pin.pin = i;

        state = io_state_low;
        result = io_write(io_pin, state);
        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(0 << i, PORTC);

        state = io_state_high;
        result = io_write(io_pin, state);
        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(1 << i, PORTC);

        reset_registers();
    }
}

void test_write_c_multi() {
    enum io_result result;
    struct io_pin io_pin;
    enum io_pin_state state;
    uint8_t i, register_value;

    register_value = 0;

    for (i = 0; i < 8; i++) {
        io_pin.port = io_port_c;
        io_pin.pin = i;

        state = io_state_low;
        result = io_write(io_pin, state);
        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(register_value, PORTC);

        register_value |= 1 << i;

        state = io_state_high;
        result = io_write(io_pin, state);
        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(register_value, PORTC);
        result = io_toggle(io_pin);
    }
}

void test_write_d_single() {
    enum io_result result;
    struct io_pin io_pin;
    enum io_pin_state state;
    uint8_t i;

    for (i = 0; i < 8; i++) {
        io_pin.port = io_port_d;
        io_pin.pin = i;

        state = io_state_low;
        result = io_write(io_pin, state);
        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(0 << i, PORTD);

        state = io_state_high;
        result = io_write(io_pin, state);
        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(1 << i, PORTD);

        reset_registers();
    }
}

void test_write_d_multi() {
    enum io_result result;
    struct io_pin io_pin;
    enum io_pin_state state;
    uint8_t i, register_value;

    register_value = 0;

    for (i = 0; i < 8; i++) {
        io_pin.port = io_port_d;
        io_pin.pin = i;

        state = io_state_low;
        result = io_write(io_pin, state);
        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(register_value, PORTD);

        register_value |= 1 << i;

        state = io_state_high;
        result = io_write(io_pin, state);
        TEST_ASSERT_EQUAL(result, io_success);
        TEST_ASSERT_EQUAL(register_value, PORTD);
        result = io_toggle(io_pin);
    }
}

int main() {
    RUN_TEST(test_direction_output_b_single);
    RUN_TEST(test_direction_output_b_multi);
    RUN_TEST(test_direction_output_c_single);
    RUN_TEST(test_direction_output_c_multi);
    RUN_TEST(test_direction_output_d_single);
    RUN_TEST(test_direction_output_d_multi);

    RUN_TEST(test_toggle_b_single);
    RUN_TEST(test_toggle_b_multi);
    RUN_TEST(test_toggle_c_single);
    RUN_TEST(test_toggle_c_multi);
    RUN_TEST(test_toggle_d_single);
    RUN_TEST(test_toggle_d_multi);

    RUN_TEST(test_read_b_single);
    RUN_TEST(test_read_b_multi);
    RUN_TEST(test_read_c_single);
    RUN_TEST(test_read_c_multi);
    RUN_TEST(test_read_d_single);
    RUN_TEST(test_read_d_multi);

    RUN_TEST(test_write_b_single);
    RUN_TEST(test_write_b_multi);
    RUN_TEST(test_write_c_single);
    RUN_TEST(test_write_c_multi);
    RUN_TEST(test_write_d_single);
    RUN_TEST(test_write_d_multi);

    return UnityEnd();
}

void setUp() { reset_registers(); }

void tearDown() { reset_registers(); }
