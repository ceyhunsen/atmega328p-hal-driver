/**
 * @file
 * @author Ceyhun Şen
 *
 * Standard I/O operations.
 * */

// SPDX-FileCopyrightText: 2025 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include "hal_io.h"
#include "hal_internals.h"

#include <avr/io.h>

static volatile uint8_t *get_ddr_pointer(enum hal_io_port port);
static volatile uint8_t *get_port_pointer(enum hal_io_port port);
static volatile uint8_t *get_pin_pointer(enum hal_io_port port);

/**
 * Checks if IO pin is valid. If not, returns error.
 */
#define CHECK_IO_PIN(io)                                                       \
    if (io.port > hal_io_port_d) {                                             \
        return hal_result_io_error_invalid_port;                               \
    }                                                                          \
    if (io.pin > 8) {                                                          \
        return hal_result_io_error_invalid_pin;                                \
    }

/**
 * Checks if IO pin configuration is valid. If not, returns error.
 */
#define CHECK_IO_PIN_CONFIGURATION(io)                                         \
    if (configuration.direction > hal_io_direction_input) {                    \
        return hal_result_io_error_invalid_direction;                          \
    }

/**
 * Checks if IO state is valid. If not, returns error.
 */
#define CHECK_IO_STATE(state)                                                  \
    if (state > hal_io_state_high) {                                           \
        return hal_result_io_error_invalid_state;                              \
    }

/**
 * Configure an I/O pin to either input or output.
 *
 * @param io I/O pin to be configured.
 * @param configuration How to configure selected pin.
 *
 * @returns If given pin or configuration is invalid, returns related error.
 */
enum hal_result_io
hal_io_configure(struct hal_io_pin io,
                 struct hal_io_pin_configuration configuration) {
    // Get port pointers.
    volatile uint8_t *ddr_pointer, *port_pointer;
    uint8_t ddr_value, port_value;
    ddr_pointer = get_ddr_pointer(io.port);
    port_pointer = get_port_pointer(io.port);

    CHECK_IO_PIN(io);
    CHECK_IO_PIN_CONFIGURATION(configuration);

    // Read register values before doing a modification. Reading these
    // values beforehand will help in case of an interruption from another
    // context like interrupts.
    ddr_value = *ddr_pointer;
    port_value = *port_pointer;

    // Set direction.
    switch (configuration.direction) {
    case hal_io_direction_output:
        // Tri-state intermediate step.
        if (!(ddr_value & BIT(io.pin)) && !(port_value & BIT(io.pin))) {
            CLEAR_BIT(*port_pointer, io.pin);
        }
        // Input pull up intermediate step.
        if (!(ddr_value & BIT(io.pin)) && (port_value & BIT(io.pin))) {
            CLEAR_BIT(*port_pointer, io.pin);
        }

        SET_BIT(*ddr_pointer, io.pin);

        break;
    default:
    case hal_io_direction_input:
        if (configuration.is_pull_up) {
            // Output low intermediate step.
            if ((ddr_value & BIT(io.pin)) && !(port_value & BIT(io.pin))) {
                SET_BIT(*port_pointer, io.pin);
            }

            CLEAR_BIT(*ddr_pointer, io.pin);
            SET_BIT(*port_pointer, io.pin);
        } else {
            // Output high intermediate step.
            if ((ddr_value & BIT(io.pin)) && (port_value & BIT(io.pin))) {
                SET_BIT(*ddr_pointer, io.pin);
                CLEAR_BIT(*port_pointer, io.pin);
            }

            CLEAR_BIT(*ddr_pointer, io.pin);
            CLEAR_BIT(*port_pointer, io.pin);
        }
    }

    return hal_result_io_ok;
}

/**
 * Set state of a given I/O pin.
 *
 * @param io Target I/O pin.
 * @param state Pin state to be set.
 *
 * @returns If given pin or state is invalid, returns related error.
 * */
enum hal_result_io hal_io_write(struct hal_io_pin io,
                                enum hal_io_pin_state state) {
    volatile uint8_t *port_pointer;
    port_pointer = get_port_pointer(io.port);

    CHECK_IO_PIN(io);
    CHECK_IO_STATE(state);

    switch (state) {
    default:
    case hal_io_state_high:
        SET_BIT(*port_pointer, io.pin);
        break;
    case hal_io_state_low:
        CLEAR_BIT(*port_pointer, io.pin);
        break;
    }

    return hal_result_io_ok;
}

/**
 * Toggle state of the given pin.
 *
 * @param io Target I/O pin.
 *
 * @returns If given pin is invalid, returns related error.
 * */
enum hal_result_io hal_io_toggle(struct hal_io_pin io) {
    volatile uint8_t *pin_pointer;
    pin_pointer = get_pin_pointer(io.port);

    CHECK_IO_PIN(io);

    SET_BIT(*pin_pointer, io.pin);

    return hal_result_io_ok;
}

/**
 * Read value of a I/O pin.
 *
 * @param io Target I/O pin.
 * @param state Pointer that will hold read result.
 *
 * @returns If given pin is invalid, returns related error.
 * */
enum hal_result_io hal_io_read(struct hal_io_pin io,
                               enum hal_io_pin_state *state) {
    volatile uint8_t *pin_pointer;
    pin_pointer = get_pin_pointer(io.port);

    CHECK_IO_PIN(io);

    uint8_t pin_value = *pin_pointer;

    *state = (pin_value & BIT(io.pin)) ? hal_io_state_high : hal_io_state_low;

    return hal_result_io_ok;
}

/**
 * Gets DDRx pointer for a port.
 *
 * @param port I/O port.
 *
 * @returns DDRx pointer
 *
 * @see hal_io_port
 * */
static volatile uint8_t *get_ddr_pointer(enum hal_io_port port) {
    volatile uint8_t *p;

    p = &DDRB + ((uint8_t)port * 3);

    return p;
}

/**
 * Gets PORTx pointer for a port.
 *
 * @param port I/O port.
 *
 * @returns PORTx pointer.
 *
 * @see hal_io_port
 * */
static volatile uint8_t *get_port_pointer(enum hal_io_port port) {
    volatile uint8_t *p;

    p = &PORTB + ((uint8_t)port * 3);

    return p;
}

/**
 * Gets PINx pointer for a port.
 *
 * @param port I/O port.
 *
 * @returns PINx pointer.
 *
 * @see hal_io_port
 * */
static volatile uint8_t *get_pin_pointer(enum hal_io_port port) {
    volatile uint8_t *p;

    p = &PINB + ((uint8_t)port * 3);

    return p;
}
