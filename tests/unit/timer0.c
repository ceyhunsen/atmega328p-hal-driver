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

/// @brief Try to change COM0A* bits and check if operation is successful or
/// not.
/// @param mode Mode to be tested
/// @param expected Expected register value
/// @param initial_val Initial value of the register
void set_and_test(enum hal_timer0_output_compare_mode mode, uint8_t expected,
                  uint8_t initial_val) {
    printf("For mode %d, expected value is %d\n", mode, expected);

    TEST_ASSERT_EQUAL(hal_timer0_set_output_compare_mode(mode),
                      hal_result_timer0_ok);

    TEST_ASSERT_EQUAL(TCCR0A >> 6, expected);
    TEST_ASSERT_EQUAL(TCCR0A & initial_val, initial_val);
}
void test_set_output_compare_mode() {
    enum hal_timer0_output_compare_mode mode;

    // Initial value shouldn't be changed, except COM0A* bits.
    uint8_t initial_val = 0b00001010;
    TCCR0A = initial_val;

    // Invalid modes should return error.
    mode = hal_timer0_compare_output_mode_set + 1;
    TEST_ASSERT_EQUAL(hal_timer0_set_output_compare_mode(mode),
                      hal_result_timer0_invalid_output_compare_mode);
    mode = hal_timer0_compare_output_mode_normal - 1;
    TEST_ASSERT_EQUAL(hal_timer0_set_output_compare_mode(mode),
                      hal_result_timer0_invalid_output_compare_mode);

    set_and_test(hal_timer0_compare_output_mode_normal, 0b00, initial_val);
    set_and_test(hal_timer0_compare_output_mode_toggle, 0b01, initial_val);
    set_and_test(hal_timer0_compare_output_mode_clear, 0b10, initial_val);
    set_and_test(hal_timer0_compare_output_mode_set, 0b11, initial_val);
}

int main() {
    RUN_TEST(test_set_output_compare_mode);

    return UnityEnd();
}

void setUp() { reset_registers(); }

void tearDown() { reset_registers(); }
