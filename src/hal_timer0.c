/**
 * @file
 * @author Ceyhun Şen
 *
 * @brief Timer module, main functionalities.
 * */

// SPDX-FileCopyrightText: 2026 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include "hal_timer0.h"

enum hal_result_timer0
hal_timer0_set_output_compare_mode(enum hal_timer0_output_compare_mode mode) {
    if (mode < hal_timer0_compare_output_mode_normal ||
        mode > hal_timer0_compare_output_mode_set) {
        return hal_result_timer0_invalid_output_compare_mode;
    }

    return hal_result_timer0_ok;
}
