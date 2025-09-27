/**
 * @file
 * @author Ceyhun Şen
 * @brief Unit tests for toggle operations in GPIO module.
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
#include "io.h"
#include "unity.h"
#include <avr/io.h>
#include <stdint.h>
#include <test_mock_up.h>

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
