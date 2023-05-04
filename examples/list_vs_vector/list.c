#include "list.h"

#include <stdlib.h>
#include <string.h>

List* list_create(unsigned int data_len) {

    List* list = malloc(sizeof(List));
    list->data_len = data_len;
    list->end = list->start = NULL;
    list->list_len = 0;
    return list;
}

void list_free(List* list) {
    for(Node* node = list->start; node;) {
        Node* next = node->next;
        free(node->data);
        free(node);
        node = next;
    }
    free(list);
}

void* list_get(List* list, unsigned int idx) {

    Node* node = list->start;
    for(unsigned int i = 0; node && i < idx; i++) {
        node = node->next;    
    }
    return node ? node->data : NULL;
}

Node* list_search(List* list, void* data, int (*equal)(void*,void*)) {
    for(Node* node = list->start; node; node = node->next) {
        if(equal(data, node->data)) return node;
    }
    return NULL;
}

List* list_append_node(List* list, Node* node, unsigned int data_len) {
    if(!list) list = list_create(data_len);
    if(list->end) {
        list->end->next = node;
        node->prev = list->end;
        list->end = node;
    } else {
        list->end = node;
        list->start = node;
    }
    list->list_len++;
    return list;
}

List* list_append(List* list, void* new_data, unsigned int data_len) {
    if(!list) list = list_create(data_len);
    Node* node = malloc(sizeof(Node));
    node->data = malloc(list->data_len);
    node->next = NULL;
    memcpy(node->data, new_data, list->data_len);
    list_append_node(list, node, data_len);
    return list;
}

void list_remove_node(List* list, Node* node) {
    if(!list->list_len) return;
    if(list->start == node) list->start = node->next;
    if(list->end == node) list->end = node->prev;
    if(node->next) node->next->prev = node->prev;
    if(node->prev) node->prev->next = node->next;
    list->list_len--;
}

void list_remove(List* list, void* data, int (*equal)(void*,void*)) {
    Node* node = list_search(list, data, equal);
    list_remove_node(list, node);
}

void list_print(List* list, void (*print)(void* element)) {
    for(Node* node = list->start; node; node = node->next) {
        print(node->data);
    }
}
