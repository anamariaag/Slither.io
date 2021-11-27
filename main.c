#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "raymath.h"
#include "slitherio.h"

#define valorInicial 10
#define nFood 400
#define nGusanos 20
#define worldSize 6000
#define speed 7


    int main() {
        printf("Hello, World!\n");
        int screenWidth = 1800;
        int screenHeight = 900;

        InitWindow(screenWidth, screenHeight, "Sliter.io -- Ana y Valeria");


        Color foods[nFood];
        Vector2 randomCirclesCentro[nFood];//centro
        Vector2 randomCirclesTodo[nFood];//toda la pantalla
        foodPrep(foods,randomCirclesCentro,randomCirclesTodo,nFood);

        Vector2 pInicial = { 100.0f, 100.0f };
        Vector2 initialPositions[valorInicial];
        initialPositions[0] = pInicial;


        SetTargetFPS(30);               // Set our game to run at 60 frames-per-second
        //--------------------------------------------------------------------------------------


        List *posiciones = newList();
        List *gusano = newList();
        inicializarBloque(initialPositions,gusano);
        inicializarPosiciones(posiciones,initialPositions,pInicial);


        Vector2 randomPosF[nGusanos][valorInicial];
        List* fGusano[nGusanos];
        List* fGusanoPos[nGusanos];
        inicializarFakeGusanos(fGusano,fGusanoPos,randomPosF);


        Camera2D camera = { 0 };
        camera.target = (Vector2){getPosicion(gusano,1).x + 20.0f, getPosicion(gusano,1).y + 20.0f };
        camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;

        Vector2 fakeGusanoPos[nGusanos];
        for(int i=0;i<nGusanos;i++){
            fakeGusanoPos[i]=getRandomPosTodo();
        }

        // Main game loop
        while (!WindowShouldClose())    // Detect window close button or ESC key
        {
            // Update
            //----------------------------------------------------------------------------------
            // TODO: Update your variables here
            updateListaP(posiciones, mouseMovement(GetMousePosition(),posiciones));//agrega nueva posicion mouse y quita ultima
            updateGusano(gusano,posiciones);//copia lista de posiciones a posiciones de los bloques

            for(int i =0; i<nGusanos;i++){
                updateListaP(fGusanoPos[i],updatePosFakeGusano(fGusanoPos[i],&fakeGusanoPos[i]));
                updateGusano(fGusano[i],fGusanoPos[i]);
            }


            // Camera target follows player
            camera.target = (Vector2 ){getPosicion(gusano,1).x , getPosicion(gusano,1).y};

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

            //CIRCULO DE JUEGO
            DrawCircle(0, 0, worldSize+20, LIGHTGRAY);

            //CUERPO GUSANO
            for(int i=0;i<getSize(gusano);i++){
                DrawCircleV(getPosicion(gusano,i), (getRadio(gusano,i))+2, DARKGRAY);
                DrawCircleV(getPosicion(gusano,i), getRadio(gusano,i), getColor(gusano,i));
            }

            //CUERPO GUSANO FAKE
            for(int j=0;j<nGusanos;j++){
                for(int i=0;i<getSize(fGusano[j]);i++){
                    DrawCircleV(getPosicion(fGusano[j],i), (getRadio(fGusano[j],i))+2, DARKGRAY);
                    DrawCircleV(getPosicion(fGusano[j],i), getRadio(fGusano[j],i), getColor(fGusano[j],i));
                }
            }


            //COMIDA
            checkCollisionFood(gusano, posiciones, fGusano,fGusanoPos,randomCirclesTodo,randomCirclesCentro,foods);

            gameplayer(gusano);

            EndMode2D();

            gameState(gusano);

            EndDrawing();
            //----------------------------------------------------------------------------------
        }
        // De-Initialization
        //--------------------------------------------------------------------------------------
        CloseWindow();        // Close window and OpenGL context
        //--------------------------------------------------------------------------------------
        return 0;
    }



