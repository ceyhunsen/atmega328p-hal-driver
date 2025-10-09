/**
 * @file
 * @author Ceyhun Şen
 * @brief Unit tests for mock interface.
 */

// SPDX-FileCopyrightText: 2023 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

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
