#include "queue.h"
#include "vector.h"

#include <stdlib.h>
#include <string.h>

Queue* queue_init(Queue* queue, unsigned int data_len, unsigned int capacity) {
    if(!queue) queue = malloc(sizeof(Queue));
    queue->vector = vector_create(data_len, capacity);
    queue->head = queue->tail = queue->num_elements = 0;
    return queue;
}

void* queue_pop(Queue* queue) {
    if(!queue->num_elements) return NULL;
    // queue increases towards tail
    void* data = malloc(queue->vector->element_size);
    memcpy(data, vector_get(queue->vector, queue->head), queue->vector->element_size);
    queue->head++;
    queue->num_elements--;
    return data;
}

void queue_push(Queue* queue, void* data) {

    // if tail is at the end of the vector and we can move the items back
    if(queue->tail == queue->vector->capacity-1 && queue->head) {
        memmove(
            queue->vector->vec,
            vector_get(queue->vector, queue->head),
            queue->num_elements * queue->vector->element_size
        );
        queue->head = 0;
        queue->tail = queue->num_elements - 1;
    }
    // if there are no elements, don't update queue->tail
    if(queue->num_elements) queue->tail++;
    queue->num_elements++;
    queue->vector = vector_insert(queue->vector, data, queue->tail);
}

void* queue_peek(Queue* queue) {
    if(!queue->num_elements) return NULL;
    return vector_get(queue->vector, queue->head);
}

unsigned int queue_len(Queue* queue) {
    return queue->num_elements;
}

void queue_free(Queue* queue) {
    vector_free(queue->vector);
}

void queue_print(Queue* queue, void (*print)(void* element)) {
    for(unsigned int i = 0; i < queue->num_elements; i++) {
        print(vector_get(queue->vector, i + queue->head));
    }
}
