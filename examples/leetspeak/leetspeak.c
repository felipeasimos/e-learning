#include <stdio.h>
#include <string.h>

void convert_to_leetspeak(char* word) {
  int word_size = strlen(word);
  for(int i = 0; i < word_size; i++) {
    char c;
    switch (word[i]) {
      case 'A':
      case 'a':
        c = '4';
        break;
      case 'B':
      case 'b':
        c = '8';
        break;
      case 'C':
      case 'c':
        c = '<';
        break;
      case 'E':
      case 'e':
        c = '3';
        break;
      case 'H':
      case 'h':
        c = '#';
        break;
      default:
        c = word[i];
        break;
    }
    word[i] = c;
  }
}

int main(int argc, char** argv) {

  if(argc < 2) {
    printf("usage: leetspeak WORDS\n");
    return 1;
  }

  for(int i = 1; i < argc; i++) {
    char* word = argv[i];
    convert_to_leetspeak(word);
    printf("%s ", word);
  }
  printf("\n");
  return 0;
}
