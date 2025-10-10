/**
 * @file
 * @author Ceyhun Şen
 * @brief USART extra HAL functions for ATmega328P HAL driver.
 * */

// SPDX-FileCopyrightText: 2023 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include "hal_internals.h"
#include "hal_usart.h"
#include <avr/io.h>
#include <stdio.h>

/*******************************************************************************
 * Standart I/O support.
 ******************************************************************************/

/**
 * @brief Transmit a char on USART for stdio.
 * @param c Char to transmit.
 * @param stream I/O stream (only here cause it's necessary).
 * @retval 0
 * */
static int usart_stdio_transmit_char(char c, FILE *stream) {
    // Add cariage return character to the end of the stream.
    if (c == '\n')
        usart_stdio_transmit_char('\r', stream);

    // Wait till' any ongoing transfer is complete.
    loop_until_bit_is_set(UCSR0A, UDRE0);

    // Set char.
    UDR0 = c;

    return 0;
}

/**
 * @brief Receive a char on USART for stdio.
 * @param stream I/O stream (only here cause it's necessary).
 * @returns Received char.
 * */
static int usart_stdio_receive_char(FILE *stream) {
    // Wait till' any ongoing transfer is complete.
    loop_until_bit_is_set(UCSR0A, UDRE0);

    // Wait till' data is received.
    loop_until_bit_is_set(UCSR0A, RXC0);

    // Get data.
    char c = UDR0;

    return c;
}

/**
 * @brief Initialize standart I/O stream.
 * */
void usart_stdio_init() {
    // Set stdout.
    static FILE hal_stdout =
        FDEV_SETUP_STREAM(usart_stdio_transmit_char, NULL, _FDEV_SETUP_WRITE);
    stdout = &hal_stdout;

    // Set stdin.
    static FILE hal_stdin =
        FDEV_SETUP_STREAM(NULL, usart_stdio_receive_char, _FDEV_SETUP_READ);
    stdin = &hal_stdin;
}
