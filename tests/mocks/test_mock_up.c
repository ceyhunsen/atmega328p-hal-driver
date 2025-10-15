/**
 * @file test_mock_up.c
 * @author Ceyhun Şen
 * @brief Mock-up register definitions for testing.
 */

// SPDX-FileCopyrightText: 2025 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include "test_mock_up.h"

#include <pthread.h>
#include <stdint.h>
#include <string.h>

/**
 * @brief Virtual mock-up memory for ATmega328P registers.
 */
uint8_t __atmega328p_registers[0xFF];

/**
 * @brief Reset virtual memory.
 */
void reset_registers() {
    // Reset everything to zero.
    memset(__atmega328p_registers, 0, sizeof __atmega328p_registers);
}

/**
 * @brief Spawns a thread that will watch for changes in registers and does it's
 * stuff. This is useful especially for interrupts.
 * @param handler Function that will watch for changes and will do it's stuff.
 */
void spawn_watcher_thread(void *(*handler)()) {
    pthread_t t;
    pthread_create(&t, NULL, handler, NULL);
}
