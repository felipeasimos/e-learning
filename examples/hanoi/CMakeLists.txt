cmake_minimum_required(VERSION 3.10)
project(hanoi)

add_executable(main hanoi.c)
target_compile_options(main PRIVATE -Wall -Wextra -Werror -pedantic-errors)

add_library(stack SHARED stack.c)

add_library(vector SHARED IMPORTED)

IF (WIN32)
  set_property(TARGET vector PROPERTY IMPORTED_LOCATION "../../sizes/build/libvector.dll")
  set_property(TARGET vector PROPERTY IMPORTED_IMPLIB "../../sizes/build/libvector.dll.a")
  set_target_properties(vector PROPERTIES LINKER_LANGUAGE C)
  target_link_libraries(stack vector)
ELSE()
  set_property(TARGET vector PROPERTY IMPORTED_LOCATION "../../sizes/build/libvector.so")
ENDIF()

target_link_libraries(main vector stack)
