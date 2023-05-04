cmake_minimum_required(VERSION 3.10)
project(display)

add_executable(main display.c)
target_compile_options(main PRIVATE -Wall -Wextra -Werror -pedantic-errors)
