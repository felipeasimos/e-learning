#pragma once

typedef struct Node {
    struct Node* next;
    struct Node* prev;
    void* data;
} Node;

typedef struct List {
    struct Node* start;
    struct Node* end;
    unsigned int list_len;
    unsigned int data_len;
} List;

List* list_create(unsigned int data_len);
void list_free(List*);
void* list_get(List*, unsigned int idx);

Node* list_search(List* list, void* data, int (*equal)(void*,void*));

List* list_append_node(List* list, Node* node, unsigned int data_len);
List* list_append(List* list, void* new_data, unsigned int data_len);
void list_remove_node(List* list, Node* node);
void list_remove(List* list, void* data, int (*equal)(void*,void*));

void list_print(List*, void (*print)(void* element));
