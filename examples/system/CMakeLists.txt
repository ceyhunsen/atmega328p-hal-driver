cmake_minimum_required(VERSION 3.11)

add_executable(system_example system.c)
target_link_libraries(system_example PRIVATE atmega328p_hal_driver)
