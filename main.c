#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "raymath.h"

#define valorInicial 5
#define nFood 400

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
Vector2 mouseProporcional(Vector2 n);
//Vector2 Vector2Unitario(Vector2 n);
void updateGusano(List *gusano,List* posiciones);


void food(List *gusano,List *posiciones,Vector2 *randomPos, Color randomColor);
void foodPrep(Color foods[],Vector2 positions[],int n);

Vector2 getRandomVector2();
Color getRandomColor();

List *newList();
void addElement(List *list,void* value);
void removeLastElement(List *list);
void* getElement(List* list,int index);
int getSize(List *gusano);


struct node{
    void* value;
    struct node *next;
};

struct list{
    Node* head;
    int size;
};

struct bloque{
    Color color;
    Vector2 posicion;
    float alpha;
    float radio;
};

    int main() {
        printf("Hello, World!\n");
        int screenWidth = 1800;
        int screenHeight = 900;

        InitWindow(screenWidth, screenHeight, "Sliter.io -- Ana y Valeria");

        Color foods[nFood];
        Vector2 randomCircles[nFood];
        foodPrep(foods,randomCircles,nFood);


        Vector2 pInicial = { 100.0f, 100.0f };
        Vector2 initialPositions[valorInicial];
        initialPositions[0] = pInicial;

        SetTargetFPS(30);               // Set our game to run at 60 frames-per-second
        //--------------------------------------------------------------------------------------
        List *posiciones = newList();
        List *gusano = newList();

        inicializarBloque(initialPositions,gusano);
        inicializarPosiciones(posiciones,initialPositions,pInicial);

        Camera2D camera = { 0 };
        camera.target = (Vector2){getPosicion(gusano,1).x + 20.0f, getPosicion(gusano,1).y + 20.0f };
        camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;


        // Main game loop
        while (!WindowShouldClose())    // Detect window close button or ESC key
        {
            // Update
            //----------------------------------------------------------------------------------
            // TODO: Update your variables here
            updateListaP(posiciones, mouseMovement(GetMousePosition(),posiciones));//agrega nueva posicion mouse y quita ultima
            updateGusano(gusano,posiciones);//copia lista de posiciones a posiciones de los bloques

            // Camera target follows player
            camera.target = (Vector2 ){getPosicion(gusano,1).x + 20.0f, getPosicion(gusano,1).y + 20.0f };


            /* NOTA: vamos a cambiar el zoom conforme el gusano crezca
            // Camera zoom controls
            camera.zoom += ((float)GetMouseWheelMove()*0.05f);

            if (camera.zoom > 3.0f) camera.zoom = 3.0f;
            else if (camera.zoom < 0.1f) camera.zoom = 0.1f;

            // Camera reset (zoom and rotation)
            if (IsKeyPressed(KEY_R))
            {
                camera.zoom = 1.0f;
                camera.rotation = 0.0f;
            }*/

            //----------------------------------------------------------------------------------
            // Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();

            ClearBackground(RAYWHITE);
            BeginMode2D(camera);

            DrawCircle(screenWidth/2, screenHeight/2, 2000, LIGHTGRAY);


            DrawLine((int)camera.target.x, -screenHeight*10, (int)camera.target.x, screenHeight*10, BLACK);
            DrawLine(-screenWidth*10, (int)camera.target.y, screenWidth*10, (int)camera.target.y, BLACK);

            for(int i=0;i<getSize(gusano);i++){
                DrawCircleV(getPosicion(gusano,i), getRadio(gusano,i), getColor(gusano,i));
            }

            for(int i =0; i<nFood;i++){
                food(gusano,posiciones, randomCircles+i, foods[i]);
            }
            printf("[%f,%f]\n",GetMousePosition().x,GetMousePosition().y);

            EndMode2D();



            DrawText("Slither.io Prueba 626", 100, 100, 40, BLACK);

            //NOTA: Agregar mapa que muestre donde se encuentra el gusano, usar proporciones

            EndDrawing();
            //----------------------------------------------------------------------------------
        }
        // De-Initialization
        //--------------------------------------------------------------------------------------
        CloseWindow();        // Close window and OpenGL context
        //--------------------------------------------------------------------------------------
        return 0;
    }

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

Bloque *newBloque(Color color,int n){
    Bloque* new=malloc(sizeof(Bloque));
    new->color=color;
    new->alpha=1;
    new->posicion=(Vector2){ 100+5*n, 100+5*n};
    new->radio=20;
    return new;
}

Vector2 *newPos(float x, float y){
    Vector2 *new=malloc(sizeof (Vector2));
    new->x=x;
    new->y=y;
    return new;
    }




Vector2 getRandomVector2(){
        Vector2 n = {GetRandomValue(-2000,2000), GetRandomValue(-2000,2000)};
        return n;
    }

Color getRandomColor(){
    Color random1=(Color){ GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };
    return random1;
}




Bloque* getBloque(List* list,int index){
    Node *focusNode = list->head;//index 0
    for (int i = 0; i < index; i++) {
        focusNode = focusNode->next;
    }
    Bloque *ptr = focusNode->value;
    return ptr;
}

Color getColor(List* gusano, int index){
    Node *focusNode = gusano->head;//index 0
    for (int i = 0; i < index; i++) {
        focusNode = focusNode->next;
    }
    Bloque *ptr = focusNode->value;
    return ptr->color;
}

float getRadio(List* gusano,int index){
    Node *focusNode = gusano->head;//index 0
    for (int i = 0; i < index; i++) {
        focusNode = focusNode->next;
    }
    Bloque *ptr = focusNode->value;
    return ptr->radio;
}

Vector2 getPosicion(List* gusano,int index){
    Node *focusNode = gusano->head;//index 0
    for (int i = 0; i < index; i++) {
        focusNode = focusNode->next;
    }
    Bloque *ptr = focusNode->value;
    return ptr->posicion;
}

void setPosicion(List* gusano, int index,Vector2 pos){
    Node *focusNode = gusano->head;//index 0
    for (int i = 0; i < index; i++) {
        focusNode = focusNode->next;
    }
    Bloque *ptr = focusNode->value;
    ptr->posicion=pos;
    }



void inicializarBloque(Vector2 initialPositions[valorInicial], List *gusano){
    Color random1=(Color){ GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };
    for(int i = 0; i<valorInicial;i++){//inicializar bloque
        addElement(gusano, newBloque(random1,i));
    }
}

void inicializarPosiciones(List *posiciones, Vector2 initialPositions[valorInicial],  Vector2 pInicial){
    for(int i = 0; i<valorInicial;i++){//inicializar posiciones
        initialPositions[i].x = pInicial.x + i;
        initialPositions[i].y = pInicial.y + i;
        addElement(posiciones, initialPositions+i);
    }

}

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

Vector2 mouseMovement(Vector2 mouse,List *posiciones){
    //Vector2 direction = Vector2Multiply(*((Vector2*)getElement(posiciones,0)),Vector2Unitario(mouse));
    Vector2 direction=Vector2MoveTowards(*((Vector2*)getElement(posiciones,0)), mouseProporcional(mouse),100);
    return direction;
}

Vector2 mouseProporcional(Vector2 n){
    Vector2 result={(n.x)*2.2,n.y*4.4};
    return result;
}

/*Vector2 Vector2Unitario(Vector2 n){
    Vector2 result={n.x/Vector2Length(n),n.y/Vector2Length(n)};
    return result;
}*/
void updateGusano(List *gusano,List *posiciones){
    for(int i =0; i<gusano->size;i++){
        setPosicion(gusano,i,*(Vector2*)getElement(posiciones,i));
    }
}

void food(List *gusano,List *posiciones,Vector2 *randomPos, Color randomColor){
    if(CheckCollisionCircles(getPosicion(gusano,0), getRadio(gusano,0),*randomPos,10)){
        addElement(gusano, newBloque(getColor(gusano,0),1));
        addElement(posiciones, newPos(getPosicion(gusano, 1).x,getPosicion(gusano, 1).y));
        *randomPos=getRandomVector2();
    }
    else{
        DrawCircleV(*randomPos,10,randomColor);
    }
}

void foodPrep(Color foods[], Vector2 positions[],int n){
     for(int i=0;i<n;i++){
         foods[i]=getRandomColor();
         positions[i]=getRandomVector2();
     }
}

