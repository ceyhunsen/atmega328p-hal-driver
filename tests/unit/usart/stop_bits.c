/**
 * @file
 * @author Ceyhun Şen
 * @brief Unit tests for stop bits settings for USART.
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

#include "hal_usart.h"
#include "unity.h"
#include "usart.h"
#include <avr/io.h>
#include <test_mock_up.h>

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
