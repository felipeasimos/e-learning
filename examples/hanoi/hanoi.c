#include "stack.h"
#include "vector.h"

#include <stdlib.h>

#define NUM_TOWERS 3

typedef struct {
    Stack towers[NUM_TOWERS];
    unsigned int num_disks;
    unsigned int num_moves;
} Hanoi;

Hanoi* hanoi_init(Hanoi* hanoi, unsigned int num_disks) {
    if(!hanoi) hanoi = malloc(sizeof(Hanoi));
    hanoi->num_disks = num_disks;
    for(unsigned int i = 0; i < NUM_TOWERS; i++) stack_init(&hanoi->towers[i], sizeof(int), hanoi->num_disks);
    // populate first tower
    for(unsigned int i = 0; i < hanoi->num_disks; i++) {
        unsigned int disk_size = hanoi->num_disks - i;
        stack_push(&hanoi->towers[0], &disk_size);
    }
    hanoi->num_moves = 0;
    return hanoi;
}

Hanoi* hanoi_free(Hanoi* hanoi) {
    for(unsigned int i = 0; i < NUM_TOWERS; i++) stack_free(&hanoi->towers[i]);
    return hanoi;
}

void hanoi_print(Hanoi* hanoi) {
    // print each row
    for(unsigned int i = 0; i < hanoi->num_disks; i++) {
        unsigned int disk_idx = hanoi->num_disks - i - 1;
        // print each tower
        for(unsigned int j = 0; j < NUM_TOWERS; j++) {
            Stack* tower = &hanoi->towers[j];
            if( disk_idx < tower->vector->num_elements ) {
                printf(" %u ", *(unsigned int*)vector_get(tower->vector, disk_idx));
            } else {
                printf(" | ");
            }
        }
        printf("\n");
    }
    printf("number of moves: %d\n-----------------\n", hanoi->num_moves);
}

int hanoi_win(Hanoi* hanoi) {
    Stack* last_tower = &hanoi->towers[NUM_TOWERS-1];
    if(stack_len(last_tower) != hanoi->num_disks) return 0;
    for(unsigned int i = 0; i < hanoi->num_disks; i++) {
        if(*(unsigned int*)vector_get(last_tower->vector, i) != hanoi->num_disks - i) return 0;
    }
    return 1;
}

int hanoi_check_move(Hanoi* hanoi, unsigned int from, unsigned int to) {
    return from != to && to < NUM_TOWERS && from < NUM_TOWERS &&
        stack_len(&hanoi->towers[from]) &&
        (
            (
                stack_peek(&hanoi->towers[from]) &&
                !stack_peek(&hanoi->towers[to])
            )
            ||
            (
                *(unsigned int*)stack_peek(&hanoi->towers[from]) <
                *(unsigned int*)stack_peek(&hanoi->towers[to])
            )
         );
}

int main(int argc, char** argv) {
    if(argc < 2) {
        printf("usage: hanoi NUM_DISKS\n");
        return 1;
    }
    unsigned int num_disks;
    sscanf(argv[1], "%u", &num_disks);
    Hanoi* hanoi = hanoi_init(NULL, num_disks);
    while(!hanoi_win(hanoi)) {
        hanoi_print(hanoi);
        unsigned int from, to;
        printf("take from tower: ");
        scanf("%u", &from);
        printf("put on tower: ");
        scanf("%u", &to);
        if( hanoi_check_move(hanoi, from, to) ) {
            void* data = stack_pop(&hanoi->towers[from]);
            stack_push(&hanoi->towers[to], data);
            free(data);
        } else {
            hanoi->num_moves--;
        }
        hanoi->num_moves++;
    }
    printf("you win! number of moves: %u\n", hanoi->num_moves);

    free(hanoi_free(hanoi));

    return 0;
}
