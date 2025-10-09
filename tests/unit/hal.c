/**
 * @file
 * @author Ceyhun Şen
 * @brief Unit tests for internal HAL interface.
 */

// SPDX-FileCopyrightText: 2023 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include "hal_internals.h"
#include "unity.h"

#include <stdint.h>

/**
 * Tests if clear bit macro works as expected.
 */
void test_clear_bit() {
    uint8_t value;

    value = 0b11111111;

    // Clear second least significant bit.
    CLEAR_BIT(value, 1);

    TEST_ASSERT_EQUAL(0b11111101, value);
}

/**
 * Tests if clearing an already cleared bit messes up the value.
 */
void test_clear_a_cleared_bit() {
    uint8_t value;

    value = 0b11111101;

    // Clear second least significant bit.
    CLEAR_BIT(value, 1);

    TEST_ASSERT_EQUAL(0b11111101, value);
}

/**
 * Tests clearing every bit.
 */
void test_clear_every_bit() {
    uint32_t value, expected, i;

    value = INT32_MAX;
    expected = INT32_MAX;

    for (i = 0; i < 31; i++) {
        CLEAR_BIT(value, 31 - i - 1);
        expected >>= 1;

        TEST_ASSERT_EQUAL(expected, value);
    }
}

/**
 * Tests if set bit macro works as expected.
 */
void test_set_bit() {
    uint8_t value;

    value = 0;

    // Set second least significant bit.
    SET_BIT(value, 1);

    TEST_ASSERT_EQUAL(0b10, value);
}

/**
 * Tests if setting an already setted bit messes up the value.
 */
void test_set_a_setted_bit() {
    uint8_t value;

    value = 0b11;

    // Set second least significant bit.
    SET_BIT(value, 1);

    TEST_ASSERT_EQUAL(0b11, value);
}

/**
 * Tests setting every bit.
 */
void test_set_every_bit() {
    uint32_t value, expected, i;

    value = 0;
    expected = 0;

    for (i = 0; i < 32; i++) {
        SET_BIT(value, 32 - i - 1);
        expected |= 1 << (32 - i - 1);

        TEST_ASSERT_EQUAL(expected, value);
    }
}

void setUp() {}
void tearDown() {}

int main() {
    RUN_TEST(test_clear_bit);
    RUN_TEST(test_clear_a_cleared_bit);
    RUN_TEST(test_clear_every_bit);
    RUN_TEST(test_set_bit);
    RUN_TEST(test_set_a_setted_bit);
    RUN_TEST(test_set_every_bit);

    return UnityEnd();
}
