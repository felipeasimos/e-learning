#include "vector.h"

#include <stdlib.h>
#include <string.h>

Vector* vector_create(unsigned int element_size, unsigned int capacity) {
  if( !capacity ) capacity = 1;
  Vector* vector = malloc(sizeof(Vector) + capacity * element_size);
  vector->element_size = element_size;
  vector->capacity = capacity;
  vector->num_elements = 0;
  return vector;
}

void vector_free(Vector* vector) {
  free(vector);
}

void* vector_get(Vector* vector, unsigned int index) {
  return &vector->vec[index * vector->element_size];
}

void vector_set(Vector* vector, void* element, unsigned int index) {
  memcpy(vector_get(vector, index), element, vector->element_size);
}

Vector* vector_insert(Vector* vector, void* element, unsigned int index) {  
  if( vector->capacity == vector->num_elements ) {
    vector->capacity <<= 1;
    vector = realloc(vector, sizeof(Vector) + vector->capacity * vector->element_size);
  }
  // move elements up front
  for(int i = vector->num_elements-1; (int)index < i; i--) {
    vector_set(vector, vector_get(vector, i), i+1);
  }
  vector->num_elements++;
  vector_set(vector, element, index);
  return vector;
}

Vector* vector_remove(Vector* vector, unsigned int index) {
  vector->num_elements--;
  for(unsigned int i = index; i < vector->num_elements; i++) {
    vector_set(vector, vector_get(vector, i+1), i);
  }
  return vector;
}

void vector_print(Vector* vector, void (*print)(void* element)) {
  for(unsigned int i = 0; i < vector->num_elements; i++) {
    print(vector_get(vector, i));
  }
}

void vector_sort(Vector* vector, int (*cmp)(void*, void*)) {
  qsort(vector->vec, vector->num_elements, vector->element_size, (int (*)(const void*, const void*))cmp);
}
