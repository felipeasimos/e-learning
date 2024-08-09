cmake_minimum_required(VERSION 3.10)
project(list_vs_vector)

add_executable(main list_vs_vector.c)
target_compile_options(main PRIVATE -Wall -Wextra -Werror -pedantic-errors)

add_library(list SHARED list.c)
add_library(vector SHARED IMPORTED)

IF (WIN32)
  set_property(TARGET vector PROPERTY IMPORTED_LOCATION "../../sizes/build/libvector.dll")
  set_property(TARGET vector PROPERTY IMPORTED_IMPLIB "../../sizes/build/libvector.dll.a")
  set_target_properties(vector PROPERTIES LINKER_LANGUAGE C)
ELSE()
  set_property(TARGET vector PROPERTY IMPORTED_LOCATION "../../sizes/build/libvector.so")
ENDIF()

target_link_libraries(main vector list)
