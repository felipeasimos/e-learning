#pragma once

#include "vector.h"

typedef struct {
    Vector* vector;
} Stack;

Stack* stack_init(Stack* stack, unsigned int data_len, unsigned int capacity);
Stack* stack_free(Stack* stack);

void* stack_pop(Stack* stack);
void stack_push(Stack* stack, void* data);
void* stack_peek(Stack* stack);
unsigned int stack_len(Stack* stack);
