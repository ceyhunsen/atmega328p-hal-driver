cmake_minimum_required(VERSION 3.11)

add_executable(power_example power.c)
target_link_libraries(power_example PRIVATE atmega328p_hal_driver)
