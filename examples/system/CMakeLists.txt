cmake_minimum_required(VERSION 3.11)

# Create new example project.
project(system_example)
add_executable(system_example system.c)

# We must use avr-gcc as our compiler.
set(CMAKE_C_COMPILER "avr-gcc")
set(CMAKE_CXX_COMPILER "avr-g++")

# Add ATmega328P HAL driver as subdirectory.
add_subdirectory("${PROJECT_SOURCE_DIR}/../.." atmega328p_hal_build)
target_link_libraries(system_example PRIVATE atmega328p_hal_driver)
