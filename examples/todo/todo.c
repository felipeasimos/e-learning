#include "queue.h"

#include <stdlib.h>
#include <string.h>

#define TASK_LEN 4096

typedef enum {
    EXIT=0,
    DONE=1,
    NEW=2,
} Choice;

void task_print(void* task) {
    unsigned int n = strlen(*(char**)task);
    printf("* %s (%u)\n", *(char**)task, n);
}

int main() {

    Queue queue;
    queue_init(&queue, sizeof(char*), 1);

    Choice choice;
    do {
        queue_print(&queue, task_print);
        printf("%d) exit\n%d) mark as done\n%d) add new task\n", EXIT, DONE, NEW);
        scanf("%u", &choice);
        switch(choice) {
            case EXIT:
                break;
            case DONE: {
                char** task_ptr = (char**)queue_pop(&queue);
                // printf("task removed from list: %s\n", *(char**)task_ptr);
                free(*task_ptr);
                free(task_ptr);
                break;
            }
            case NEW: {
                char new[TASK_LEN-1];
                printf("new task: ");
                scanf(" %[^\n]s", new);
                unsigned int new_len = strlen(new);
                char* task = malloc(new_len+1);
                strncpy(task, new, new_len+1);
                queue_push(&queue, &task);
                break;
            }
        }
    } while(choice != EXIT);

    for(unsigned int i = queue.head; i <= queue.tail; i++) {
        free(*(char**)vector_get(queue.vector, i));
    }

    return 0;
}
