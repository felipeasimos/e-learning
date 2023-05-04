#include <stdio.h>

void help() {
  printf("loc FILE\n");
}

int main(int argc, char* argv[]) {

  if(argc < 2) {
    help();
    return 1;
  }
  FILE* file = NULL;
  if( !(file = fopen(argv[1], "rt") ) ) {
    help();
    return 1;
  }
  char c=0x00;
  unsigned int newlines=0;
  do {
    if( c == '\n' ) newlines++;
    c = fgetc(file);
  } while( c != EOF );
  printf("%u\n", newlines);
  return 0;
}
