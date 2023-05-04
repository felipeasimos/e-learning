cmake_minimum_required(VERSION 3.10)
project(hanoi)

add_executable(main hanoi.c)
target_compile_options(main PRIVATE -Wall -Wextra -Werror -pedantic-errors)

add_library(stack SHARED stack.c)
target_include_directories(stack PUBLIC "../sizes")

add_library(vector SHARED IMPORTED)
set_property(TARGET vector PROPERTY IMPORTED_LOCATION "../../sizes/build/libvector.so")

target_link_libraries(main vector stack)
