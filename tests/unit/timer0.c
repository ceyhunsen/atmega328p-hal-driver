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

void basic_set_and_get_timer0_counter() {
    uint8_t val;

    TEST_ASSERT_EQUAL(hal_timer0_get_counter(), 0);

    val = 0x45;
    hal_timer0_set_counter(val);
    TEST_ASSERT_EQUAL(hal_timer0_get_counter(), val);

    val = 0x54;
    hal_timer0_set_counter(val);
    TEST_ASSERT_EQUAL(hal_timer0_get_counter(), val);
}

void set_operation_mode() {
    enum hal_timer0_operation_modes mode;

    mode = hal_timer0_mode_normal - 1;
    TEST_ASSERT_EQUAL(hal_timer0_set_operation_mode(mode),
                      hal_result_timer0_invalid_operation_mode);

    // A reserved value.
    mode = 4;
    TEST_ASSERT_EQUAL(hal_timer0_set_operation_mode(mode),
                      hal_result_timer0_invalid_operation_mode);

    mode = hal_timer0_mode_normal;
    TEST_ASSERT_EQUAL(hal_timer0_set_operation_mode(mode),
                      hal_result_timer0_ok);
    TEST_ASSERT_EQUAL(TCCR0A, 0);
    TEST_ASSERT_EQUAL(TCCR0B, 0);

    mode = hal_timer0_mode_ctc;
    TEST_ASSERT_EQUAL(hal_timer0_set_operation_mode(mode),
                      hal_result_timer0_ok);
    TEST_ASSERT_EQUAL(TCCR0A, 0b10);
    TEST_ASSERT_EQUAL(TCCR0B, 0);

    mode = hal_timer0_mode_fast_pwm;
    TEST_ASSERT_EQUAL(hal_timer0_set_operation_mode(mode),
                      hal_result_timer0_ok);
    TEST_ASSERT_EQUAL(TCCR0A, 0b11);
    TEST_ASSERT_EQUAL(TCCR0B, 0);

    mode = hal_timer0_mode_phase_correct_pwm;
    TEST_ASSERT_EQUAL(hal_timer0_set_operation_mode(mode),
                      hal_result_timer0_ok);
    TEST_ASSERT_EQUAL(TCCR0A, 0b01);
    TEST_ASSERT_EQUAL(TCCR0B, 0);

    mode = hal_timer0_mode_phase_correct_pwm_to_top;
    TEST_ASSERT_EQUAL(hal_timer0_set_operation_mode(mode),
                      hal_result_timer0_ok);
    TEST_ASSERT_EQUAL(TCCR0A, 0b01);
    TEST_ASSERT_EQUAL(TCCR0B, 1 << WGM02);

    mode = hal_timer0_mode_fast_pwm_to_top;
    TEST_ASSERT_EQUAL(hal_timer0_set_operation_mode(mode),
                      hal_result_timer0_ok);
    TEST_ASSERT_EQUAL(TCCR0A, 0b11);
    TEST_ASSERT_EQUAL(TCCR0B, 1 << WGM02);
}

/// @brief Try to change COM0A* bits and check if operation is successful or
/// not.
/// @param mode Mode to be tested
/// @param expected Expected register value
/// @param initial_val Initial value of the register
void set_and_test(enum hal_timer0_output_compare_register reg,
                  enum hal_timer0_output_compare_mode mode, uint8_t expected,
                  uint8_t initial_val) {
    printf("For mode %d, expected value is %d and register is: %08b\n", mode,
           expected, TCCR0A);

    TEST_ASSERT_EQUAL(hal_timer0_set_output_compare_mode(reg, mode),
                      hal_result_timer0_ok);

    switch (reg) {
    default:
    case hal_timer0_output_compare_register_a:
        TEST_ASSERT_EQUAL(TCCR0A >> 6, expected);
        TEST_ASSERT_EQUAL(DDRD & 1 << 6, 1 << 6);
        break;
    case hal_timer0_output_compare_register_b:
        TEST_ASSERT_EQUAL(TCCR0A >> 4, expected);
        TEST_ASSERT_EQUAL(DDRD & 1 << 5, 1 << 5);
        break;
    }
    TEST_ASSERT_EQUAL(TCCR0A & initial_val, initial_val);
}
void test_set_output_compare_mode() {
    enum hal_timer0_output_compare_mode mode;
    enum hal_timer0_output_compare_register reg;

    // Initial value shouldn't be changed, except COM0A* bits.
    uint8_t initial_val = 0b00001010;

    for (reg = hal_timer0_output_compare_register_a;
         reg <= hal_timer0_output_compare_register_b; reg++) {
        printf("Testing OCR: %d\n", reg);
        TCCR0A = initial_val;

        // Invalid modes should return error.
        mode = hal_timer0_compare_output_mode_set + 1;
        TEST_ASSERT_EQUAL(hal_timer0_set_output_compare_mode(reg, mode),
                          hal_result_timer0_invalid_output_compare_mode);
        mode = hal_timer0_compare_output_mode_normal - 1;
        TEST_ASSERT_EQUAL(hal_timer0_set_output_compare_mode(reg, mode),
                          hal_result_timer0_invalid_output_compare_mode);

        set_and_test(reg, hal_timer0_compare_output_mode_normal, 0b00,
                     initial_val);
        set_and_test(reg, hal_timer0_compare_output_mode_toggle, 0b01,
                     initial_val);
        set_and_test(reg, hal_timer0_compare_output_mode_clear, 0b10,
                     initial_val);
        set_and_test(reg, hal_timer0_compare_output_mode_set, 0b11,
                     initial_val);
    }
}

void test_set_output_compare_register_wrong() {
    enum hal_timer0_output_compare_mode mode;
    enum hal_timer0_output_compare_register reg;

    mode = hal_timer0_compare_output_mode_set;

    TEST_ASSERT_EQUAL(hal_timer0_set_output_compare_mode(
                          hal_timer0_output_compare_register_a, mode),
                      hal_result_timer0_ok);
    TEST_ASSERT_EQUAL(hal_timer0_set_output_compare_mode(
                          hal_timer0_output_compare_register_b, mode),
                      hal_result_timer0_ok);
    TEST_ASSERT_EQUAL(hal_timer0_set_output_compare_mode(
                          hal_timer0_output_compare_register_b + 1, mode),
                      hal_result_timer0_invalid_output_compare_register);
}

void test_set_clock_source_invalid() {
    enum hal_timer0_clock_source source;

    for (source = hal_timer0_stop; source <= hal_timer0_external_rising_edge;
         source++) {
        TEST_ASSERT_EQUAL(hal_timer0_set_clock_source(source),
                          hal_result_timer0_ok);
    }

    source = hal_timer0_stop - 1;
    TEST_ASSERT_EQUAL(hal_timer0_set_clock_source(source),
                      hal_result_timer0_invalid_clock_source);
    source = hal_timer0_external_rising_edge + 1;
    TEST_ASSERT_EQUAL(hal_timer0_set_clock_source(source),
                      hal_result_timer0_invalid_clock_source);
}

void test_set_clock_source() {
    enum hal_timer0_clock_source source;

    TEST_ASSERT_EQUAL(TCCR0B, 0);

    for (source = hal_timer0_stop; source <= hal_timer0_external_rising_edge;
         source++) {
        hal_timer0_set_clock_source(source);
        TEST_ASSERT_EQUAL(TCCR0B, source);
    }
}

void test_set_top() {
    uint16_t val;

    TEST_ASSERT_EQUAL(OCR0A, 0);

    for (val = 0; val <= 0xFF; val++) {
        hal_timer0_set_top((uint8_t)val);
        TEST_ASSERT_EQUAL(OCR0A, val);
    }

    val = 0xF0;
    hal_timer0_set_top(val);
    TEST_ASSERT_EQUAL(OCR0A, val);
}

int main() {
    RUN_TEST(basic_set_and_get_timer0_counter);
    RUN_TEST(set_operation_mode);
    RUN_TEST(test_set_output_compare_mode);
    RUN_TEST(test_set_output_compare_register_wrong);
    RUN_TEST(test_set_clock_source_invalid);
    RUN_TEST(test_set_clock_source);
    RUN_TEST(test_set_top);

    return UnityEnd();
}

void setUp() { reset_registers(); }

void tearDown() { reset_registers(); }
