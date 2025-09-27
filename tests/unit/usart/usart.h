/**
 * @file
 * @author Ceyhun Şen
 * @brief Unit test header for USART module.
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

#ifndef __USART_H
#define __USART_H

#include "test_mock_up.h"

/**
 * Sets necessary data for initializing.
 */
#define SET_MEMBERS(usart)                                                     \
    usart.stop_bits = 2;                                                       \
    usart.baud_rate = 9600;                                                    \
    usart.data_bits = 8;

void test_direction_transmit();
void test_direction_receive();
void test_direction_transmit_and_receive();
void test_asynchronous_normal();
void test_asynchronous_double_speed();
void test_synchronous_master();
void test_stop_bits_legal();
void test_stop_bits_illegal();

#endif // __USART_H
