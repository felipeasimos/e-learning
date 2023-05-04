cmake_minimum_required(VERSION 3.10)
project(sizes)

add_executable(main sizes.c)
target_compile_options(main PRIVATE -Wall -Wextra -Werror -pedantic-errors)

add_library(vector SHARED vector.c)
target_link_libraries(main vector)
