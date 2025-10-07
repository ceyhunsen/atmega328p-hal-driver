/**
 * @file
 * @author Ceyhun Şen
 * @brief Unit tests for mock interface.
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

#include "unity.h"
#include <avr/io.h>
#include <test_mock_up.h>

/**
 * Tests if reset register function actually clears mock-up register.
 */
void test_reset() {
    __atmega328p_registers[0x00] = 0xDE;
    __atmega328p_registers[0x0F] = 0xAD;
    __atmega328p_registers[0x1F] = 0xBE;
    __atmega328p_registers[0xFE] = 0xEF;

    TEST_ASSERT_EQUAL(0xDE, __atmega328p_registers[0x00]);
    TEST_ASSERT_EQUAL(0xAD, __atmega328p_registers[0x0F]);
    TEST_ASSERT_EQUAL(0xBE, __atmega328p_registers[0x1F]);
    TEST_ASSERT_EQUAL(0xEF, __atmega328p_registers[0xFE]);

    reset_registers();

    TEST_ASSERT_EQUAL(0x00, __atmega328p_registers[0x00]);
    TEST_ASSERT_EQUAL(0x00, __atmega328p_registers[0x0F]);
    TEST_ASSERT_EQUAL(0x00, __atmega328p_registers[0x1F]);
    TEST_ASSERT_EQUAL(0x00, __atmega328p_registers[0xFE]);
}

/**
 * Tests if reset register function actually clears mock-up register with real
 * register name access.
 */
void test_writing_registers_and_ressetting() {
    UDR0 = 0xAF;

    TEST_ASSERT_EQUAL(0xAF, UDR0);
    TEST_ASSERT_EQUAL(0xAF, __atmega328p_registers[0xC6]); // UDR0 points
                                                           // to 0xC6
                                                           // address.

    reset_registers();

    TEST_ASSERT_EQUAL(0x00, UDR0);
    TEST_ASSERT_EQUAL(0x00, __atmega328p_registers[0xC6]);
}

void setUp() {}

void tearDown() {}

int main() {
    RUN_TEST(test_reset);
    RUN_TEST(test_writing_registers_and_ressetting);

    return UnityEnd();
}
