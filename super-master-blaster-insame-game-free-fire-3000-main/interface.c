#include "../include/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Estrutura para armazenar palavras por nível
#define MAX_PALAVRAS 200
#define MAX_TAMANHO_PALAVRA 50

typedef struct {
    char palavras[MAX_PALAVRAS][MAX_TAMANHO_PALAVRA];
    int quantidade;
} ListaPalavras;

typedef struct {
    ListaPalavras nivel1; // 5 letras
    ListaPalavras nivel2; // 6-9 letras
} BancoPalavras;

// Função para remover caracteres especiais e converter para maiúsculo
void LimparPalavra(char *palavra) {
    int i, j = 0;
    char temp[MAX_TAMANHO_PALAVRA];
    
    for (i = 0; palavra[i] != '\0'; i++) {
        if (isalpha((unsigned char)palavra[i])) {
            temp[j++] = toupper((unsigned char)palavra[i]);
        }
    }
    temp[j] = '\0';
    strcpy(palavra, temp);
}

// Função para carregar palavras do arquivo CSV
int CarregarPalavrasCSV(BancoPalavras *banco, const char *nomeArquivo) {
    banco->nivel1.quantidade = 0;
    banco->nivel2.quantidade = 0;
    
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro: Não foi possível abrir o arquivo %s\n", nomeArquivo);
        return 0;
    }
    
    char linha[1024];
    int totalCarregadas = 0;
    
    while (fgets(linha, sizeof(linha), arquivo) && totalCarregadas < MAX_PALAVRAS) {
        linha[strcspn(linha, "\r\n")] = 0;
        
        if (strlen(linha) > 0) {
            char palavra[MAX_TAMANHO_PALAVRA];
            strcpy(palavra, linha);
            LimparPalavra(palavra);
            
            int tamanho = strlen(palavra);
            
            if (tamanho >= 1 && tamanho <= 9) {
                if (tamanho == 5) {
                    if (banco->nivel1.quantidade < MAX_PALAVRAS) {
                        strcpy(banco->nivel1.palavras[banco->nivel1.quantidade], palavra);
                        banco->nivel1.quantidade++;
                        totalCarregadas++;
                    }
                } else if (tamanho >= 6 && tamanho <= 9) {
                    if (banco->nivel2.quantidade < MAX_PALAVRAS) {
                        strcpy(banco->nivel2.palavras[banco->nivel2.quantidade], palavra);
                        banco->nivel2.quantidade++;
                        totalCarregadas++;
                    }
                }
            }
        }
    }
    
    fclose(arquivo);
    printf("Carregadas %d palavras do arquivo CSV\n", totalCarregadas);
    printf("Nível 1 (5 letras): %d palavras\n", banco->nivel1.quantidade);
    printf("Nível 2 (6-9 letras): %d palavras\n", banco->nivel2.quantidade);
    
    return totalCarregadas;
}

// Função para listar palavras
void TelaListarPalavras(BancoPalavras *banco) {
    const int screenWidth = 1600;
    // Removida a variável screenHeight não utilizada
    
    bool sair = false;
    
    Rectangle btnVoltar = {50, 800, 200, 50};
    int scrollOffset = 0;
    bool mostrarNivel1 = true;
    
    while (!sair && !WindowShouldClose()) {
        int wheel = GetMouseWheelMove();
        scrollOffset -= wheel * 30;
        if (scrollOffset < 0) scrollOffset = 0;
        
        if (IsKeyPressed(KEY_ONE)) mostrarNivel1 = true;
        if (IsKeyPressed(KEY_TWO)) mostrarNivel1 = false;
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePosition = GetMousePosition();
            if (CheckCollisionPointRec(mousePosition, btnVoltar)) {
                sair = true;
            }
        }
        
        BeginDrawing();
            ClearBackground(BLACK);
            
            DrawText("LISTA DE PALAVRAS DO JOGO", screenWidth/2 - 250, 20, 40, WHITE);
            
            if (mostrarNivel1) {
                DrawText("NIVEL 1 - PALAVRAS DE 5 LETRAS", screenWidth/2 - 200, 70, 30, GREEN);
                DrawText(TextFormat("Total: %d palavras", banco->nivel1.quantidade), screenWidth/2 - 100, 100, 25, LIGHTGRAY);
            } else {
                DrawText("NIVEL 2 - PALAVRAS DE 6-9 LETRAS", screenWidth/2 - 220, 70, 30, YELLOW);
                DrawText(TextFormat("Total: %d palavras", banco->nivel2.quantidade), screenWidth/2 - 120, 100, 25, LIGHTGRAY);
            }
            
            DrawText("Pressione 1 para Nivel 1 | 2 para Nivel 2", 50, 120, 20, LIGHTGRAY);
            
            int startY = 150;
            ListaPalavras *listaAtual = mostrarNivel1 ? &banco->nivel1 : &banco->nivel2;
            
            for (int i = 0; i < listaAtual->quantidade; i++) {
                int yPos = startY + (i * 35) - scrollOffset;
                if (yPos > 130 && yPos < 750) {
                    Color cor = mostrarNivel1 ? GREEN : YELLOW;
                    DrawText(TextFormat("%3d. %s (%d letras)", i + 1, listaAtual->palavras[i], 
                            (int)strlen(listaAtual->palavras[i])), 
                            100, yPos, 25, cor);
                }
            }
            
            DrawRectangleRec(btnVoltar, DARKPURPLE);
            DrawText("Voltar", btnVoltar.x + 60, btnVoltar.y + 10, 30, WHITE);
            
        EndDrawing();
    }
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
void raylib(){
    // Inicialização
    const int screenWidth = 1600;
    const int screenHeight = 900;
    bool TelaCadastro = false;
    bool TelaComecar = false;
    bool ListarPalavrasAtivo = false;
    
    // Carregar banco de palavras
    BancoPalavras banco;
    int palavrasCarregadas = CarregarPalavrasCSV(&banco, "palavras.csv");
    
    // Fallback se não conseguir carregar do arquivo
    if (palavrasCarregadas == 0) {
    // Palavras padrão nível 1 (5 letras) - na ordem do CSV
    const char* palavrasNivel1[] = {
        "MARIO", "ZELDA", "HALO", "FIFA", "SONIC", "CRASH", "LIMBO", "RISK", 
        "MINES", "BRAID", "PONG", "DOOM", "VEXX", "GEMS", "SLY", "FTL", 
        "ALIEN", "PIXEL", "ZOMBI", "KOF", "DARKS", "WARIO", "TORCH", "SOUL", 
        "MOON", "LARA", "BLOX", "HADES", "GOLF", "MAGE"
    };
    
    // Palavras padrão nível 2 (6-9 letras) - na ordem do CSV
    const char* palavrasNivel2[] = {
        "FORTNITE", "SPELUNKY", "TETRIS", "FLAPPY", "PLANTS", "FALLOUT", 
        "FABLE", "CUPHEAD", "SPYRO", "PACMAN", "BASTION", "TRIALS", 
        "CLASH", "BRAWL", "AMNESIA", "THIEF", "VALIANT", "BRICK", 
        "LOCO", "TRINE", "GEARS", "ROBLOX", "CELESTE", "HOLLOW", 
        "TERRARIA", "STARDEW", "WARZONE", "DESTINY", "OUTLAST", "CONTROL", 
        "DIABLO3", "HORIZON", "FARLIGHT", "METRO2033", "FORAGER", "INFAMOUS", 
        "WATCHDOGS", "RIMWORLD", "PAYDAY2", "UNRAVEL", "INSIDE", "VAMPYR", 
        "GODFALL", "AMONGUS", "STARFOX", "VALORANT", "MANHUNT", "CRYSIS", 
        "HITMAN2", "FARCRY3", "TUROK2", "DUSTFORCE", "HADESII", "WASTELAND", 
        "TETRIS99", "PEGGLE2", "DOOM64", "JUMPKING", "DEADBOLT", "OXENFREE", 
        "CARRION", "KATANA0", "ABSOLVER", "BAYONETT", "OVERLORD", "DEADCELLS", 
        "BIOSHOCK", "MINECRAFT", "OVERWATCH", "SKYRIM"
    };
    
    // Carregar palavras nível 1 (5 letras)
    for (int i = 0; i < 30; i++) {
        strcpy(banco.nivel1.palavras[i], palavrasNivel1[i]);
    }
    banco.nivel1.quantidade = 30;
    
    // Carregar palavras nível 2 (6-9 letras)
    for (int i = 0; i < 70; i++) {
        strcpy(banco.nivel2.palavras[i], palavrasNivel2[i]);
    }
    banco.nivel2.quantidade = 70;
    
    printf("Usando palavras padrão: 30 nivel1 + 70 nivel2\n");
}

    //Botao Começar a Jogar
    int XL_jogar = 400;
    int YA_Jogar = 80;
    int X_Jogar = (screenWidth/2)-200;
    int Y_Jogar = 400;
    Rectangle B_jogar = {X_Jogar,Y_Jogar,XL_jogar,YA_Jogar};

    //Botao Menu cadastro
    int XL_cadastro = 400;
    int YA_cadastro = 80;
    int X_cadastro = (screenWidth/2)-200;
    int Y_cadastro = 600;
    Rectangle B_cadastro = {X_cadastro,Y_cadastro,XL_cadastro,YA_cadastro};
    Rectangle B_Sair_cadastro = {50,777,400,100};

    // Botão Listar no menu de cadastro
    Rectangle B_Listar = {50,222,400,100};

    InitWindow(screenWidth, screenHeight, "TERMO 1.0 - Com Banco de Palavras");
    SetTargetFPS(60);

    // Loop principal do jogo
    while (!WindowShouldClose()){
        // Atualizar
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            Vector2 mousePosition = GetMousePosition();
            
            if (CheckCollisionPointRec(mousePosition,B_jogar)){
                TelaComecar = true;
            }
            
            if (CheckCollisionPointRec(mousePosition,B_cadastro)){
                TelaCadastro = true;
            }
            
            // No menu de cadastro, verificar clique em "Listar"
            if (TelaCadastro && CheckCollisionPointRec(mousePosition, B_Listar)) {
                ListarPalavrasAtivo = true;
            }
        }

        // Desenha
        BeginDrawing();
            ClearBackground(BLACK);
            
            //Menu Principal
            DrawText("super-master-blaster-insame-game-free-fire-3000",200,200,50 ,WHITE);
            
            // Mostrar estatísticas das palavras carregadas
            DrawText(TextFormat("Palavras: N1:%d | N2:%d", 
                banco.nivel1.quantidade, banco.nivel2.quantidade), 200, 270, 25, LIGHTGRAY);

            //Botão Jogar
            DrawRectangle(X_Jogar,Y_Jogar,XL_jogar,YA_Jogar,DARKPURPLE);
            DrawText("Iniciar",(screenWidth/2)-100,Y_Jogar + 20,40 ,WHITE);
            
            //Botão Cadastro
            DrawRectangle(X_cadastro,Y_cadastro,XL_cadastro,YA_cadastro,DARKPURPLE);
            DrawText("Cadastrar",(screenWidth/2)-100,Y_cadastro + 20,40 ,WHITE);

            // Tela Comecar
            if(TelaComecar == true){
                bool voltarJogo = false;
                while (!WindowShouldClose() && !voltarJogo){
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        Vector2 mousePos = GetMousePosition();
                        Rectangle btnVoltarJogo = {50, 800, 200, 50};
                        if (CheckCollisionPointRec(mousePos, btnVoltarJogo)) {
                            voltarJogo = true;
                        }
                    }
                    
                    BeginDrawing();
                        ClearBackground(BLACK);
                        DrawText("TELA DO JOGO", screenWidth/2 - 150, screenHeight/2, 40, WHITE);
                        DrawText("Em desenvolvimento...", screenWidth/2 - 150, screenHeight/2 + 50, 30, LIGHTGRAY);
                        
                        DrawRectangle(50, 800, 200, 50, DARKPURPLE);
                        DrawText("Voltar", 100, 810, 30, WHITE);
                    EndDrawing();
                    
                    if (voltarJogo) {
                        TelaComecar = false;
                        break;
                    }
                }
            }

            // Tela Cadastro
            if(TelaCadastro == true){
                bool sairCadastro = false;
                
                while (!WindowShouldClose() && !sairCadastro && !ListarPalavrasAtivo){
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        Vector2 mousePosition = GetMousePosition();
                        
                        if (CheckCollisionPointRec(mousePosition,B_Sair_cadastro)){
                            sairCadastro = true;
                        }
                        
                        if (CheckCollisionPointRec(mousePosition, B_Listar)) {
                            ListarPalavrasAtivo = true;
                        }
                    }
                    
                    BeginDrawing();
                        ClearBackground(BLACK);
                        
                        // Menu de cadastro
                        DrawRectangle(50,111,400,100,DARKPURPLE);
                        DrawText("Adicionar",60,140,40 ,WHITE);

                        DrawRectangle(50,222,400,100,DARKPURPLE);
                        DrawText("Listar",60,251,40 ,WHITE);

                        DrawRectangle(50,333,400,100,DARKPURPLE);
                        DrawText("Pesquisar",60,362,40 ,WHITE);

                        DrawRectangle(50,444,400,100,DARKPURPLE);
                        DrawText("Alterar",60,473,40 ,WHITE);

                        DrawRectangle(50,555,400,100,DARKPURPLE);
                        DrawText("Excluir",60,584,40 ,WHITE);

                        DrawRectangle(50,666,400,100,DARKPURPLE);
                        DrawText("Exportar",60,695,40 ,WHITE);

                        DrawRectangle(50,777,400,100,DARKPURPLE);
                        DrawText("Sair",60,806,40 ,WHITE);
                    EndDrawing();
                    
                    if (sairCadastro) {
                        TelaCadastro = false;
                        break;
                    }
                }
                
                // Tela de listar palavras
                if (ListarPalavrasAtivo) {
                    TelaListarPalavras(&banco);
                    ListarPalavrasAtivo = false;
                }
            }

        EndDrawing();
    }

    CloseWindow();
}
