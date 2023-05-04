#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.14159265358979323846
#define NUM_POINTS 1000000

double random_double() {
  return rand()/(double)RAND_MAX;
}

int is_inside_circle() {
  double x = random_double();
  double y = random_double();

  double distance_squared = x * x + y * y;
  return distance_squared < 1;
}

int main() {
  srand(time(0));

  double inside = 0.0;
  unsigned int num_points = 0;
  do {
    if( is_inside_circle() ) inside++;
    #ifdef DEBUG
      printf("current pi(%u): %F\n", num_points, 4 * inside/NUM_POINTS);
    #endif
    num_points++;
  } while( num_points < NUM_POINTS );
  printf("pi guess: %F\n", 4 * inside/NUM_POINTS);
  printf("pi real: %F\n", PI);
}
