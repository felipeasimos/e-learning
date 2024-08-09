cmake_minimum_required(VERSION 3.10)
project(todo)

add_executable(main todo.c)
target_compile_options(main PRIVATE -Wall -Wextra -Werror -pedantic-errors)

add_library(queue SHARED queue.c)

add_library(vector SHARED IMPORTED)

IF (WIN32)
  set_property(TARGET vector PROPERTY IMPORTED_LOCATION "../../sizes/build/libvector.dll")
  set_property(TARGET vector PROPERTY IMPORTED_IMPLIB "../../sizes/build/libvector.dll.a")
  set_target_properties(vector PROPERTIES LINKER_LANGUAGE C)
  target_link_libraries(queue vector)
ELSE()
  set_property(TARGET vector PROPERTY IMPORTED_LOCATION "../../sizes/build/libvector.so")
ENDIF()

target_link_libraries(main vector queue)
