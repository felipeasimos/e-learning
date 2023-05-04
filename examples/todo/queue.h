#pragma once

#include "vector.h"

typedef struct {
    // vector increases towards tail
    Vector* vector;
    // index of current head item
    unsigned int head;
    // index of current tail item
    unsigned int tail;
    unsigned int num_elements;
} Queue;

Queue* queue_init(Queue* queue, unsigned int data_len, unsigned int capacity);
void* queue_pop(Queue* queue);
void queue_push(Queue* queue, void* data);
void* queue_peek(Queue* queue);
unsigned int queue_len(Queue* queue);
void queue_free(Queue* queue);
void queue_print(Queue* queue, void (*print)(void* element));
