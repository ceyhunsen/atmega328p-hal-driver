cmake_minimum_required(VERSION 3.11)
project(atmega328p_hal_driver VERSION 0.3)

# set(CMAKE_C_COMPILER "avr-gcc")
# set(CMAKE_CXX_COMPILER "avr-g++")

add_library(atmega328p_hal_driver src/hal_power.c src/hal_system.c)

target_include_directories(atmega328p_hal_driver PUBLIC include)
target_compile_definitions(atmega328p_hal_driver PUBLIC __AVR_ATmega328P__)

# Optionally, build examples.
option(BUILD_EXAMPLES "Build example programs" OFF)
if(BUILD_EXAMPLES)
  add_subdirectory(examples/power)
  add_subdirectory(examples/system)
endif()
