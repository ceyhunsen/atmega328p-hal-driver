# Master makefile for all tests. This makefile will call every test seperately.
# Change HOST_C_STD and MCU_C_LIB paths according to your system.
#
# Author: Ceyhun Şen

# Copyright (c) 2023 Ceyhun Şen
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Host system C standard library include directory.
HOST_C_STD = /usr/include/

# AVR-libc include directory.
MCU_C_LIB  = -isystem /usr/avr/include -isystem /usr/lib/avr/include

# Host C compiler.
export HOST_CC = gcc

# MCU C compiler and other stuff.
export MCU_CC = avr-gcc
export MCU_OBJ_COPY = avr-objcopy
export MCU_SIZE = avr-size

# MCU specific stuff.
export MCU = atmega328p
export PROGRAMMER = arduino
export BAUD = 115200
export PORT = /dev/ttyUSB0
export AVRDUDE = avrdude

# Local build directory.
export BUILD_DIR = build

# Host include directories.
export HOST_C_INCLUDES =  \
-I $(CURDIR)/../include   \
-I $(CURDIR)/Unity/src    \

# MCU include directories.
export MCU_C_INCLUDES =          \
-I $(CURDIR)/../include          \
-I $(CURDIR)/Unity/src           \
-I $(CURDIR)/integration/common  \

# Host system include directories.
export HOST_C_SYS_INCLUDES =  \
-isystem $(HOST_C_STD)        \
-isystem $(CURDIR)/mocks      \
$(MCU_C_LIB)         \

# Host C definitions.
export HOST_C_DEFINES =  \
-D __AVR_ATmega328P__    \

# MCU C definitions.
export MCU_C_DEFINES =  \
-D F_CPU=16000000UL     \

# Host C flags.
export HOST_C_FLAGS =  \
-Wall                  \
-O2                    \
$(HOST_C_DEFINES)      \
$(HOST_C_INCLUDES)     \
$(HOST_C_SYS_INCLUDES) \

# MCU C flags.
export MCU_C_FLAGS =  \
-Wall                 \
-O1                   \
-mmcu=$(MCU)          \
$(MCU_C_DEFINES)      \
$(MCU_C_INCLUDES)     \

# Host source files.
export HOST_C_SOURCES =  \
unity.c                  \
test_mock_up.c           \

# MCU source files.
export MCU_C_SOURCES =  \
unity.c                 \
debug.c                 \
hal_usart.c             \
hal_usart_extra.c       \

# Compile .c files to object files.
export HOST_COMPILE_OBJ = $(HOST_CC) $(HOST_C_FLAGS) -c

# Link previously compiled object files and create the test executable.
export HOST_COMPILE = $(HOST_CC) $(HOST_C_FLAGS) $(BUILD_DIR)/*.o

# Compile .c files to object files.
export MCU_COMPILE_OBJ = $(MCU_CC) $(MCU_C_FLAGS) -c

# Link previously compiled object files and create the test executable.
export MCU_COMPILE = $(MCU_CC) $(MCU_C_FLAGS) $(BUILD_DIR)/*.o

# Use this paths for searching source and header files.
export VPATH =                \
$(CURDIR)/Unity/src/          \
$(CURDIR)/mocks/              \
$(CURDIR)/integration/common  \
$(CURDIR)/../src/             \
$(CURDIR)/../include/         \

# All unit test directories.
UNIT_TESTS = $(wildcard unit/*/.)

# All integration test directories.
INTEGRATION_TESTS = $(wildcard integration/*/.)

# Run all tests.
all: unit integration

unit: $(UNIT_TESTS)

$(UNIT_TESTS):
	$(MAKE) -C $@

integration: $(INTEGRATION_TESTS)

$(INTEGRATION_TESTS):
	$(MAKE) -C $@

clean:
	rm -rf unit/*/build/ integration/*/build

.PHONY: clean $(UNIT_TESTS) $(INTEGRATION_TESTS)
