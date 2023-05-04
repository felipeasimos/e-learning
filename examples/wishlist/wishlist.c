#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* link;
    unsigned int price;
} Item;

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

Item* get_list_items(FILE* file, unsigned int* num_items) {
    *num_items = num_lines(file) - 1;
    Item* items = calloc(*num_items, sizeof(Item));
    for(unsigned long i = 0; i < *num_items; i++) {
        goto_line(file, i+1);
        Item* item = &items[i];
        item->link = malloc(1000);
        item->name = malloc(1000);
        fscanf(file, "%[^\n,],%u,%[^\n,]\n", item->name, &item->price, item->link);
    }
    return items;
}

void items_free(Item* items, unsigned int items_size) {

    for(unsigned int i = 0; i < items_size; i++) {
        free(items[i].name);
        free(items[i].link);
    }
    free(items);
}

int cmp(const void* a, const void* b) {

    if( ((Item*)a)->price < ((Item*)b)->price) {
        return -1;
    } else if(((Item*)a)->price > ((Item*)b)->price) {
        return 1;
    }
    return 0;
}

int main(int argc, char** argv) {

    if( argc < 2 ) {
        printf("usage: wishlist FILE\n");
        return 1;
    }

    FILE* file = NULL;
    if(!(file = fopen(argv[1], "rt"))) {
        return 1;
    }

    // get items
    unsigned int num_items = 0;
    Item* items = get_list_items(file, &num_items);

    // sort
    qsort(items, num_items, sizeof(Item), cmp);

    // print
    for(unsigned int i = 0; i < num_items; i++) {
        Item* item = &items[i];
        printf("%s (R$ %.2f) - %s\n", item->name, ((float)item->price) / 100, item->link);
    }

    // free resources (file/memory)
    items_free(items, num_items);
    fclose(file);
    return 0;
}
