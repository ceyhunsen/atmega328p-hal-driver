/**
 * @file
 * @author Ceyhun Şen
 * @brief Unit tests for power management and sleep modes module.
 */

// SPDX-FileCopyrightText: 2025 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include "hal_internals.h"
#include "hal_power.h"
#include "test_mock_up.h"
#include "unity.h"

#include <avr/io.h>

void sleep_callback() { TEST_ASSERT_EQUAL(1, SMCR & BIT(SE)); }
void test_sleep_mode() {
    enum hal_power_sleep_modes mode;
    for (mode = hal_power_idle_mode; mode <= hal_power_external_standby_mode;
         mode++) {
        int ret = hal_power_set_sleep_mode(mode);

        // For illegal values between the max and min values, check if it
        // errors out.
        if (mode != 4 && mode != 5) {
            TEST_ASSERT_EQUAL(ret, 0);
        } else {
            TEST_ASSERT_EQUAL(ret, 1);
            continue;
        }

        // Test if enum value is same as the register value.
        TEST_ASSERT_EQUAL(mode << 1, SMCR & 0b1110);

        // Test if sleep enable bit is disabled after the change.
        TEST_ASSERT_EQUAL(0, SMCR & BIT(SE));
    }
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
        if (i == 4) {
            TEST_ASSERT_EQUAL(1, hal_power_set_module_power(i, 1));
            continue;
        }

        TEST_ASSERT_EQUAL(0, hal_power_set_module_power(i, 1));
        TEST_ASSERT_EQUAL(0, PRR);

        TEST_ASSERT_EQUAL(0, hal_power_set_module_power(i, 0));
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
        if (i == 4) {
            TEST_ASSERT_EQUAL(1, hal_power_set_module_power(i, 1));
            continue;
        }

        TEST_ASSERT_EQUAL(0, hal_power_set_module_power(i, 1));
        TEST_ASSERT_EQUAL(0, PRR & (1 << i));

        TEST_ASSERT_EQUAL(0, hal_power_set_module_power(i, 0));
        TEST_ASSERT_EQUAL(reg | (1 << i), PRR);

        reg = PRR;
    }

    reg = 0;
    reset_registers();

    // Start from last.
    for (i = 0; i < 8; i++) {
        if (i == 3) {
            TEST_ASSERT_EQUAL(1, hal_power_set_module_power(7 - i, 1));
            continue;
        }

        TEST_ASSERT_EQUAL(0, hal_power_set_module_power(7 - i, 1));
        TEST_ASSERT_EQUAL(0, PRR & (1 << (7 - i)));

        TEST_ASSERT_EQUAL(0, hal_power_set_module_power(7 - i, 0));
        TEST_ASSERT_EQUAL(reg | (1 << (7 - i)), PRR);

        reg = PRR;
    }

    // No random order testing.
}

void test_change_module_powers_reserved_value() {
    uint8_t power_off, power_on;

    power_off = BIT(4);
    power_on = 0;
    TEST_ASSERT_EQUAL(1, hal_power_change_module_powers(power_off, power_on));

    power_off = 0;
    power_on = BIT(4);
    TEST_ASSERT_EQUAL(1, hal_power_change_module_powers(power_off, power_on));

    power_off = BIT(4);
    power_on = BIT(4);
    TEST_ASSERT_EQUAL(1, hal_power_change_module_powers(power_off, power_on));
}

void test_change_module_powers_same_bit() {
    int i;

    for (i = 0; i < 1 << 8; i++) {
        if (i & BIT(4)) {
            continue;
        }

        TEST_ASSERT_EQUAL(
            1, hal_power_change_module_powers((uint8_t)i, (uint8_t)i));
    }
}

int main() {
    RUN_TEST(test_sleep_mode);
    RUN_TEST(test_module_power_single);
    RUN_TEST(test_module_power_multi);
    RUN_TEST(test_power_set_sleep_mode_incorrect_input);
    RUN_TEST(test_change_module_powers_reserved_value);
    RUN_TEST(test_change_module_powers_same_bit);

    return UnityEnd();
}

void setUp() { reset_registers(); }

void tearDown() { reset_registers(); }
