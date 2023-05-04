#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"

#define COLUMNS 100
#define ROWS 10
#define SIZE_MULTIPLIER 500

void randomize_arr(int* arr, int arr_size) {
    for(int i = 0; i < arr_size; i++) arr[i] = rand() % RAND_MAX;
}

void print_sorting_plot() {
  int arr[COLUMNS * SIZE_MULTIPLIER];

  char matrix[ROWS][COLUMNS];
  memset(&matrix, ' ', ROWS * COLUMNS);
  for(int i = 0; i < COLUMNS; i++) {
    unsigned long arr_size = i * SIZE_MULTIPLIER;
    randomize_arr(arr, arr_size);
    time_t start = time(0);
    quicksort(arr, arr_size);
    time_t end = time(0);
    int quicksort_y = end - start;
    randomize_arr(arr, arr_size);
    start = time(0);
    selection_sort(arr, arr_size);
    end = time(0);
    int selection_y = end - start;
    if( quicksort_y < ROWS ) {
      matrix[ROWS - quicksort_y - 1][i] = 'Q';
    }
    if( selection_y < ROWS ) {
      matrix[ROWS - selection_y - 1][i] = 'S';
    }
    if( selection_y < ROWS && quicksort_y < ROWS && selection_y == quicksort_y ) { 
      matrix[ROWS - selection_y - 1][i] = 'T';
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

int main() {
    print_sorting_plot();
    return 0;
}
