#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void selection_sort(int* arr, unsigned long num_elements) {

  if( num_elements <= 1 ) return;

  // iterate over vector
  for(unsigned long sorted_idx = 0; sorted_idx < num_elements; sorted_idx++) {
    unsigned long lowest_idx = sorted_idx;
    // iterate over unsorted part of the vector
    for(unsigned long unsorted_idx = sorted_idx+1; unsorted_idx < num_elements; unsorted_idx++) {
      if( arr[unsorted_idx] < arr[lowest_idx] ) {
        lowest_idx = unsorted_idx;
      }
    }
    // swap 'highest_idx' with 'sorted_idx'
    swap(&arr[lowest_idx], &arr[sorted_idx]);
  }
}

void quicksort(int* arr, unsigned long num_elements) {
  
    if( num_elements < 2 ) return;

    unsigned long lower_index = 0;
    for(unsigned long i = 1; i < num_elements; i++) {
        int* current_element = &arr[i];
        if(*current_element < arr[0]) {
            swap(current_element, &arr[++lower_index]);
        }
    }

    swap(&arr[lower_index], arr);
    quicksort(arr, lower_index);
    quicksort(&arr[lower_index+1], num_elements - lower_index - 1);
}
