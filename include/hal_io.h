/**
 * @file
 * @author Ceyhun Şen
 *
 * # I/O Module
 *
 * ## Capabilities
 *
 * - Pin direction can be set to input or output
 *   - Pull-up or pull-down selection when pin is configured as input
 * - High or low signal output when pin is configured as output
 *   - Toggle pin output signal when pin is configured as output
 * - Pin level reading when pin is configured as input
 *
 * ## Function Return Type
 *
 * Every I/O function will return `io_result` type. This value can be
 * checked if operation was successful or wasn't.
 *
 * ## Configuring Pins
 *
 * Configuring a I/O pin is done with `io_configure()` function. This function
 * will accept any kind of information about a pin.
 *
 * ### Switching Between Input and Output
 *
 * `struct io_pin_configuration.direction` can be used to specify direction of
 * an I/O pin.
 *
 * ### Setting Pin As Pull-Up/Pull-Down In Input Mode
 *
 * I/O pins with input direction, can be configured with pull-up enabled or
 * disabled. To do this, `struct io_pin_configuration.is_pull_up` can be used.
 *
 * ## Read/Write Operations On Pins
 *
 * ### Change Pin Output State
 *
 * I/O pins can be driven high or low with `io_write()` function.
 *
 * ### Toggling Pin Output State
 *
 * Pin state can be toggled with `io_toggle()` function.
 *
 * ### Reading Pin Input State
 *
 * Pin state can be read with `io_read()` function. Read value should be stored
 * in given `enum io_pin_state` pointer.
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
