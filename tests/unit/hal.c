/**
 * @file
 * @author Ceyhun Şen
 * @brief Unit tests for internal HAL interface.
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
