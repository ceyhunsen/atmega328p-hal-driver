/**
 * @file
 * @author Ceyhun Şen
 * @brief I/O (GPIO) operations
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
 * Every I/O function will return \ref hal_result_io. This value can be checked
 * if operation was successful or wasn't.
 *
 * ## Configuring Pins
 *
 * Configuring a I/O pin is done with hal_io_configure() function. This function
 * will accept any kind of information about a pin.
 *
 * ### Switching Between Input and Output
 *
 * \ref hal_io_pin_configuration's `direction` member can be used to specify
 * direction of an I/O pin.
 *
 * ### Setting Pin As Pull-Up/Pull-Down In Input Mode
 *
 * I/O pins with input direction, can be configured with pull-up enabled or
 * disabled. To do this, \ref hal_io_pin_configuration's `is_pull_up` member can
 * be used.
 *
 * ## Read/Write Operations On Pins
 *
 * ### Change Pin Output State
 *
 * I/O pins can be driven high or low with hal_io_write() function.
 *
 * ### Toggling Pin Output State
 *
 * Pin state can be toggled with hal_io_toggle() function.
 *
 * ### Reading Pin Input State
 *
 * Pin state can be read with hal_io_read() function. Read value should be
 * stored in given \ref hal_io_pin_state pointer.
 * */

// SPDX-FileCopyrightText: 2025 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef __HAL_IO_H
#define __HAL_IO_H

#include <stdint.h>

/**
 * @enum hal_result_io
 * @brief Module specific return results.
 */
enum hal_result_io {
    hal_io_success = 0,
    hal_result_io_error_invalid_pin,
    hal_result_io_error_invalid_port,
    hal_result_io_error_invalid_direction
};

/**
 * @enum hal_io_port
 * @brief Port specifier of a I/O pin.
 */
enum hal_io_port { hal_io_port_b = 0, hal_io_port_c, hal_io_port_d };

/**
 * I/O pin specifier.
 *
 * @param port Target port.
 * @param pin Target pin of the port
 */
struct hal_io_pin {
    enum hal_io_port port;
    uint8_t pin;
};

/**
 * @enum hal_io_pin_state
 * @brief State of the current I/O pin.
 */
enum hal_io_pin_state { hal_io_state_low = 0, hal_io_state_high = 1 };

/**
 * @enum hal_io_pin_direction
 * @brief Direction settings for I/O pins.
 */
enum hal_io_pin_direction { hal_io_direction_output, hal_io_direction_input };

/**
 * Configuration options for an I/O pin.
 *
 * @param direction Direction of the pin.
 * @param pull_up Is pull-up enabled? 0 on disabled, 1 (or other values) on
 * enabled.
 */
struct hal_io_pin_configuration {
    enum hal_io_pin_direction direction;
    uint8_t is_pull_up;
};

enum hal_result_io
hal_io_configure(struct hal_io_pin io,
                 struct hal_io_pin_configuration configuration);
enum hal_result_io hal_io_write(struct hal_io_pin io,
                                enum hal_io_pin_state state);
enum hal_result_io hal_io_toggle(struct hal_io_pin io);
enum hal_result_io hal_io_read(struct hal_io_pin io,
                               enum hal_io_pin_state *state);

#endif // __HAL_IO_H
