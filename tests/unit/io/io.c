/**
 * @file
 * @author Ceyhun Şen
 * @brief Unit tests for GPIO module.
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

#include "io.h"
#include "unity.h"
#include <test_mock_up.h>

int main() {
    RUN_TEST(test_direction_output_b_single);
    RUN_TEST(test_direction_output_b_multi);
    RUN_TEST(test_direction_output_c_single);
    RUN_TEST(test_direction_output_c_multi);
    RUN_TEST(test_direction_output_d_single);
    RUN_TEST(test_direction_output_d_multi);

    RUN_TEST(test_toggle_b_single);
    RUN_TEST(test_toggle_b_multi);
    RUN_TEST(test_toggle_c_single);
    RUN_TEST(test_toggle_c_multi);
    RUN_TEST(test_toggle_d_single);
    RUN_TEST(test_toggle_d_multi);

    RUN_TEST(test_read_b_single);
    RUN_TEST(test_read_b_multi);
    RUN_TEST(test_read_c_single);
    RUN_TEST(test_read_c_multi);
    RUN_TEST(test_read_d_single);
    RUN_TEST(test_read_d_multi);

    RUN_TEST(test_write_b_single);
    RUN_TEST(test_write_b_multi);
    RUN_TEST(test_write_c_single);
    RUN_TEST(test_write_c_multi);
    RUN_TEST(test_write_d_single);
    RUN_TEST(test_write_d_multi);

    return UnityEnd();
}

void setUp() { reset_registers(); }

void tearDown() { reset_registers(); }
