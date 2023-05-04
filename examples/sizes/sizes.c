#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* name;
    unsigned int size;
} FileInfo;

unsigned int file_size(char* filename) {
    FILE* file = fopen(filename, "rb");
    if(!file) {
        printf("file '%s' not found\n", filename);
        exit(1);
    }
    unsigned int size = 0;
    for(char c = 0x00; c != EOF; c = fgetc(file), size++);
    fclose(file);
    return size;
}

int cmp(void* a, void* b) {
    if( ((FileInfo*)a)->size < ((FileInfo*)b)->size ) {
        return 1;
    } else if( ((FileInfo*)a)->size > ((FileInfo*)b)->size ) {
        return -1;
    }
    return 0;
}

int main(int argc, char** argv) {

    if( argc < 2 ) {
        printf("usage: sizes FILES\n");
        return 1;
    }

    unsigned int num_files = argc - 1;
    Vector* vector = vector_create(sizeof(FileInfo), num_files);

    for(unsigned int i = 0; i < num_files; i++) {
        FileInfo info = {
            .name = argv[i+1],
            .size = file_size(argv[i+1])
        };

        vector_insert(vector, &info, vector->num_elements);
    }
    vector_sort(vector, cmp);
    for(unsigned int i = 0; i < vector->num_elements; i++) {
        FileInfo* info = vector_get(vector, i);
        printf("%uB %s\n", info->size, info->name);
    }
    vector_free(vector);

    return 0;
}
