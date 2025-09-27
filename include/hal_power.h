/**
 * @file
 * @author Ceyhun Şen
 *
 * @brief Power management and sleep modes module header file.
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

#ifndef __HAL_POWER_H
#define __HAL_POWER_H

#include <stdint.h>

/**
 * Sleep modes for ATmega328P. Value for every mode is the same as the bit
 * number in target register.
 * */
enum power_sleep_modes {
    power_idle_mode = 0,
    power_adc_noise_reduction_mode = 1,
    power_power_down_mode = 2,
    power_power_save_mode = 3,
    power_standby_mode = 6,
    power_external_standby_mode = 7
};

/**
 * Modules that have configurable power mode. Value for every module is the same
 * as the bit number in target register.
 * */
enum power_modules {
    power_adc = 0,
    power_usart0 = 1,
    power_spi = 2,
    power_timer_1 = 3,
    power_timer0 = 5,
    power_timer_2 = 6,
    power_twi = 7
};

void power_set_sleep_mode(enum power_sleep_modes mode);
void power_set_module_power(enum power_modules module, uint8_t state);

#endif // __HAL_POWER_H
