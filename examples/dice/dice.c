#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {

  if( argc < 2 ) {
    printf("como usar: dice NUM\n");
    return 0;
  }
  srand(time(0));
  int num;
  sscanf(argv[1], "%d", &num);
  int random = rand() % num;
  printf("%d\n", random);
  return 0;
}
