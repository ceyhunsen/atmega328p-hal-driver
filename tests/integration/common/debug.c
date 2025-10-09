/**
 * @file debug.c
 * @author Ceyhun Şen
 * @brief Debug output for integration tests.
 */

// SPDX-FileCopyrightText: 2023 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include "debug.h"
#include "hal_usart.h"

/**
 * @brief Initialize USART and printf.
 */
void debug_init() {
    struct usart_t usart = {
        .baud_rate = 115200,
        .stop_bits = 1,
        .parity = usart_parity_disabled,
        .data_bits = 8,
        .mode = usart_mode_asynchronous_normal,
        .direction = usart_direction_transmit_and_receive,
    };

    usart_init(&usart);
    usart_stdio_init();
}
