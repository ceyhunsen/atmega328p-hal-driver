/**
 * @file
 * @author Ceyhun Şen
 * @brief Usart module
 *
 * ## Initializing USART
 *
 * USART can be initialized with \ref usart_init() function after setting a
 * valid \ref usart_t instance.
 *
 * Code example:
 *
 * ```c
 * struct usart_t usart;
 * enum usart_result result;
 *
 * usart.stop_bits = 1;
 * usart.baud_rate = 9600;
 * usart.data_bits = 8;
 * usart.parity = usart_parity_disabled;
 * usart.direction = usart_direction_transmit;
 * usart.mode = usart_mode_asynchronous_normal,
 *
 * result = usart_init(&usart);
 * ```
 *
 * ## Sending Data Over USART
 *
 * After initializing USART, data can be sent with \ref usart_transmit()
 * function.
 *
 * Code example:
 *
 * ```c
 * uint8_t data[] = "Hello, world!\r\n";
 * result = usart_transmit(&usart, data, sizeof data);
 * ```
 * */

// SPDX-FileCopyrightText: 2023 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

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
