/**
 * @file
 * @author Ceyhun Şen
 * @brief Unit tests for USART module.
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

#include "usart.h"
#include "unity.h"
#include <avr/io.h>

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
