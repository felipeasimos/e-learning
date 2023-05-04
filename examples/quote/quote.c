#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum {
    Unknown=0,
    Book=1,
    Person=2,
} SourceType;

typedef struct {
    SourceType sourceType;
    char* source;
    char* text;
} Quote;


unsigned int num_lines(FILE* file) {
  long current = ftell(file);
  char c=0x00;
  unsigned int newlines=0;
  do {
    if( c == '\n' ) newlines++;
    c = fgetc(file);
  } while( c != EOF );
  fseek(file, current, SEEK_SET);
  return newlines;
}

void goto_line(FILE* file, unsigned int line) {
  char c=0x00;
  unsigned int newlines=0;
  fseek(file, 0, SEEK_SET);
  do {
    if( c == '\n' ) newlines++;
    c = fgetc(file);
  } while( c != EOF && newlines < line );
  fseek(file, -1, SEEK_CUR);
}

unsigned int get_line_size(FILE* file) {
  long current = ftell(file);
  char c=0x00;
  unsigned int chars=0;
  do {
    chars++;
    c = fgetc(file);
  } while( c != EOF && c != '\n' );
  fseek(file, current, SEEK_SET);
  return chars;
}

Quote* get_random_quote(FILE* file) {

    unsigned int num_quotes = num_lines(file) - 1;
    goto_line(file, (rand() % num_quotes) + 1);

    long start_of_line = ftell(file);
    // allocate memory
    Quote* quote = malloc(sizeof(Quote));
    unsigned int line_size = get_line_size(file);
    quote->text = malloc(line_size);
    quote->source = malloc(line_size);

    // read line
    fscanf(file, "%d,", &quote->sourceType);
    if(quote->sourceType != Unknown) {
        fscanf(file, "%[^\n,],", quote->source);
        fscanf(file, "%[^\n]", quote->text);
    } else {
        fscanf(file, ",%[^\n]\n", quote->text);
    }
    return quote;
}

void quote_free(Quote* quote) {
    free(quote->text);
    free(quote->source);
    free(quote);
}

int main(int argc, char** argv) {

    srand(time(0));
    if( argc < 2 ) {
        printf("usage: quote FILE\n");
        return 1;
    }

    FILE* file = NULL;
    if(!( file = fopen(argv[1], "rt"))) {
        return 1;
    }

    Quote* quote = get_random_quote(file);
    printf("\"%s\"", quote->text);
    switch(quote->sourceType) {
        case Unknown:
            printf(" - Unknown\n");
            break;
        case Book:
            printf(" - %s (Book)\n", quote->source);
            break;
        case Person:
            printf(" - %s\n", quote->source);
            break;
    }
    quote_free(quote);
   
    fclose(file);

    return 0;
}
