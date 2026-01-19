/**
 * @file
 * @author Ceyhun Şen
 * @brief Unit tests for clock module.
 */

// SPDX-FileCopyrightText: 2026 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include "hal_clock.h"
#include "unity.h"

#include <avr/io.h>
#include <avr/sfr_defs.h>
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

//! Resets CLKPR register if prescaler is initialized.
void *reset_clkpr() {
    while (1) {
        loop_until_bit_is_set(CLKPR, 7);

        // Check if other bits are 0 while enable bit is 1.
        int i, is_set = 0;
        for (i = 0; i < 7; i++) {
            if (bit_is_set(CLKPR, i)) {
                is_set = i + 1;
            }
        }
        if (is_set) {
            continue;
        }

        CLKPR = 0;
    }

    return NULL;
}
void test_change_and_read_clock_prescaler() {
    spawn_watcher_thread(reset_clkpr);

    TEST_ASSERT_EQUAL(hal_clock_change_clock_prescaler(hal_clock_prescaler_1),
                      hal_result_clock_ok);
    TEST_ASSERT_EQUAL(CLKPR, 0b0);
    TEST_ASSERT_EQUAL(hal_clock_get_clock_prescaler(), hal_clock_prescaler_1);

    TEST_ASSERT_EQUAL(hal_clock_change_clock_prescaler(hal_clock_prescaler_2),
                      hal_result_clock_ok);
    TEST_ASSERT_EQUAL(CLKPR, 0b1);
    TEST_ASSERT_EQUAL(hal_clock_get_clock_prescaler(), hal_clock_prescaler_2);

    TEST_ASSERT_EQUAL(hal_clock_change_clock_prescaler(hal_clock_prescaler_4),
                      hal_result_clock_ok);
    TEST_ASSERT_EQUAL(CLKPR, 0b10);
    TEST_ASSERT_EQUAL(hal_clock_get_clock_prescaler(), hal_clock_prescaler_4);

    TEST_ASSERT_EQUAL(hal_clock_change_clock_prescaler(hal_clock_prescaler_8),
                      hal_result_clock_ok);
    TEST_ASSERT_EQUAL(CLKPR, 0b11);
    TEST_ASSERT_EQUAL(hal_clock_get_clock_prescaler(), hal_clock_prescaler_8);

    TEST_ASSERT_EQUAL(hal_clock_change_clock_prescaler(hal_clock_prescaler_16),
                      hal_result_clock_ok);
    TEST_ASSERT_EQUAL(CLKPR, 0b100);
    TEST_ASSERT_EQUAL(hal_clock_get_clock_prescaler(), hal_clock_prescaler_16);

    TEST_ASSERT_EQUAL(hal_clock_change_clock_prescaler(hal_clock_prescaler_32),
                      hal_result_clock_ok);
    TEST_ASSERT_EQUAL(CLKPR, 0b101);
    TEST_ASSERT_EQUAL(hal_clock_get_clock_prescaler(), hal_clock_prescaler_32);

    TEST_ASSERT_EQUAL(hal_clock_change_clock_prescaler(hal_clock_prescaler_64),
                      hal_result_clock_ok);
    TEST_ASSERT_EQUAL(CLKPR, 0b110);
    TEST_ASSERT_EQUAL(hal_clock_get_clock_prescaler(), hal_clock_prescaler_64);

    TEST_ASSERT_EQUAL(hal_clock_change_clock_prescaler(hal_clock_prescaler_128),
                      hal_result_clock_ok);
    TEST_ASSERT_EQUAL(CLKPR, 0b111);
    TEST_ASSERT_EQUAL(hal_clock_get_clock_prescaler(), hal_clock_prescaler_128);

    TEST_ASSERT_EQUAL(hal_clock_change_clock_prescaler(hal_clock_prescaler_256),
                      hal_result_clock_ok);
    TEST_ASSERT_EQUAL(CLKPR, 0b1000);
    TEST_ASSERT_EQUAL(hal_clock_get_clock_prescaler(), hal_clock_prescaler_256);

    // Passing a value bigger should return error and register should stay the
    // same.
    TEST_ASSERT_EQUAL(
        hal_clock_change_clock_prescaler(hal_clock_prescaler_256 + 1),
        hal_result_clock_invalid_prescaler);
    TEST_ASSERT_EQUAL(CLKPR, 0b1000);
    TEST_ASSERT_EQUAL(hal_clock_get_clock_prescaler(), hal_clock_prescaler_256);
}

int main() {
    RUN_TEST(test_read_and_parse_osccal);
    RUN_TEST(test_calibration_struct_size);
    RUN_TEST(test_write_and_read_osccal);
    RUN_TEST(test_change_and_read_clock_prescaler);

    return UnityEnd();
}

void setUp() { reset_registers(); }

void tearDown() { reset_registers(); }
