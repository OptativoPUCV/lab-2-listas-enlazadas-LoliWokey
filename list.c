#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() 
{
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL; 
    return list;
}

void * firstList(List * list) {
    if (list->head == NULL || list == NULL){
        return NULL;
    }
    list->current = list->head;
    return list->head->data;
}

void * nextList(List * list) {
    if (list->current == NULL || list == NULL || list->current->next == NULL){
        return NULL;
    }
    list->current = list->current->next;

    return list->current->data;
}

void * lastList(List * list) {
    if(list == NULL || list->head == NULL){
        return NULL;
    }
    Node* aux = list->head;
    while (aux->next != NULL ){
        aux = aux->next;
    }
    list->current = aux;

    return list->current->data;
}

void * prevList(List * list) {
    if (list->head == NULL || list == NULL || list->current == list->head || list->current == NULL){
        return NULL;
    }
    Node* aux = list->head;
    while (aux->next != list->current){ 
        aux = aux->next;
    }
    list->current = aux;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node * new = createNode(data);
    new->prev = NULL;
    new->next = list->head;
    if(list->head) {
        list->head->prev = new;
    } else {
        list->tail = new;
    }
    list->head = new;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if(list->current == NULL || list == NULL) {
        return;
    }
    Node * new = createNode(data);
    Node * aux = list->current->next;
    new->prev = list->current;
    new->next = aux;
    list->current->next = new;
    if(aux != NULL) {
        aux->prev = new;
    } else {
        list->tail = new;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list->current == NULL || list == NULL) {
        return NULL;
    }
    Node * aux = list->current;
    void * data = aux->data;
    if (aux->prev != NULL) {
        aux->prev->next = aux->next;
    } else {
        list->head = aux->next;
    }
    if (aux->next != NULL) {
        aux->next->prev = aux->prev;
    } else {
        list->tail = aux->prev;
    }
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
