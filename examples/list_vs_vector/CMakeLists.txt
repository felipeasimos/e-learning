cmake_minimum_required(VERSION 3.10)
project(list_vs_vector)

add_executable(main list_vs_vector.c)
target_compile_options(main PRIVATE -Wall -Wextra -Werror -pedantic-errors)

add_library(list SHARED list.c)

add_library(vector SHARED IMPORTED)
set_property(TARGET vector PROPERTY IMPORTED_LOCATION "../../sizes/build/libvector.so")

target_link_libraries(main vector list)
