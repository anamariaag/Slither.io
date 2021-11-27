//
// Created by Ana Maria on 26/11/2021.
//

#include "raylib.h"

#ifndef EXPERIMENTS_LISTS_H

typedef struct node Node;
typedef struct list List;

List *newList();
void addElement(List *list,void* value);
void removeLastElement(List *list);
void* getElement(List* list,int index);
int getSize(List *gusano);

Node *getHead(List *list);
Node *getNext(Node* focusNode);
void *getValue(Node *focusNode);

void updateListaP(List* posiciones, Vector2 mouse);

#define EXPERIMENTS_LISTS_H

#endif //EXPERIMENTS_LISTS_H
