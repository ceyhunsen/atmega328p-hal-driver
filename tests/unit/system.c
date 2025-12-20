/**
 * @file
 * @author Ceyhun Şen
 * @brief Unit tests for system control and reset module.
 */

// SPDX-FileCopyrightText: 2025 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include "hal_internals.h"
#include "hal_system.h"
#include "test_mock_up.h"
#include "unity.h"
#include <avr/io.h>

void test_set_modes() {
    struct hal_system_watchdog_t config;

    config.mode = hal_system_watchdog_disabled;
    hal_system_set_watchdog(config);
    TEST_ASSERT_EQUAL(0, WDTCSR & BIT(WDIE));
    TEST_ASSERT_EQUAL(0, WDTCSR & BIT(WDE));

    config.mode = hal_system_watchdog_interrupt_mode;
    hal_system_set_watchdog(config);
    TEST_ASSERT_EQUAL(BIT(WDIE), WDTCSR & BIT(WDIE));
    TEST_ASSERT_EQUAL(0, WDTCSR & BIT(WDE));

    config.mode = hal_system_watchdog_reset_mode;
    hal_system_set_watchdog(config);
    TEST_ASSERT_EQUAL(0, WDTCSR & BIT(WDIE));
    TEST_ASSERT_EQUAL(BIT(WDE), WDTCSR & BIT(WDE));

    config.mode = hal_system_watchdog_interrupt_and_reset_mode;
    hal_system_set_watchdog(config);
    TEST_ASSERT_EQUAL(BIT(WDIE), WDTCSR & BIT(WDIE));
    TEST_ASSERT_EQUAL(BIT(WDE), WDTCSR & BIT(WDE));
}

void test_set_cycles() {
    uint8_t i;
    struct hal_system_watchdog_t config;

    for (i = 0; i < 10; i++) {
        config.cycles = hal_system_watchdog_2k_cycles + i;
        hal_system_set_watchdog(config);
        TEST_ASSERT_EQUAL(config.cycles, WDTCSR & 0b1111);
    }
}

/**
 * Test if reset status function returns same value as the register and resets
 * register afterwards.
 */
void test_reset_cause() {
    uint8_t i;
    enum hal_system_reset_status cause;

    for (i = 0; i < 4; i++) {
        MCUSR = 1 << i;

        cause = hal_system_get_reset_status();

        TEST_ASSERT_EQUAL(1 << i, cause);
        TEST_ASSERT_EQUAL(0, MCUSR);

        if (i == 0) {
            TEST_ASSERT_EQUAL(hal_system_power_on_reset, cause);
        } else if (i == 1) {
            TEST_ASSERT_EQUAL(hal_system_external_reset, cause);
        } else if (i == 2) {
            TEST_ASSERT_EQUAL(hal_system_brownout_reset, cause);
        } else if (i == 3) {
            TEST_ASSERT_EQUAL(hal_system_watchdog_reset, cause);
        }
    }
}

int main() {
    RUN_TEST(test_reset_cause);
    RUN_TEST(test_set_modes);
    RUN_TEST(test_set_cycles);

    return UnityEnd();
}

void setUp() { reset_registers(); }

void tearDown() { reset_registers(); }
