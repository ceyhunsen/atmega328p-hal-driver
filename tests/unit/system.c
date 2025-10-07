/**
 * @file
 * @author Ceyhun Şen
 * @brief Unit tests for system control and reset module.
 */

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

#include "hal_internals.h"
#include "hal_system.h"
#include "test_mock_up.h"
#include "unity.h"
#include <avr/io.h>

/**
 * Test if reset status function returns same value as the register and resets
 * register afterwards.
 */
void test_reset_cause() {
    uint8_t i, cause;

    for (i = 0; i < 4; i++) {
        MCUSR = 1 << i;

        cause = system_get_reset_status();

        TEST_ASSERT_EQUAL(1 << i, cause);
        TEST_ASSERT_EQUAL(0, MCUSR);

        if (i == 0) {
            TEST_ASSERT_EQUAL(system_power_on_reset, cause);
        } else if (i == 1) {
            TEST_ASSERT_EQUAL(system_external_reset, cause);
        } else if (i == 2) {
            TEST_ASSERT_EQUAL(system_brownout_reset, cause);
        } else if (i == 3) {
            TEST_ASSERT_EQUAL(system_watchdog_reset, cause);
        }
    }
}

void test_set_modes() {
    struct system_watchdog_t config;

    config.mode = system_watchdog_disabled;
    system_set_watchdog(config);
    TEST_ASSERT_EQUAL(0, WDTCSR & BIT(WDIE));
    TEST_ASSERT_EQUAL(0, WDTCSR & BIT(WDE));

    config.mode = system_watchdog_interrupt_mode;
    system_set_watchdog(config);
    TEST_ASSERT_EQUAL(BIT(WDIE), WDTCSR & BIT(WDIE));
    TEST_ASSERT_EQUAL(0, WDTCSR & BIT(WDE));

    config.mode = system_watchdog_reset_mode;
    system_set_watchdog(config);
    TEST_ASSERT_EQUAL(0, WDTCSR & BIT(WDIE));
    TEST_ASSERT_EQUAL(BIT(WDE), WDTCSR & BIT(WDE));

    config.mode = system_watchdog_interrupt_and_reset_mode;
    system_set_watchdog(config);
    TEST_ASSERT_EQUAL(BIT(WDIE), WDTCSR & BIT(WDIE));
    TEST_ASSERT_EQUAL(BIT(WDE), WDTCSR & BIT(WDE));
}

void test_set_cycles() {
    uint8_t i;
    struct system_watchdog_t config;

    for (i = 0; i < 10; i++) {
        config.cycles = system_watchdog_2k_cycles + i;
        system_set_watchdog(config);
        TEST_ASSERT_EQUAL(config.cycles, WDTCSR & 0b1111);
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
