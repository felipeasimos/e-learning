#include <stdio.h>
#include <stdint.h>
#include <string.h>

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

void help() {

    printf("display PPM_FILE\n");
    printf("must be used with a binary PPM file\n");
}

unsigned int get_unsigned_int(FILE* file) {
  char buf[64]={0};
  int counter = 0;
  for(char c = fgetc(file); c != ' '; c = fgetc(file)) {
    buf[counter++] = c;
  }
  unsigned int res;
  sscanf(buf, "%u", &res);
  return res;
}

int main(int argc, char* argv[]) {

  if( argc < 2 ) {
    help();
  }

  char* filename = argv[1];
  FILE* file = NULL;
  if( !( file = fopen(filename, "rb") ) ) {
    return 1;
  }

  HEADER header = {0};
  // header type
  fread(header.type, sizeof(header.type), 1, file);
  if( strncmp(header.type, "P6", 2) ) {
    help();
    return 1;
  }
  fseek(file, 1L, SEEK_CUR);
  header.width = get_unsigned_int(file);
  header.height = get_unsigned_int(file);
  header.maximum = get_unsigned_int(file);

  for(unsigned int row = 0; row < header.height; row++) {
    for(unsigned int column = 0; column < header.width; column++) {
      RGB rgb;
      fread(&rgb, sizeof(rgb), 1, file);
      printf("\x1b[48;2;%hu;%hu;%hum \x1b[0m", rgb.red, rgb.blue, rgb.green);
    }
    printf("\n");
  }
  fclose(file);

  return 0;
}
