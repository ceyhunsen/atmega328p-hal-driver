/**
 * @file
 * @author Ceyhun Şen
 * @brief USART extra HAL functions for ATmega328P HAL driver.
 * */

/*
 * MIT License
 *
 * Copyright (c) 2022 Ceyhun Şen
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
