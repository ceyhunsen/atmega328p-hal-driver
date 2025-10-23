/**
 * @file
 * @author Ceyhun Şen
 * @brief Unit tests for power management and sleep modes module.
 */

// SPDX-FileCopyrightText: 2025 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include "hal_power.h"
#include "test_mock_up.h"
#include "unity.h"

#include <avr/io.h>

void test_power_idle_mode() {
    enum hal_power_sleep_modes mode;

    mode = hal_power_idle_mode;

    hal_power_set_sleep_mode(mode);

    // Test if register value is correct.
    TEST_ASSERT_EQUAL(0b000 << 1, SMCR & 0b1110);

    // Test if enum value is the same with register value.
    TEST_ASSERT_EQUAL(mode << 1, SMCR & 0b1110);

    // Test if sleep enable bit is disabled.
    TEST_ASSERT_EQUAL(0, SMCR & 0b1);
}

void test_power_adc_noise_reduction_mode() {
    enum hal_power_sleep_modes mode;

    mode = hal_power_adc_noise_reduction_mode;

    hal_power_set_sleep_mode(mode);

    // Test if register value is correct.
    TEST_ASSERT_EQUAL(0b001 << 1, SMCR & 0b1110);

    // Test if enum value is the same with register value.
    TEST_ASSERT_EQUAL(mode << 1, SMCR & 0b1110);

    // Test if sleep enable bit is disabled.
    TEST_ASSERT_EQUAL(0, SMCR & 0b1);
}

void test_power_power_down_mode() {
    enum hal_power_sleep_modes mode;

    mode = hal_power_power_down_mode;

    hal_power_set_sleep_mode(mode);

    // Test if register value is correct.
    TEST_ASSERT_EQUAL(0b010 << 1, SMCR & 0b1110);

    // Test if enum value is the same with register value.
    TEST_ASSERT_EQUAL(mode << 1, SMCR & 0b1110);

    // Test if sleep enable bit is disabled.
    TEST_ASSERT_EQUAL(0, SMCR & 0b1);
}

void test_power_power_save_mode() {
    enum hal_power_sleep_modes mode;

    mode = hal_power_power_save_mode;

    hal_power_set_sleep_mode(mode);

    // Test if register value is correct.
    TEST_ASSERT_EQUAL(0b011 << 1, SMCR & 0b1110);

    // Test if enum value is the same with register value.
    TEST_ASSERT_EQUAL(mode << 1, SMCR & 0b1110);

    // Test if sleep enable bit is disabled.
    TEST_ASSERT_EQUAL(0, SMCR & 0b1);
}

void test_power_standby_mode() {
    enum hal_power_sleep_modes mode;

    mode = hal_power_standby_mode;

    hal_power_set_sleep_mode(mode);

    // Test if register value is correct.
    TEST_ASSERT_EQUAL(0b110 << 1, SMCR & 0b1110);

    // Test if enum value is the same with register value.
    TEST_ASSERT_EQUAL(mode << 1, SMCR & 0b1110);

    // Test if sleep enable bit is disabled.
    TEST_ASSERT_EQUAL(0, SMCR & 0b1);
}

void test_power_external_standby_mode() {
    enum hal_power_sleep_modes mode;

    mode = hal_power_external_standby_mode;

    hal_power_set_sleep_mode(mode);

    // Test if register value is correct.
    TEST_ASSERT_EQUAL(0b111 << 1, SMCR & 0b1110);

    // Test if enum value is the same with register value.
    TEST_ASSERT_EQUAL(mode << 1, SMCR & 0b1110);

    // Test if sleep enable bit is disabled.
    TEST_ASSERT_EQUAL(0, SMCR & 0b1);
}

void test_power_set_sleep_mode_incorrect_input() {
    enum hal_power_sleep_modes incorrect_mode;
    incorrect_mode = (1 << 8) - 1;

    TEST_ASSERT_EQUAL(0, SMCR);

    uint8_t initial_value = SMCR;

    hal_power_set_sleep_mode(incorrect_mode);

    TEST_ASSERT_EQUAL(initial_value, SMCR);
}

/**
 * Test if modules are turned on/off when every other module is turned on. When
 * a module is turned on, bit value should be 0 for respective bit.
 */
void test_module_power_single() {
    enum hal_power_modules i;
    for (i = 0; i < 8; i++) {
        hal_power_set_module_power(i, 1);
        TEST_ASSERT_EQUAL(0, PRR);

        hal_power_set_module_power(i, 0);
        TEST_ASSERT_EQUAL(1 << i, PRR);

        reset_registers();
    }
}

/**
 * Test if modules are turned on/off without resetting registers. This will test
 * if hal driver is overwriting other modules or not.
 */
void test_module_power_multi() {
    uint8_t reg = 0;

    // Start from beginning.
    enum hal_power_modules i;
    for (i = 0; i < 8; i++) {
        hal_power_set_module_power(i, 1);
        TEST_ASSERT_EQUAL(0, PRR & (1 << i));

        hal_power_set_module_power(i, 0);
        TEST_ASSERT_EQUAL(reg | (1 << i), PRR);

        reg = PRR;
    }

    reg = 0;
    reset_registers();

    // Start from last.
    for (i = 0; i < 8; i++) {
        hal_power_set_module_power(7 - i, 1);
        TEST_ASSERT_EQUAL(0, PRR & (1 << (7 - i)));

        hal_power_set_module_power(7 - i, 0);
        TEST_ASSERT_EQUAL(reg | (1 << (7 - i)), PRR);

        reg = PRR;
    }

    // No random order testing.
}

int main() {
    RUN_TEST(test_power_idle_mode);
    RUN_TEST(test_power_adc_noise_reduction_mode);
    RUN_TEST(test_power_power_down_mode);
    RUN_TEST(test_power_power_save_mode);
    RUN_TEST(test_power_standby_mode);
    RUN_TEST(test_power_external_standby_mode);
    RUN_TEST(test_module_power_single);
    RUN_TEST(test_module_power_multi);
    RUN_TEST(test_power_set_sleep_mode_incorrect_input);

    return UnityEnd();
}

void setUp() { reset_registers(); }

void tearDown() { reset_registers(); }
