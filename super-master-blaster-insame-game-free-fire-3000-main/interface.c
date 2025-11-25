#include "../include/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>   
#include <ctype.h> // Adicionei esta linha para usar toupper()
#include "../include/teste.h"

void DrawChar(char c, int posX, int posY, int fontSize, Color color) {
    char text[2] = {c, '\0'};
    DrawText(text, posX, posY, fontSize, color);
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
typedef enum {
    COLOCA_PALAVRA,
    TELA_GAME_RODANDO
} Tela_Jogo;

void raylib(){

    int linhas;
    int aleatorio;
    
    FILE *arquivo = fopen("Palavras.csv","r");
    if(!arquivo){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }
    linhas = ContaLinhas(arquivo);

    char todas_P[linhas][30];
    char dica[linhas][30];

    Juntar(arquivo, todas_P, dica);
    
    fclose(arquivo);

    char deniels[30];
    sprintf(deniels, "%d", linhas);

    aleatorio = Aleatorio(linhas);

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
        DrawText(todas_P[aleatorio-1],200,200,50 ,WHITE);      
        DrawText(deniels,800,200,50 ,WHITE);  

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
                        bool TelaVictory = false;
                        int tamanho = 0;
                        char Palavra[6];
                        int tentativa = 0;
                        Tela_Jogo TELA_MOMENTO = COLOCA_PALAVRA;
               
                    while(!WindowShouldClose()){                 
                        if(TelaVictory == true){
                            while(!WindowShouldClose()){

                                BeginDrawing();

                                ClearBackground(BLACK);

                                DrawText("Victoria",450,50,50 ,GREEN);

                                EndDrawing();

                                if(!WindowShouldClose()){
                                    TelaVictory = false;
                                    TelaD1 = false;
                                    TelaComecar = true;
                                }

                            }
                        }//tela vitoria 
                        switch(TELA_MOMENTO){
                            
                            case COLOCA_PALAVRA:{

                                int key = GetCharPressed();

                                if((key >= 32) && (key <= 125) && (tamanho < 5)){
                                    Palavra[tamanho] = (char)key;
                                    Palavra[tamanho+1] = '\0';
                                    tamanho++;
                                }
                                if (IsKeyPressed(KEY_BACKSPACE)){
                                    if (tamanho > 0){
                                        tamanho--;
                                        Palavra[tamanho] = '\0';
                                    }
                                }
                               if (IsKeyPressed(KEY_ENTER)){
                                    // CONVERTE A PALAVRA PARA MAIÚSCULO APÓS O ENTER
                                    for(int i = 0; i < tamanho; i++) {
                                        Palavra[i] = toupper(Palavra[i]);
                                    }
                                    TELA_MOMENTO = TELA_GAME_RODANDO;
                                }

                                                   
                            }break;
                            case TELA_GAME_RODANDO:{
                                
                                bool Compara = comparar(Palavra,todas_P,linhas);
                                int resultado[5];   
                                
                                if(Compara == false){
                                    
                                    for(int i = 0;i < 6; i++){ 
                                        tamanho--;
                                        Palavra[i] = '\0'; 
                                    }
                                    TELA_MOMENTO = COLOCA_PALAVRA;

                                }else{
                                    
                                    compararLetras(todas_P,aleatorio -1,Palavra,resultado);
                                    
                                    if(resultado[0] == 2){
                                        printf("%d\n\n\n\n\n\n\n%s,%s\n\n\n\n\n\n\n\n",resultado[0],Palavra,todas_P[aleatorio-1]);
                                        if(resultado[1] == 2){
                                            if(resultado[2] == 2){
                                                if(resultado[3] == 2){
                                                    if(resultado[4] == 2){
                                                        TelaVictory = true;
                                                        for(int i = 0;i < 6; i++){ 
                                                            tamanho--;
                                                            Palavra[i] = '\0'; 
                                                        }

                                                    }else{
                                                        tentativa ++;
                                                        TELA_MOMENTO = COLOCA_PALAVRA;
                                                    }//else 5 letra
                                                }else{
                                                    tentativa ++;
                                                    TELA_MOMENTO = COLOCA_PALAVRA;
                                                }//else 4 letra
                                            }else{
                                                tentativa ++;
                                                TELA_MOMENTO = COLOCA_PALAVRA;
                                            }//else 3 letra
                                        }else{
                                            tentativa ++;
                                            TELA_MOMENTO = COLOCA_PALAVRA;
                                        }//else 2 letra
                                    }else{
                                        tentativa ++;
                                        TELA_MOMENTO = COLOCA_PALAVRA;
                                    }//else 1 letra
                                }
                                
                            } break;
                            default: break;
                        }
//switch tela game
                        BeginDrawing();
                            switch(TELA_MOMENTO){

                                case COLOCA_PALAVRA:{

                                    int PositionY = 50;
                                    int PositionX = 350;

                                    ClearBackground(BLACK);
                                    DrawText("JOGO DIFICULDADE 1",450,50,50 ,GREEN);

                                    for(int i = 0;i < 6; i++){
                                        PositionY = PositionY + 110;
                                        PositionX = 325;                                      
                                        for(int i = 0;i < 5; i++){   
                                            PositionX = PositionX + 150;                                       
                                            DrawRectangle(PositionX ,PositionY , 100, 100, GRAY);
                                        }                                                                              
                                    }
                                    PositionX = 500;
                                    PositionY = 160;
                                    DrawChar(Palavra[0], PositionX, PositionY, 80, WHITE);
                                 
                                    DrawChar(Palavra[1], (PositionX+150), PositionY, 80, WHITE);
                                    
                                    DrawChar(Palavra[2], (PositionX +300), PositionY, 80, WHITE);
                                    
                                    DrawChar(Palavra[3], (PositionX +450), PositionY, 80, WHITE);

                                    DrawChar(Palavra[4], (PositionX +600), PositionY, 80, WHITE);

                                }break;

                                case TELA_GAME_RODANDO:{
                                    
                                }break;

                                default: break;
                            }
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
