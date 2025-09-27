/**
 * @file
 * @author Ceyhun Şen
 * @brief USART header file for ATmega328P HAL driver.
 * */

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

#ifndef __HAL_USART_H
#define __HAL_USART_H

#include <stdint.h>

/**
 * Return results for USART module.
 */
enum usart_result {
    usart_success = 0,
    usart_error,
    usart_error_overrun,
    usart_error_underrun,
    usart_error_framing,
    usart_error_parity,
};

/**
 * USART data direction.
 * */
enum usart_direction {
    usart_direction_transmit,
    usart_direction_receive,
    usart_direction_transmit_and_receive
};

/**
 * Operating modes for USART.
 * */
enum usart_mode {
    usart_mode_asynchronous_normal,
    usart_mode_asynchronous_double_speed,
    usart_mode_synchronous_master
};

/**
 * Parity options for USART.
 * */
enum usart_parity {
    usart_parity_disabled,
    usart_parity_even,
    usart_parity_odd
};

/**
 * USART data struct.
 *
 * @param baud_rate
 * * 2400
 * * 4800
 * * 9600
 * * 14400
 * * 19200
 * * 28800
 * * 38400
 * * 57600
 * * 76800
 * * 115200
 * * 230400
 * * 250000
 *
 * @param data_bits
 * * 5
 * * 6
 * * 7
 * * 8
 * * 9
 *
 * @param stop_bits
 * * 1
 * * 2
 * */
struct usart_t {
    uint32_t baud_rate;
    uint8_t data_bits;
    uint8_t stop_bits;
    enum usart_direction direction;
    enum usart_mode mode;
    enum usart_parity parity;
};

// Core functions.
enum usart_result usart_init(struct usart_t *usart);
enum usart_result usart_transmit(struct usart_t *usart, uint8_t *data,
                                 uint16_t len);
enum usart_result usart_receive(struct usart_t *usart, uint8_t *data,
                                uint16_t len);

// Extras.
void usart_stdio_init();

#endif // __HAL_USART_H
