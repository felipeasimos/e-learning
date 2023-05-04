cmake_minimum_required(VERSION 3.10)
project(drawing)

add_executable(main drawing.c)
target_compile_options(main PRIVATE -Wall -Wextra -Werror -pedantic-errors)
