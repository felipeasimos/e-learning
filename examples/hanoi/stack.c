#include "stack.h"
#include "vector.h"

#include <stdlib.h>
#include <string.h>

Stack* stack_init(Stack* stack, unsigned int data_len, unsigned int capacity) {
    if(!stack) stack = malloc(sizeof(Stack));
    stack->vector = vector_create(data_len, capacity);
    return stack;
}

Stack* stack_free(Stack* stack) {
    vector_free(stack->vector);
    return stack;
}

void* stack_pop(Stack* stack) {

    if(!stack || !stack->vector->num_elements) return NULL;
    void* data = malloc(stack->vector->element_size);
    memcpy(data, vector_get(stack->vector, stack->vector->num_elements-1), stack->vector->element_size);
    stack->vector = vector_remove(stack->vector, stack->vector->num_elements);
    return data;
}

void stack_push(Stack* stack, void* data) {
    stack->vector = vector_insert(stack->vector, data, stack->vector->num_elements);
}

void* stack_peek(Stack* stack) {
    if(!stack->vector->num_elements) return NULL;
    return vector_get(stack->vector, stack->vector->num_elements-1);
}

unsigned int stack_len(Stack* stack) {
    return stack->vector->num_elements;
}
