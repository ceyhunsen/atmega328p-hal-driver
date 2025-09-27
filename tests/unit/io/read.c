/**
 * @file
 * @author Ceyhun Şen
 * @brief Unit tests for read operations in GPIO module.
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
