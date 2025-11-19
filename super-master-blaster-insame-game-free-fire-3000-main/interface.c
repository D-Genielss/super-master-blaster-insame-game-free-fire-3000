
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
    bool TelaComecar = false;
    //Botao Começar a Jogar
        //tamanho botão 
        int XL_jogar = 400;
        int YA_Jogar = 80;
        //localizacao do botao 
        int X_Jogar = (screenWidth/2)-200;
        int Y_Jogar = 400;
        Rectangle B_jogar = {X_Jogar,Y_Jogar,XL_jogar,YA_Jogar};

    //Botao Menu cadastro
        //tamanho botão 
        int XL_cadastro = 400;
        int YA_cadastro = 80;
        //localizacao do botao 
        int X_cadastro = (screenWidth/2)-200;
        int Y_cadastro = 600;
        Rectangle B_cadastro = {X_cadastro,Y_cadastro,XL_cadastro,YA_cadastro};
        Rectangle B_Sair_cadastro = {50,777,400,40};

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
            if (CheckCollisionPointRec(mousePosition,B_jogar)){
                TelaComecar = true;
            }
        }
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
                //nome do jogo

                DrawText("super-master-blaster-insame-game-free-fire-3000",200,200,50 ,WHITE);

                //parte Jogar
                DrawRectangle(X_Jogar,Y_Jogar,XL_jogar,YA_Jogar,DARKPURPLE);
                DrawText("Iniciar",(screenWidth/2)-100,Y_Jogar + 20,40 ,WHITE);
                if(TelaComecar == true){
                    while (!WindowShouldClose()){

                        BeginDrawing();

                            ClearBackground(BLACK);

                            if(!WindowShouldClose()){
                                TelaComecar = false;
                            }

                        EndDrawing();
                        

                    }
                }

                //Parte cadastro
                DrawRectangle(X_cadastro,Y_cadastro,XL_cadastro,YA_cadastro,DARKPURPLE);
                DrawText("Cadastrar",(screenWidth/2)-100,Y_cadastro + 20,40 ,WHITE);
                if(TelaCadastro == true){
                    while (!WindowShouldClose()){
                        //botao sair
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                            // Pega a posição do mouse no momento do clique
                            Vector2 mousePosition = GetMousePosition();
                            // Verifica a colisão entre o retangulo
                            if (CheckCollisionPointRec(mousePosition,B_Sair_cadastro)){
                                break;
                            }
                        }//botao sair
                            BeginDrawing();
                            ClearBackground(BLACK);
                            //Adicionar
                            DrawRectangle(50,111,400,100,DARKPURPLE);
                            DrawText("Adicionar",60,140,40 ,WHITE);

                            //Listar
                            DrawRectangle(50,222,400,100,DARKPURPLE);
                            DrawText("Listar",60,251,40 ,WHITE);

                            //Pesquisar
                            DrawRectangle(50,333,400,100,DARKPURPLE);
                            DrawText("Pesquisar",60,362,40 ,WHITE);

                            //Alterar
                            DrawRectangle(50,444,400,100,DARKPURPLE);
                            DrawText("Alterar",60,473,40 ,WHITE);

                            //Excluir
                            DrawRectangle(50,555,400,100,DARKPURPLE);
                            DrawText("Excluir",60,584,40 ,WHITE);

                            //Exportar
                            DrawRectangle(50,666,400,100,DARKPURPLE);
                            DrawText("Exportar",60,695,40 ,WHITE);

                            //Sair
                            DrawRectangle(50,777,400,100,DARKPURPLE);
                            DrawText("Sair",60,806,40 ,WHITE);
                        
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
