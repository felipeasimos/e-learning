#include <stdio.h>
#include <stdint.h>

#define MAXIMUM 255
#define WIDTH 140
#define HEIGHT 140

typedef struct {
  uint8_t red;
  uint8_t blue;
  uint8_t green;
} RGB;

typedef struct {
  char type[2];
  unsigned int width;
  unsigned int height;
  unsigned int maximum;
} HEADER;

void cap_rgb(RGB* rgb) {
  rgb->red %= MAXIMUM;
  rgb->blue %= MAXIMUM;
  rgb->green %= MAXIMUM;
}

#define MAX_ITER 100
#define MANDELBROT_RADIUS_SQUARED 2.25
#define MANDELBROT_RADIUS 1.5
RGB func(unsigned int x, unsigned int y) {
  double x0 = x * (MANDELBROT_RADIUS_SQUARED/HEIGHT) - MANDELBROT_RADIUS * 1.1;
  double y0 = y * (MANDELBROT_RADIUS_SQUARED/WIDTH) - MANDELBROT_RADIUS * 0.74;
  unsigned int iter = 0;
  double mb_zx = 0;
  double mb_zy = 0;
  for(; mb_zx*mb_zx + mb_zy*mb_zy < MANDELBROT_RADIUS_SQUARED && iter < MAX_ITER; iter++) {
    double x_tmp = mb_zx * mb_zx - mb_zy * mb_zy + x0;
    mb_zy = 2 * mb_zx * mb_zy + y0;
    mb_zx = x_tmp;
  }

  RGB rgb = {
    .red = iter * iter,
    .blue = iter * iter,
    .green = iter * iter,
  };
  cap_rgb(&rgb);
  return rgb;
}

int main(int argc, char* argv[]) {

  if( argc < 2 ) {
    printf("drawing FILE\n");
  }

  char* filename = argv[1];
  FILE* file = NULL;
  if( !( file = fopen(filename, "wb") ) ) {
    return 1;
  }
  const HEADER header = {
    .type = "P6",
    .width = WIDTH,
    .height = HEIGHT,
    .maximum = MAXIMUM,
  };

  fprintf(file, "%s %u %u %u ",
          header.type,
          header.width,
          header.height,
          header.maximum
  );

  for(unsigned int i = 0; i < header.width; i++) {
    for(unsigned int j = 0; j < header.height; j++) {
      RGB rgb = func(j, i);
      fwrite(&rgb, sizeof(rgb), 1, file);
    }
  }
  fclose(file);

  return 0;
}
