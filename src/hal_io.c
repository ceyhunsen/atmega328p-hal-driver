/**
 * @file
 * @author Ceyhun Şen
 *
 * Standard I/O operations.
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

#include "hal_io.h"
#include "hal_internals.h"
#include <avr/io.h>

static volatile uint8_t *get_ddr_pointer(enum io_port port);
static volatile uint8_t *get_port_pointer(enum io_port port);
static volatile uint8_t *get_pin_pointer(enum io_port port);

/**
 * Configure an I/O pin.
 *
 * @param io I/O pin to be configured.
 * @param configuration How to configure selected pin.
 */
enum io_result io_configure(struct io_pin io,
                            struct io_pin_configuration configuration) {
    // Get port pointers.
    volatile uint8_t *ddr_pointer, *port_pointer;
    uint8_t ddr_value, port_value;

    ddr_pointer = get_ddr_pointer(io.port);
    port_pointer = get_port_pointer(io.port);

    // Read register values before doing a modification. Reading these
    // values beforehand will help in case of an interruption from another
    // context like interrupts.
    ddr_value = *ddr_pointer;
    port_value = *port_pointer;

    // Set direction.
    switch (configuration.direction) {
    case io_direction_output:
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
    case io_direction_input:
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

    return io_success;
}

/**
 * Set pin state of given I/O pin.
 *
 * @param io Target I/O pin.
 * @param state Pin state to be set.
 * */
enum io_result io_write(struct io_pin io, enum io_pin_state state) {
    volatile uint8_t *port_pointer;
    port_pointer = get_port_pointer(io.port);

    switch (state) {
    case io_state_high:
        SET_BIT(*port_pointer, io.pin);
        break;
    default:
    case io_state_low:
        CLEAR_BIT(*port_pointer, io.pin);
        break;
    }

    return io_success;
}

/**
 * Toggle state of the given pin.
 *
 * @param io Target I/O pin.
 * */
enum io_result io_toggle(struct io_pin io) {
    volatile uint8_t *pin_pointer;

    pin_pointer = get_pin_pointer(io.port);

    SET_BIT(*pin_pointer, io.pin);

    return io_success;
}

/**
 * Read value of a I/O pin.
 *
 * @param io Target I/O pin.
 * @param state Pointer that will hold read result.
 * */
enum io_result io_read(struct io_pin io, enum io_pin_state *state) {
    volatile uint8_t *pin_pointer;
    pin_pointer = get_pin_pointer(io.port);

    uint8_t pin_value = *pin_pointer;

    *state = (pin_value & BIT(io.pin)) ? io_state_high : io_state_low;

    return io_success;
}

/**
 * @brief Get DDRx pointer.
 *
 * @param port I/O port.
 * @returns DDRx pointer
 * @see io_port
 * */
static volatile uint8_t *get_ddr_pointer(enum io_port port) {
    volatile uint8_t *p;

    p = &DDRB + ((uint8_t)port * 3);

    return p;
}

/**
 * @brief Get PORTx pointer.
 *
 * @param port I/O port.
 * @returns PORTx pointer.
 * @see io_port
 * */
static volatile uint8_t *get_port_pointer(enum io_port port) {
    volatile uint8_t *p;

    p = &PORTB + ((uint8_t)port * 3);

    return p;
}

/**
 * @brief Get PINx pointer.
 *
 * @param port I/O port.
 * @returns PINx pointer.
 * @see io_port
 * */
static volatile uint8_t *get_pin_pointer(enum io_port port) {
    volatile uint8_t *p;

    p = &PINB + ((uint8_t)port * 3);

    return p;
}
