#include <stdio.h>
#include <string.h>
#include <math.h>

// csv plots
#define COLUMNS 100
#define ROWS 30

double f(float x) {
  return sin(x/6) * 10 + 15;
}

void help() {
    printf("csv_plot FILE RANGE1 RANGE2 STEP\n");
}

int main(int argc, char* argv[1]) {

  if( argc < 5 ) {
    help();
    return 1;
  }

  FILE* file;
  if(!( file = fopen(argv[1], "wt"))) {
    fprintf(stderr, "couldn't create file\n");
    return 1;
  }

  double range_x1, range_x2, step_x;
  if( !sscanf(argv[2], "%lf", &range_x1) ) {
    help();
    return 1;
  }
  if( !sscanf(argv[3], "%lf", &range_x2) ) {
    help();
    return 1;
  }
  if( !sscanf(argv[4], "%lf", &step_x) ) {
    help();
    return 1;
  }

  // header
  fprintf(file, "x, y\n");
  for(double x = range_x1; x <= range_x2; x += step_x) {
    fprintf(file, "%F,%F\n", x, f(x));
  }
  fclose(file);
  return 0;
}
