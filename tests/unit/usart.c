/**
 * @file
 * @author Ceyhun Şen
 * @brief Unit tests for USART module.
 */

// SPDX-FileCopyrightText: 2023 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include "hal_usart.h"
#include "test_mock_up.h"
#include "unity.h"

#include <avr/io.h>

/**
 * Sets necessary data for initializing.
 */
#define SET_MEMBERS(usart)                                                     \
    usart.stop_bits = 2;                                                       \
    usart.baud_rate = 9600;                                                    \
    usart.data_bits = 8;

void test_direction_transmit() {
    struct usart_t usart;
    enum usart_result result;

    SET_MEMBERS(usart);
    usart.direction = usart_direction_transmit;

    result = usart_init(&usart);

    TEST_ASSERT_EQUAL(usart_success, result);

    TEST_ASSERT_EQUAL(1 << TXEN0, UCSR0B);
}

void test_direction_receive() {
    struct usart_t usart;
    enum usart_result result;

    SET_MEMBERS(usart);
    usart.direction = usart_direction_receive;

    result = usart_init(&usart);

    TEST_ASSERT_EQUAL(usart_success, result);

    TEST_ASSERT_EQUAL(1 << RXEN0, UCSR0B);
}

void test_direction_transmit_and_receive() {
    struct usart_t usart;
    enum usart_result result;

    SET_MEMBERS(usart);
    usart.direction = usart_direction_transmit_and_receive;

    result = usart_init(&usart);

    TEST_ASSERT_EQUAL(usart_success, result);

    TEST_ASSERT_EQUAL(1 << TXEN0 | 1 << RXEN0, UCSR0B);
}

void test_asynchronous_normal() {
    struct usart_t usart;
    enum usart_result result;

    SET_MEMBERS(usart);
    usart.mode = usart_mode_asynchronous_normal;

    result = usart_init(&usart);

    TEST_ASSERT_EQUAL(usart_success, result);

    TEST_ASSERT_EQUAL(0, UCSR0C & ((1 << UMSEL00) | (1 << UMSEL01)));
    TEST_ASSERT_EQUAL(0, UCSR0A & (1 << U2X0));
}

void test_asynchronous_double_speed() {
    struct usart_t usart;
    enum usart_result result;

    SET_MEMBERS(usart);
    usart.mode = usart_mode_asynchronous_double_speed;

    result = usart_init(&usart);

    TEST_ASSERT_EQUAL(usart_success, result);

    TEST_ASSERT_EQUAL(0, UCSR0C & ((1 << UMSEL00) | (1 << UMSEL01)));
    TEST_ASSERT_EQUAL(1 << U2X0, UCSR0A & (1 << U2X0));
}

void test_synchronous_master() {
    struct usart_t usart;
    enum usart_result result;

    SET_MEMBERS(usart);
    usart.mode = usart_mode_synchronous_master;

    result = usart_init(&usart);

    TEST_ASSERT_EQUAL(usart_success, result);

    TEST_ASSERT_EQUAL(1 << UMSEL01, UCSR0C & ((1 << UMSEL00) | (1 << UMSEL01)));
    TEST_ASSERT_EQUAL(0, UCSR0A & (1 << U2X0));
}

void test_stop_bits_legal() {
    struct usart_t usart;
    enum usart_result result;

    SET_MEMBERS(usart);

    usart.stop_bits = 2;

    result = usart_init(&usart);

    TEST_ASSERT_EQUAL(usart_success, result);
}

void test_stop_bits_illegal() {
    struct usart_t usart;
    enum usart_result result;

    SET_MEMBERS(usart);

    usart.stop_bits = 3;

    result = usart_init(&usart);

    TEST_ASSERT_EQUAL(usart_error, result);
}

void setUp() {
    reset_registers();

    // This register's value must be modified for tests to pass.
    UCSR0A |= 1 << UDRE0;
}

void tearDown() { reset_registers(); }

int main() {
    RUN_TEST(test_direction_transmit);
    RUN_TEST(test_direction_receive);
    RUN_TEST(test_direction_transmit_and_receive);
    RUN_TEST(test_asynchronous_normal);
    RUN_TEST(test_asynchronous_double_speed);
    RUN_TEST(test_synchronous_master);
    RUN_TEST(test_stop_bits_legal);
    RUN_TEST(test_stop_bits_illegal);

    return UnityEnd();
}
