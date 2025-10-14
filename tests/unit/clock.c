/**
 * @file
 * @author Ceyhun Şen
 * @brief Unit tests for clock module.
 */

// SPDX-FileCopyrightText: 2025 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include "hal_clock.h"
#include "unity.h"

#include <avr/io.h>
#include <stdint.h>
#include <test_mock_up.h>

//! \ref hal_clock_oscillator_calibration needs to be 1 byte even after parsing.
void test_calibration_struct_size() {
    TEST_ASSERT_EQUAL(sizeof(struct hal_clock_oscillator_calibration), 1);
}

void test_read_and_parse_osccal() {
    {
        OSCCAL = 0;
        struct hal_clock_oscillator_calibration val =
            hal_clock_read_oscillator_calibration();
        TEST_ASSERT_EQUAL(val.range, 0);
        TEST_ASSERT_EQUAL(val.calibration_value, 0);
    }

    {
        OSCCAL = (uint8_t)0b10000000;
        struct hal_clock_oscillator_calibration val =
            hal_clock_read_oscillator_calibration();
        TEST_ASSERT_EQUAL(val.range, 1);
        TEST_ASSERT_EQUAL(val.calibration_value, 0);
    }

    {
        OSCCAL = (uint8_t)0b01111111;
        struct hal_clock_oscillator_calibration val =
            hal_clock_read_oscillator_calibration();
        TEST_ASSERT_EQUAL(val.range, 0);
        TEST_ASSERT_EQUAL(val.calibration_value, 0b01111111);
    }

    {
        OSCCAL = (uint8_t)0b11111111;
        struct hal_clock_oscillator_calibration val =
            hal_clock_read_oscillator_calibration();
        TEST_ASSERT_EQUAL(val.range, 1);
        TEST_ASSERT_EQUAL(val.calibration_value, 0b01111111);
    }

    {
        OSCCAL = (uint8_t)0b11111011;
        struct hal_clock_oscillator_calibration val =
            hal_clock_read_oscillator_calibration();
        TEST_ASSERT_EQUAL(val.range, 1);
        TEST_ASSERT_EQUAL(val.calibration_value, 0b01111011);
    }
}

void test_write_and_read_osccal() {
    {
        struct hal_clock_oscillator_calibration val = {
            .range = 0,
            .calibration_value = 0,
        };
        hal_clock_write_oscillator_calibration_value(val);
        struct hal_clock_oscillator_calibration read =
            hal_clock_read_oscillator_calibration();
        TEST_ASSERT_EQUAL(val.range, read.range);
        TEST_ASSERT_EQUAL(val.calibration_value, read.calibration_value);
    }

    {
        struct hal_clock_oscillator_calibration val = {
            .range = 1,
            .calibration_value = 0,
        };
        hal_clock_write_oscillator_calibration_value(val);
        struct hal_clock_oscillator_calibration read =
            hal_clock_read_oscillator_calibration();
        TEST_ASSERT_EQUAL(val.range, read.range);
        TEST_ASSERT_EQUAL(val.calibration_value, read.calibration_value);
    }

    {
        struct hal_clock_oscillator_calibration val = {
            .range = 0,
            .calibration_value = 0b01000000,
        };
        hal_clock_write_oscillator_calibration_value(val);
        struct hal_clock_oscillator_calibration read =
            hal_clock_read_oscillator_calibration();
        TEST_ASSERT_EQUAL(val.range, read.range);
        TEST_ASSERT_EQUAL(val.calibration_value, read.calibration_value);
    }

    {
        struct hal_clock_oscillator_calibration val = {
            .range = 1,
            .calibration_value = 0b01000000,
        };
        hal_clock_write_oscillator_calibration_value(val);
        struct hal_clock_oscillator_calibration read =
            hal_clock_read_oscillator_calibration();
        TEST_ASSERT_EQUAL(val.range, read.range);
        TEST_ASSERT_EQUAL(val.calibration_value, read.calibration_value);
    }
}

int main() {
    RUN_TEST(test_read_and_parse_osccal);
    RUN_TEST(test_calibration_struct_size);
    RUN_TEST(test_write_and_read_osccal);

    return UnityEnd();
}

void setUp() { reset_registers(); }

void tearDown() { reset_registers(); }
