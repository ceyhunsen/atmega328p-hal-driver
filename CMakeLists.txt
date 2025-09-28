cmake_minimum_required(VERSION 3.11)

add_library(atmega328p_hal_driver src/hal_power.c src/hal_system.c)

target_include_directories(atmega328p_hal_driver PUBLIC include)
target_compile_definitions(atmega328p_hal_driver PUBLIC __AVR_ATmega328P__)
