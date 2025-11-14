/**
 * @file hello.c
 * @author Muriel Godoi (muriel@utfpr.edu.br)
 * @brief Hello World in Raylib 5.5
 * @version 0.1
 * @date 2024-11-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../include/raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
void raylib(){
    // Inicialização
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1600;
    const int screenHeight = 900;
    bool TelaCadastro = false;

    //Botao Menu cadastro
        //tamanho botão 
        int XL_cadastro = 400;
        int YA_cadastro = 80;
        //localizacao do botao 
        int X_cadastro = (screenWidth/2)-200;
        int Y_cadastro = 600;
        Rectangle B_cadastro = {X_cadastro,Y_cadastro,XL_cadastro,YA_cadastro};

    InitWindow(screenWidth, screenHeight, "TERMO 1.0");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Loop principal do jogo
    while (!WindowShouldClose()){
        // Atualizar
        //----------------------------------------------------------------------------------
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            // Pega a posição do mouse no momento do clique
            Vector2 mousePosition = GetMousePosition();
            // Verifica a colisão entre o retangulo
            if (CheckCollisionPointRec(mousePosition,B_cadastro)){
                TelaCadastro = true;
            }
        }
        //----------------------------------------------------------------------------------

        // Desenha
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            //Menu Principal

                DrawRectangle(X_cadastro,Y_cadastro,XL_cadastro,YA_cadastro,DARKPURPLE);
                DrawText("Cadastrar",(screenWidth/2)-100,Y_cadastro + 20,40 ,WHITE);
                if(TelaCadastro == true){
                    while (!WindowShouldClose()){
                        BeginDrawing();
                            ClearBackground(BLACK);

                            
                            if(!WindowShouldClose()){
                                TelaCadastro = false;
                            }


                        EndDrawing();
                    }                   
                }//Tela cadastro
                    
                    //DrawRectangle(screenWidth/2,0,2,450,WHITE);Linha no meio (questao de medida)

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // Desinicialização
    //--------------------------------------------------------------------------------------
    CloseWindow();         // Fecha a janela e o contexto OpenGL
    //--------------------------------------------------------------------------------------

}