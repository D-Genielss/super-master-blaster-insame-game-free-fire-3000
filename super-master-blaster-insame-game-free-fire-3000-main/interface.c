#include "../include/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
    
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
void raylib(){
    // Inicialização
    const int screenWidth = 1600;
    const int screenHeight = 900;
    bool TelaComecar = false;

    //Botao Começar a Jogar
    int XL_jogar = 400;
    int YA_Jogar = 80;
    int X_Jogar = (screenWidth/2)-200;
    int Y_Jogar = 400;
    Rectangle B_jogar = {X_Jogar,Y_Jogar,XL_jogar,YA_Jogar};

    //botoes dificuldade
    Rectangle B_D1 = {360,410,440,120};
    bool TelaD1 = false;
    Rectangle B_D2 = {860,410,440,120};
    bool TelaD2 = false;
    InitWindow(screenWidth, screenHeight, "TERMO 1.0 ");
    SetTargetFPS(60);

// Loop principal do jogo
while (!WindowShouldClose()){
    // Atualizar
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        Vector2 mousePosition = GetMousePosition();

        if (CheckCollisionPointRec(mousePosition,B_jogar)){
            TelaComecar = true;
        }
    }//testa botoes

// Desenha
    BeginDrawing();

        ClearBackground(BLACK);
            
//Menu Principal
        DrawText("super-master-blaster-insame-game-Termo-3000",200,200,50 ,WHITE);           

        //Botão Jogar
        DrawRectangle(X_Jogar,Y_Jogar,XL_jogar,YA_Jogar,DARKPURPLE);
        DrawText("Iniciar",(screenWidth/2)-100,Y_Jogar + 20,40 ,WHITE);
            
// Tela Comecar
        if(TelaComecar == true){

            while(!WindowShouldClose()){

                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    Vector2 mousePosition = GetMousePosition();

                    if (CheckCollisionPointRec(mousePosition,B_D1) && TelaComecar == false){
                        TelaD1 = true;
                    }
                    if (CheckCollisionPointRec(mousePosition,B_D2) && TelaComecar == false){
                        TelaD2 = true;
                    }
                }//testa botao telas dificuldades
   
                BeginDrawing();

                ClearBackground(BLACK);

                DrawText("ESCOLHA A DIFICULDADE",450,200,50 ,WHITE);
            //dificuldade 1
                DrawRectangle(360,410,440,120,GREEN);
                DrawRectangle(370,420,420,100,BLACK);
                DrawText("DIFICULDADE 1",380,445,50 ,GREEN);
//tela dificulade 1 /game facil                 
                if(TelaD1 == true){
                    while(!WindowShouldClose()){

                  int key = GetCharPressed();
                    int letterCount = 0;
                    char palavra[5];
                                          
                        if ((key >= 32) && (key <= 125) && (letterCount < 4)){
                        palavra[letterCount] = (char)key;
                        palavra[letterCount+1] = '\0';
                        letterCount++;
                        }

                        if (IsKeyPressed(KEY_BACKSPACE)){
                            if (letterCount > 0){
                                letterCount--;
                                palavra[letterCount] = '\0';
                            }
                        }
                
                        BeginDrawing();

                            ClearBackground(BLACK);
                            DrawText("JOGO DIFICULDADE 1",450,200,50 ,GREEN);

                            //DrawText(palavra, 460, 400, 40, GREEN);
                            DrawRectangle(450, 540, 200, 2, GREEN);

                        EndDrawing();
                    if (!WindowShouldClose()){TelaD1 = false;}//if fechar tela
                    }//while Tela dificuldade 1
                }//if Tela dificuldade 1

        //dificuldade 2
                DrawRectangle(860,410,440,120,YELLOW);
                DrawRectangle(870,420,420,100,BLACK);
                DrawText("DIFICULDADE 2",880,445,50 ,YELLOW);
//tela dificuldade 2 /game medio
                if(TelaD2 == true){
                    while(!WindowShouldClose()){
                        BeginDrawing();

                        ClearBackground(BLACK);
                        DrawText("JOGO DIFICULDADE 2",450,200,50 ,YELLOW);

                        EndDrawing();
                    if (!WindowShouldClose()){TelaD2 = false;}//if fechar tela
                    }//while Tela dificuldade 2
                }//if tela dificuldade 2
                        
                EndDrawing();
                    
                if (!WindowShouldClose()){TelaComecar = false;}//if fechar tela começar
            }//while tela começar
        }//if tela começar
    EndDrawing();
}//loop principal
CloseWindow();
}//reylib
