#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#include "vector.h"


#define COLUMNS 3
#define ROWS 5

Vector* create_vector_with_size(unsigned int size) {
    Vector* vec = vector_create(1, size);
    memset(vec->vec, 0x00, size);
    vec->num_elements = size;
    return vec;
}

List* create_list_with_size(unsigned int size) {
    List* list = list_create(0);
    for(unsigned int i =0; i < size; i++) {
        list = list_append(list, NULL, 0);
    }
    return list;
}

void print_list_vs_vector_plot(void* (*list_func)(List*), void* (*vec_func)(Vector*), unsigned int scale_multiplier, unsigned int repetitions) {
  char matrix[ROWS][COLUMNS];
  memset(&matrix, ' ', ROWS * COLUMNS);
  for(int i = 0; i < COLUMNS; i++) {
    unsigned int arr_size = (i+1) * scale_multiplier;
    Vector* vector = create_vector_with_size(arr_size);
    if(!vector) printf("sadfaf\n\n\n");
    time_t start = time(0);
    for(unsigned int j = 0; j < repetitions; j++) vector = vec_func(vector);
    time_t end = time(0);
    vector_free(vector);
    int vector_y = (end - start);
    List* list = create_list_with_size(arr_size);
    start = time(0);
    for(unsigned int j = 0; j < repetitions; j++) list = list_func(list);
    end = time(0);
    list_free(list);
    int list_y = (end - start);
    if( vector_y < ROWS ) {
      matrix[ROWS - vector_y - 1][i] = 'V';
    }
    if( list_y < ROWS ) {
      matrix[ROWS - list_y - 1][i] = 'L';
    }
    if( list_y < ROWS && list_y == vector_y ) { 
      matrix[ROWS - list_y - 1][i] = 'T';
    }
  }

  for(int i = 0; i < ROWS; i++) {
    printf("%02d |", ROWS - i - 1);
    for(int j = 0; j < COLUMNS; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
}

void* get_list_element(List* list) {
    list_get(list, list->list_len-1);
    return list;
}

void* get_vector_element(Vector* vector) {
    vector_get(vector, vector->num_elements-1);
    return vector;
}

void* append_list_element(List* list) {
    return list_append(list, NULL, 0);
}

void* append_vector_element(Vector* vector) {
    char c = 'a';
    return vector_insert(vector, &c, 0);
}

void* remove_list_element(List* list) {
    list_remove_node(list, list->start);
    return list;
}

void* remove_vector_element(Vector* vector) {
    return vector_remove(vector, 0);
}

int main() {
    printf("get element:\n");
    print_list_vs_vector_plot(get_list_element, get_vector_element, 1000000, 100);
    printf("append element:\n");
    print_list_vs_vector_plot(append_list_element, append_vector_element, 1000000, 100);
    printf("remove element:\n");
    print_list_vs_vector_plot(remove_list_element, remove_vector_element, 1000000, 100);
    return 0;
}
