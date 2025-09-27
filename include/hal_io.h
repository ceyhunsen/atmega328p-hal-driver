/**
 * @file
 * @author Ceyhun Şen
 *
 * Main header for I/O module.
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

#ifndef __HAL_IO_H
#define __HAL_IO_H

#include <stdint.h>

/**
 * @enum io_result
 * @brief Module specific return results.
 */
enum io_result {
    io_success = 0,
    io_error,
};

/**
 * @enum io_port
 * @brief Port specifier of a I/O pin.
 */
enum io_port { io_port_b = 0, io_port_c, io_port_d };

/**
 * I/O pin specifier.
 *
 * @param port Target port.
 * @param pin Target pin of the port
 */
struct io_pin {
    enum io_port port;
    uint8_t pin;
};

/**
 * @enum io_pin_state
 * @brief State of the current I/O pin.
 */
enum io_pin_state { io_state_low = 0, io_state_high = 1 };

/**
 * @enum io_pin_direction
 * @brief Direction settings for I/O pins.
 */
enum io_pin_direction { io_direction_output, io_direction_input };

/**
 * Configuration options for an I/O pin.
 *
 * @param direction Direction of the pin.
 * @param pull_up Is pull-up enabled? 0 on disabled, 1 (or other values) on
 * enabled.
 */
struct io_pin_configuration {
    enum io_pin_direction direction;
    uint8_t is_pull_up;
};

enum io_result io_configure(struct io_pin io,
                            struct io_pin_configuration configuration);
enum io_result io_write(struct io_pin io, enum io_pin_state state);
enum io_result io_toggle(struct io_pin io);
enum io_result io_read(struct io_pin io, enum io_pin_state *state);

#endif // __HAL_IO_H
