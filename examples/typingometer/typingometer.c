#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

const char* phrases[] = {
  "the quick brown fox jumps over the lazy dog",
  "this is a test, how fast can you type it?",
  "you will be typing a lot of code as a programmer",
  "int main() { return 0; }",
  "the printf and scanf family of functions are widely used for string and file manipulation"
};

//https://stackoverflow.com/questions/3419332/c-preprocessor-stringify-the-result-of-a-macro
#define STRING(str) #str
#define STRINGFY(str) STRING(str)
#define MAX_LENGTH_PHRASE 100
#define MAX_LENGTH_PHRASE_STR STRINGFY(MAX_LENGTH_PHRASE)

unsigned int num_phrases = sizeof(phrases)/sizeof(phrases[0]);

unsigned int min(unsigned int a, unsigned int b) {
  if( a < b ) {
    return a;
  }
  return b;
}

double type_phrase(const char* phrase) {
  char input[MAX_LENGTH_PHRASE+1]={0};
  printf("%s\n", phrase);
  scanf("%" MAX_LENGTH_PHRASE_STR "[^\n]", input);

  unsigned int min_length = min(strlen(phrase), strlen(input));
  unsigned int errors=0;
  for(unsigned int i = 0; i < min_length; i++) {
    if( phrase[i] != input[i] ) {
      errors++;
    }
  }
  printf("errors: %u, min_length: %u\n", errors, min_length);
  return ((double)errors)/(double)min_length;
}

unsigned int number_of_words(char* string) {
  unsigned int spaces = 0;
  unsigned int len = strlen(string)-1;
  for(unsigned int i = 0; i < len; i++) {
    if(string[i] == ' ' && string[i+1] != ' ') {
      spaces++;
    }
  }
  return spaces;
}

int main() {

  srand(time(0));
  const char* phrase = phrases[rand() % num_phrases];

  const time_t start = time(0);
  double error_percentage = type_phrase(phrase);
  const time_t end = time(0);

  unsigned int total_time = end - start;

  printf("time: %us\n", total_time);
  printf("error percentage: %.2F%%\n", error_percentage * 100);

  unsigned int num_words = number_of_words((char*) phrase);
  double minutes = total_time/60.0;
  printf("words per minute: %.2F\n", num_words/minutes);
  printf("characters per minute: %.2F\n", strlen(phrase)/minutes);

  return 0;
}
