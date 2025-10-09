/**
 * @file
 * @author Ceyhun Şen
 *
 * Main header for I/O module.
 * */

// SPDX-FileCopyrightText: 2023 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

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
