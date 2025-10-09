/**
 * @file sfr_defs.h
 * @author Ceyhun Şen
 * @brief Mock-up header of macros for accessing AVR special function registers.
 * This header must overwrite avr/sfr_defs.h for testing.
 */

// SPDX-FileCopyrightText: 2023 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

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
