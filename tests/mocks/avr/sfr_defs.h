/**
 * @file sfr_defs.h
 * @author Ceyhun Şen
 * @brief Mock-up header of macros for accessing AVR special function registers.
 * This header must overwrite avr/sfr_defs.h for testing.
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

#ifndef __SFR_DEFS_H
#define __SFR_DEFS_H

#include <stdint.h>

extern uint8_t __atmega328p_registers[];

#define _MMIO_BYTE(mem_addr) __atmega328p_registers[mem_addr]
#define _MMIO_WORD(mem_addr) __atmega328p_registers[mem_addr]
#define _MMIO_DWORD(mem_addr) __atmega328p_registers[mem_addr]

#define __SFR_OFFSET 0x20

#define _BV(bit) (1 << (bit))

#define _SFR_MEM8(mem_addr) _MMIO_BYTE(mem_addr)
#define _SFR_MEM16(mem_addr) _MMIO_WORD(mem_addr)
#define _SFR_MEM32(mem_addr) _MMIO_DWORD(mem_addr)

#define _SFR_IO8(io_addr) _MMIO_BYTE((io_addr) + __SFR_OFFSET)
#define _SFR_IO16(io_addr) _MMIO_WORD((io_addr) + __SFR_OFFSET)

#define bit_is_set(sfr, bit) (sfr & _BV(bit))
#define bit_is_clear(sfr, bit) (!(sfr & _BV(bit)))

#define loop_until_bit_is_set(sfr, bit)                                        \
    do {                                                                       \
    } while (bit_is_clear(sfr, bit))
#define loop_until_bit_is_clear(sfr, bit)                                      \
    do {                                                                       \
    } while (bit_is_set(sfr, bit))

#endif // __SFR_DEFS_H
