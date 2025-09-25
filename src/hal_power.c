/**
 * @file
 * @author Ceyhun Şen
 *
 * @brief Power management and sleep modes module, main functionalities.
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

#include "hal_power.h"
#include "hal_internals.h"
#include <avr/io.h>
#include <avr/sleep.h>

/**
 * @brief Set sleep mode for ATmega328P.
 * @param mode Sleep mode to be set.
 */
void power_set_sleep_mode(enum power_sleep_modes mode) {
  // Assign new mode. Other bits of the register should be 0.
  SMCR = mode << 1;

  // Set sleep enable bit and call sleep instruction.
  SET_BIT(SMCR, SE);
  sleep_cpu();

  // Clear sleep flag after sleep.
  CLEAR_BIT(SMCR, SE);
}

/**
 * @brief Set specified module's power on or off. If a module is turned off,
 * it might need reinitialization (refer to data-sheet).
 * @param module Module name.
 * @param state 1 (or any other positive number) for on, 0 for off.
 * */
void power_set_module_power(enum power_modules module, uint8_t state) {
  if (state)
    CLEAR_BIT(PRR, module);
  else
    SET_BIT(PRR, module);
}
