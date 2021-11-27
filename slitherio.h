//
// Created by Ana Maria on 26/11/2021.
//

#ifndef EXPERIMENTS_SLITHERIO_H

#define valorInicial 10
#define nFood 400
#define nGusanos 20
#define worldSize 6000
#define speed 7

typedef struct node Node;
typedef struct list List;
typedef struct bloque Bloque;

Bloque* getBloque(List* list,int index);
Color getColor(List* gusano, int index);
float getRadio(List* gusano,int index);
Vector2 getPosicion(List* gusano,int index);
void setPosicion(List* gusano, int index, Vector2 pos);
Bloque *newBloque(Color color,int n);
Vector2 *newPos(float x, float y);
void inicializarBloque(Vector2 initialPositions[valorInicial], List *gusano);
void inicializarPosiciones(List *posiciones,Vector2 initialPositions[valorInicial],Vector2 pInicial);
void updateListaP(List* posiciones, Vector2 mouse);
Vector2 mouseMovement(Vector2 mouse, List *posiciones);
Vector2 Vector2Transformacion(Vector2 n);
void updateGusano(List *gusano,List* posiciones);
Vector2 updatePosFakeGusano(List* posiciones, Vector2 *pos);
void inicializarFakeGusanos(List *fakeGusanos[],List *posicionesFakeGusanos[],Vector2 randomPos[nGusanos][valorInicial]);
int compareVector2(Vector2 a, Vector2 b);


void gameState(List *gusano);
void gameplayer(List *gusano);

void checkCollisionFood(List *gusano, List *posiciones, List* fakeGusanos[], List *fakeGusanosPos[],Vector2 randomPosTodo[],Vector2 randomPosCentro[],Color random[]);
void foodPrep(Color foods[],Vector2 positionsCentro[], Vector2 positionsAll[],int n);

Vector2 getRandomPosTodo();
Vector2 getRandomPosCentro();
Color getRandomColor();

List *newList();
void addElement(List *list,void* value);
void removeLastElement(List *list);
void* getElement(List* list,int index);
int getSize(List *gusano);


#define EXPERIMENTS_SLITHERIO_H

#endif //EXPERIMENTS_SLITHERIO_H
