cmake_minimum_required(VERSION 3.10)
project(todo)

add_executable(main todo.c)
target_compile_options(main PRIVATE -Wall -Wextra -Werror -pedantic-errors)

add_library(queue SHARED queue.c)
target_include_directories(queue PUBLIC "../sizes")

add_library(vector SHARED IMPORTED)
set_property(TARGET vector PROPERTY IMPORTED_LOCATION "../../sizes/build/libvector.so")

target_link_libraries(main vector queue)
