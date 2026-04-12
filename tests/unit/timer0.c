/**
 * @file
 * @author Ceyhun Şen
 * @brief Unit tests for timer0 module.
 */

// SPDX-FileCopyrightText: 2026 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include "hal_internals.h"
#include "hal_timer0.h"

#include "test_mock_up.h"

#include "unity.h"

#include <avr/io.h>

void test_set_output_compare_mode() {
    enum hal_timer0_output_compare_mode mode;

    mode = hal_timer0_compare_output_mode_set + 1;
    TEST_ASSERT_EQUAL(hal_timer0_set_output_compare_mode(mode),
                      hal_result_timer0_invalid_output_compare_mode);
    mode = hal_timer0_compare_output_mode_normal - 1;
    TEST_ASSERT_EQUAL(hal_timer0_set_output_compare_mode(mode),
                      hal_result_timer0_invalid_output_compare_mode);

    mode = hal_timer0_compare_output_mode_normal;
    TEST_ASSERT_EQUAL(hal_timer0_set_output_compare_mode(mode),
                      hal_result_timer0_ok);
}

int main() {
    RUN_TEST(test_set_output_compare_mode);

    return UnityEnd();
}

void setUp() { reset_registers(); }

void tearDown() { reset_registers(); }
