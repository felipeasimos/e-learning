cmake_minimum_required(VERSION 3.10)
project(loc)

add_executable(main loc.c)
target_compile_options(main PRIVATE -Wall -Wextra -Werror -pedantic-errors)
