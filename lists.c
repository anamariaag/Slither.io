//
// Created by Ana Maria on 26/11/2021.
//
#include <stdlib.h>
#include <stdio.h>
#include "lists.h"
#include "raylib.h"


struct node{
    void* value;
    struct node *next;
};

struct list{
    Node* head;
    int size;
};


List *newList(){//regresa el primer nodo de una lista
    List *newHead= malloc(sizeof(List));
    newHead->size=0;
    newHead->head=NULL;
    return newHead;
}

void* getElement(List* list, int index){
    Node *focusNode=list->head;
    for(int i=0;i<index;i++){
        focusNode=focusNode->next;
    }
    return focusNode->value;
}

void addElement(List *list,void* value){
    Node *new =malloc(sizeof(Node));
    new->value=value;
    new->next=list->head;
    list->head=new;
    list->size++;
}

void removeLastElement(List *list){
    Node *focusNode = list->head;
    while (focusNode->next->next!= NULL) {
        focusNode = focusNode->next;
    }
    Node *elementDelete = focusNode->next;
    focusNode->next = NULL;
    free(elementDelete);
    list->size--;
}

int getSize(List *list) {
    return list->size;
}

Node *getHead(List *list){
    return list->head;
}

Node *getNext(Node* focusNode){
    return focusNode->next;
}

void *getValue(Node *focusNode){
    return focusNode->value;
}

//agrega posicion a la cabeza de la lista y recorre todas las demas
void updateListaP(List* posiciones,Vector2 mouse){
    Node* focus=posiciones->head;
    Vector2 *vec=focus->value;
    Vector2 tmp1=*vec;
    Vector2 tmp2;
    *vec=mouse;
    while(focus->next!=NULL){
        focus=focus->next;
        vec=focus->value;
        tmp2=*vec;
        *vec=tmp1;

        if(focus->next==NULL){
            break;
        }

        focus=focus->next;
        vec=focus->value;
        tmp1=*vec;
        *vec=tmp2;
    }
}