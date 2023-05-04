cmake_minimum_required(VERSION 3.10)
project(csv_plot)

add_executable(main csv_plot.c)
target_link_libraries(main m)
target_compile_options(main PRIVATE -Wall -Wextra -Werror -pedantic-errors)
