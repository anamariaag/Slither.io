#include "raylib.h"
#include "slitherio.h"
#include "lists.h"

    int main() {
        int play=0;
        int letter=0;
        char player[maxInputChars]="\0";
        InitWindow(screenWidth, screenHeight, "Sliter.io -- Ana y Valeria");

        SetTargetFPS(30);
        //--------------------------------------------------------------------------------------

        Color foodsColores[nFood];
        Vector2 randomCirclesCentro[nFood];//centro
        Vector2 randomCirclesTodo[nFood];//toda la pantalla
        inicializarFood(foodsColores,randomCirclesCentro,randomCirclesTodo,nFood);

        Vector2 pInicial = { 100.0f, 100.0f };
        Vector2 initialPositions[valorInicial];
        initialPositions[0] = pInicial;
        List *posiciones = newList();
        List *gusano = newList();
        inicializarBloque(initialPositions,gusano);
        inicializarPosiciones(posiciones,initialPositions,pInicial);

        Vector2 randomPosF[nGusanos][valorInicial];
        List* fGusano[nGusanos];
        List* fGusanoPos[nGusanos];
        int randomSizes[nGusanos];
        inicializarFakeGusanos(fGusano,fGusanoPos,randomPosF);

        Camera2D camera;
        initCamera(&camera,gusano);


        //TARGET HACIA DONDE SE MUEVEN FAKE GUSANOS
        Vector2 fakeGusanoTarget[nGusanos];
        for(int i=0;i<nGusanos;i++){
            fakeGusanoTarget[i]=getRandomPosTodo();
        }

        // Main game loop
        while (!WindowShouldClose())
        {
            // Update
            //----------------------------------------------------------------------------------
            // TODO: Update your variables here

            //UPDATE GUSANO
            updateListaP(posiciones, mouseMovement(GetMousePosition(),posiciones));
            updateGusano(gusano,posiciones);


            //UPDATE FAKE GUSANOS
            for(int i =0; i<nGusanos;i++){
                updateListaP(fGusanoPos[i],updatePosFakeGusano(fGusanoPos[i],&fakeGusanoTarget[i]));
                updateGusano(fGusano[i],fGusanoPos[i]);
                fakeGusanoFollowFood(fGusano[i], fGusanoPos[i], randomCirclesTodo, randomCirclesCentro,foodsColores,&fakeGusanoTarget[i]);
            }

            checkBoundaries(posiciones,gusano,&play);


            // Camera target follows player
            camera.target = (Vector2){getPosicion(gusano,1).x , getPosicion(gusano,1).y};

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


            // Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();

            if(play==0)
                starScreen(screenWidth,&letter, player);

            if(IsKeyPressed(KEY_SPACE)|| IsKeyPressed(KEY_ENTER))
                play=1;

            if(play) {
                ClearBackground(BLACK);
                BeginMode2D(camera);

                //CIRCULO DE JUEGO
                DrawCircle(0, 0, worldSize + 70,RED);
                DrawCircle(0, 0, worldSize + 20, LIGHTGRAY);

                //CUERPO GUSANO
                drawGusano(gusano);

                //CUERPO GUSANOS FAKE
                for (int j = 0; j < nGusanos; j++) {
                    drawGusano(fGusano[j]);
                }

                checkCollisionGusanos(gusano, posiciones, fGusano, fGusanoPos,&play);

                //COMIDA
                checkCollisionFood(gusano, posiciones, fGusano, fGusanoPos, randomCirclesTodo, randomCirclesCentro,foodsColores);

                //NOMBRE
                gameplayer(gusano,player);

                EndMode2D();

                //MAPA, SCORE
                gameState(gusano);
            }
            EndDrawing();
            //----------------------------------------------------------------------------------
        }
        // De-Initialization
        //FREE()--¿?
        //--------------------------------------------------------------------------------------
        CloseWindow();        // Close window and OpenGL context
        //--------------------------------------------------------------------------------------
        return 0;
    }



