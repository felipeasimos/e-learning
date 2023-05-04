#pragma once

#include <stdint.h>
#include <stdio.h>

typedef struct Vector {
  unsigned int num_elements;
  unsigned int element_size;
  unsigned int capacity;
  uint8_t vec[];
} Vector;

Vector* vector_create(unsigned int element_size, unsigned int capacity);
void vector_free(Vector*);
void* vector_get(Vector*, unsigned int index);
void vector_set(Vector*, void* element, unsigned int index);

Vector* vector_insert(Vector*, void* element, unsigned int index);
Vector* vector_remove(Vector*, unsigned int index);

void vector_print(Vector*, void (*print)(void* element));

void vector_sort(Vector*, int (*cmp)(void*, void*));
