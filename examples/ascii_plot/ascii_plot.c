#include <stdio.h>
#include <string.h>
#include <math.h>

#define COLUMNS 100
#define ROWS 30

float f(float x) {
  return sin(x/6) * 10 + 15;
}

int main() {
  char matrix[ROWS][COLUMNS];
  memset(&matrix, ' ', ROWS * COLUMNS);

  for(int i = 0; i < COLUMNS; i++) {
    int y = (int)f(i);
    if( y < ROWS ) {
      matrix[ROWS - y - 1][i] = '*';
    }
  }

  for(int i = 0; i < ROWS; i++) {
    printf("%02d |", ROWS - i - 1);
    for(int j = 0; j < COLUMNS; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
  return 0;
}
