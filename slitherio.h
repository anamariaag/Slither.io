//
// Created by Ana Maria on 26/11/2021.
//

#include "lists.h"

#ifndef EXPERIMENTS_SLITHERIO_H

#define valorInicial 10
#define nFood 250
#define nGusanos 50
#define worldSize 3000
#define speed 5
#define screenWidth 1800
#define screenHeight 900
#define maxInputChars 10
#define growth 1
#define radioInicial 20
#define radioFindFood 100
#define radioAvoidGusano 30

typedef struct bloque Bloque;

Bloque* getBloque(List* list,int index);
Color getColor(List* gusano);
float getRadio(List* gusano);
void setRadio(List* gusano, float newValue);
void changeRadio(List *gusano);
Vector2 getPosicion(List* gusano,int index);
void setPosicion(List* gusano, int index, Vector2 pos);
void setPosicionGusano(List* posiciones, int index,Vector2 pos);
Bloque *newBloque(Color color,int n,float radio);
Vector2 *newPos(float x, float y);
void inicializarBloque(Vector2 initialPositions[valorInicial], List *gusano);
void inicializarPosiciones(List *posiciones,Vector2 initialPositions[valorInicial],Vector2 pInicial);
void inicializarFakeGusanos(List *fakeGusanos[],List *posicionesFakeGusanos[],Vector2 randomPos[nGusanos][valorInicial]);

Vector2 mouseMovement(Vector2 mouse, List *posiciones);
void checkBoundaries(List *posiciones, List *gusano, int *play);
void updateGusano(List *gusano,List* posiciones);
Vector2 updatePosFakeGusano(List* posiciones, Vector2 *pos);
void checkCollisionGusanos(List *gusano, List *posiciones, List* fakeGusanos[], List *fakeGusanosPos[],int *play);
void fakeGusanoFollowFood(List* fakeGusanos,Vector2 randomPosTodo[],Vector2 randomPosCentro[],Vector2 *target);
void fakeGusanoAvoidGusanos(List* fakeGusanos[],List* fakeGusano, Vector2 *target,int i, List *gusano);

void gameState(List *gusano);
void gameplayer(List *gusano, char player[]);

void checkCollisionFood(List *gusano, List *posiciones, List* fakeGusanos[], List *fakeGusanosPos[],Vector2 randomPosTodo[],Vector2 randomPosCentro[],Color random[]);
void inicializarFood(Color foods[],Vector2 positionsCentro[], Vector2 positionsAll[],int n);

Vector2 getRandomPosTodo();
Vector2 getRandomPosAfueras();
Vector2 getRandomPosCentro();
Color getRandomColor();
void initCamera(Camera2D *camera, List *gusano);
void starScreen(int sw,int *letterCount,char player[]);
void drawGusano(List *gusano);
int compareVector2(Vector2 a, Vector2 b);
Vector2 Vector2Transformacion(Vector2 n);


#define EXPERIMENTS_SLITHERIO_H

#endif //EXPERIMENTS_SLITHERIO_H
