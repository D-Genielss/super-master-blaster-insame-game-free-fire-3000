#include "../include/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>   
#include <ctype.h>
#include <time.h>

void DrawChar(char c, int posX, int posY, int fontSize, Color color) {
    char text[2] = {c, '\0'};
    DrawText(text, posX, posY, fontSize, color);
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
typedef enum {
    MENU_PRINCIPAL,
    SELECAO_DIFICULDADE,
    JOGO_D1,
    JOGO_D2,
    VICTORY,
    GAME_OVER
} Tela_Atual;

// FUNÇÕES
int ContaLinhas(FILE *arquivo){
    char c;
    int linhas = 0;
    while ((c = fgetc(arquivo)) != EOF){
        if (c == '\n') linhas++;
    }
    fseek(arquivo, 0, SEEK_SET);
    return linhas;
}

int Aleatorio(int linhas){
    srand(time(NULL));
    return (rand() % linhas);
}

void Juntar(FILE *arquivo, char palavra[][30], char dica[][30]){
    int contador = 0;
    while (fscanf(arquivo, "%[^,],%[^,],%*s\n", palavra[contador], dica[contador]) != EOF) {
        contador++;
    }
}

int comparar(char descobrir[6], char palavra[][30], int linhas) {
    for (int i = 0; i < linhas; i++) {
        if (strcmp(descobrir, palavra[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void compararLetras(char palavra[][30], int aleatorio, char descobrir[6], int resultado[5]) {
    for (int i = 0; i < 5; i++) {
        resultado[i] = 0; // Inicializa como não encontrada
        
        if (descobrir[i] == palavra[aleatorio][i]) {
            resultado[i] = 2; // letra certa no lugar certo
        } else {
            for (int j = 0; j < 5; j++) {
                if (descobrir[i] == palavra[aleatorio][j]) {
                    resultado[i] = 1; // letra existe mas em posição diferente
                    break;
                }
            }
        }
    }
}

int verificarVitoria(int resultado[5]) {
    for (int i = 0; i < 5; i++) {
        if (resultado[i] != 2) return 0;
    }
    return 1;
}

void raylib() {
    // Carregar palavras
    FILE *arquivo = fopen("Palavras.csv","r");
    if(!arquivo){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }
    int linhas = ContaLinhas(arquivo);
    char todas_P[linhas][30];
    char dica[linhas][30];
    Juntar(arquivo, todas_P, dica);
    fclose(arquivo);

    int aleatorio = Aleatorio(linhas);

    // Inicialização
    const int screenWidth = 1600;
    const int screenHeight = 900;
    
    InitWindow(screenWidth, screenHeight, "TERMO 1.0 ");
    SetTargetFPS(60);

    // Estado do jogo
    Tela_Atual telaAtual = MENU_PRINCIPAL;
    
    //Botões
    Rectangle B_jogar = {(screenWidth/2)-200, 400, 400, 80};
    Rectangle B_D1 = {360, 410, 440, 120};
    Rectangle B_D2 = {860, 410, 440, 120};
    Rectangle B_voltar = {50, 50, 200, 60}; // Botão voltar

    // Variáveis do jogo principal
    char Palavra[6] = ""; // Palavra atual
    int tamanho = 0;
    int tentativa = 0;
    int maxTentativas = 6;
    int resultados[6][5] = {0}; // Resultados para todas as tentativas
    char palavrasTentadas[6][6] = {0}; // Palavras tentadas

    // Loop principal do jogo
    while (!WindowShouldClose()) {
        // Input
        Vector2 mousePosition = GetMousePosition();
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            switch(telaAtual) {
                case MENU_PRINCIPAL:
                    if (CheckCollisionPointRec(mousePosition, B_jogar)) {
                        telaAtual = SELECAO_DIFICULDADE;
                    }
                    break;
                    
                case SELECAO_DIFICULDADE:
                    if (CheckCollisionPointRec(mousePosition, B_D1)) {
                        telaAtual = JOGO_D1;
                        maxTentativas = 6;
                        // Resetar jogo
                        strcpy(Palavra, "");
                        tamanho = 0;
                        tentativa = 0;
                        memset(resultados, 0, sizeof(resultados));
                        memset(palavrasTentadas, 0, sizeof(palavrasTentadas));
                        aleatorio = Aleatorio(linhas);
                    }
                    if (CheckCollisionPointRec(mousePosition, B_D2)) {
                        telaAtual = JOGO_D2;
                        maxTentativas = 4;
                        // Resetar jogo
                        strcpy(Palavra, "");
                        tamanho = 0;
                        tentativa = 0;
                        memset(resultados, 0, sizeof(resultados));
                        memset(palavrasTentadas, 0, sizeof(palavrasTentadas));
                        aleatorio = Aleatorio(linhas);
                    }
                    if (CheckCollisionPointRec(mousePosition, B_voltar)) {
                        telaAtual = MENU_PRINCIPAL;
                    }
                    break;
                    
                case VICTORY:
                case GAME_OVER:
                    if (CheckCollisionPointRec(mousePosition, B_voltar)) {
                        telaAtual = SELECAO_DIFICULDADE;
                    }
                    break;
                    
                default:
                    break;
            }
        }

        // Lógica do jogo quando ativo
        if (telaAtual == JOGO_D1 || telaAtual == JOGO_D2) {
            int key = GetCharPressed();
            if ((key >= 32) && (key <= 125) && (tamanho < 5)) {
                Palavra[tamanho] = (char)key;
                Palavra[tamanho + 1] = '\0';
                tamanho++;
            }
            if (IsKeyPressed(KEY_BACKSPACE) && tamanho > 0) {
                tamanho--;
                Palavra[tamanho] = '\0';
            }
            if (IsKeyPressed(KEY_ENTER) && tamanho == 5) {
                // Converter para maiúsculo
                for (int i = 0; i < tamanho; i++) {
                    Palavra[i] = toupper(Palavra[i]);
                }
                
                if (comparar(Palavra, todas_P, linhas)) {
                    strcpy(palavrasTentadas[tentativa], Palavra);
                    compararLetras(todas_P, aleatorio, Palavra, resultados[tentativa]);
                    
                    if (verificarVitoria(resultados[tentativa])) {
                        telaAtual = VICTORY;
                    } else {
                        tentativa++;
                        if (tentativa >= maxTentativas) {
                            telaAtual = GAME_OVER;
                        } else {
                            // Prepara para próxima tentativa
                            strcpy(Palavra, "");
                            tamanho = 0;
                        }
                    }
                } else {
                    // Palavra não existe no dicionário
                    // Você pode mostrar uma mensagem de erro aqui
                }
            }
            
            // Botão voltar durante o jogo
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePosition, B_voltar)) {
                telaAtual = SELECAO_DIFICULDADE;
            }
        }

        // Render
        BeginDrawing();
        ClearBackground(BLACK);

        switch(telaAtual) {
            case MENU_PRINCIPAL:
                DrawText("SUPER-MASTER-BLASTER-INSANE-GAME-FREE-FIRE-3000", screenWidth/2 - 500, 200, 40, WHITE);
                DrawRectangleRec(B_jogar, DARKPURPLE);
                DrawText("Iniciar", B_jogar.x + 150, B_jogar.y + 20, 40, WHITE);
                break;
                
            case SELECAO_DIFICULDADE:
                DrawText("ESCOLHA A DIFICULDADE", 450, 200, 50, WHITE);
                
                // Dificuldade 1
                DrawRectangleRec(B_D1, GREEN);
                DrawRectangle(B_D1.x + 10, B_D1.y + 10, B_D1.width - 20, B_D1.height - 20, BLACK);
                DrawText("DIFICULDADE 1", B_D1.x + 20, B_D1.y + 45, 40, GREEN);
                DrawText("6 TENTATIVAS", B_D1.x + 20, B_D1.y + 85, 25, GREEN);
                
                // Dificuldade 2
                DrawRectangleRec(B_D2, YELLOW);
                DrawRectangle(B_D2.x + 10, B_D2.y + 10, B_D2.width - 20, B_D2.height - 20, BLACK);
                DrawText("DIFICULDADE 2", B_D2.x + 20, B_D2.y + 45, 40, YELLOW);
                DrawText("4 TENTATIVAS", B_D2.x + 20, B_D2.y + 85, 25, YELLOW);
                
                // Botão voltar
                DrawRectangleRec(B_voltar, RED);
                DrawText("Voltar", B_voltar.x + 50, B_voltar.y + 15, 30, WHITE);
                break;
                
            case JOGO_D1:
                DrawText("JOGO DIFICULDADE 1 - 6 TENTATIVAS", 350, 50, 40, GREEN);
                DrawText(TextFormat("Dica: %s", dica[aleatorio]), 100, 120, 25, GREEN);
                DrawText("TODO 'space' TROCAR POR '_'", 100, 150, 25, GREEN);
                
                // Desenhar tentativas anteriores
                for (int t = 0; t < tentativa; t++) {
                    int PositionY = 150 + t * 130;
                    for (int i = 0; i < 5; i++) {
                        int PositionX = 500 + i * 150;
                        Color cor;
                        switch (resultados[t][i]) {
                            case 0: cor = GRAY; break;
                            case 1: cor = YELLOW; break;
                            case 2: cor = GREEN; break;
                            default: cor = GRAY; break;
                        }
                        DrawRectangle(PositionX, PositionY, 100, 120, cor);
                        DrawChar(palavrasTentadas[t][i], PositionX + 20, PositionY, 80, WHITE);
                    }
                }
                
                // Desenhar tentativa atual
                if (tentativa < maxTentativas) {
                    int PositionY = 150 + tentativa * 130;
                    for (int i = 0; i < 5; i++) {
                        int PositionX = 500 + i * 150;
                        DrawRectangle(PositionX, PositionY, 100, 120, DARKGRAY);
                        if (i < tamanho) {
                            DrawChar(Palavra[i], PositionX + 20, PositionY, 80, WHITE);
                        }
                    }
                }
                
                // Botão voltar
                DrawRectangleRec(B_voltar, RED);
                DrawText("Voltar", B_voltar.x + 50, B_voltar.y + 15, 30, WHITE);
                break;
                
            case JOGO_D2:
                DrawText("JOGO DIFICULDADE 2 - 4 TENTATIVAS", 350, 50, 40, YELLOW);
                DrawText("SEM DICA !", 100, 120, 25, YELLOW);
                DrawText("TODO 'space' TROCAR POR '_'", 100, 150, 25, YELLOW);

                // Desenhar tentativas anteriores
                for (int t = 0; t < tentativa; t++) {
                    int PositionY = 200 + t * 130;
                    for (int i = 0; i < 5; i++) {
                        int PositionX = 500 + i * 150;
                        Color cor;
                        switch (resultados[t][i]) {
                            case 0: cor = GRAY; break;
                            case 1: cor = YELLOW; break;
                            case 2: cor = GREEN; break;
                            default: cor = GRAY; break;
                        }
                        DrawRectangle(PositionX, PositionY, 100, 120, cor);
                        DrawChar(palavrasTentadas[t][i], PositionX + 20, PositionY, 80, WHITE);
                    }
                }
                
                // Desenhar tentativa atual
                if (tentativa < maxTentativas) {
                    int PositionY = 200 + tentativa * 130;
                    for (int i = 0; i < 5; i++) {
                        int PositionX = 500 + i * 150;
                        DrawRectangle(PositionX, PositionY, 100, 120, DARKGRAY);
                        if (i < tamanho) {
                            DrawChar(Palavra[i], PositionX + 20, PositionY, 80, WHITE);
                        }
                    }
                }
                
                // Botão voltar
                DrawRectangleRec(B_voltar, RED);
                DrawText("Voltar", B_voltar.x + 50, B_voltar.y + 20, 30, WHITE);
                break;
                
            case VICTORY:
                DrawText("VITÓRIA!", screenWidth/2 - 100, 300, 60, GREEN);
                DrawText(TextFormat("Palavra: %s", todas_P[aleatorio]), screenWidth/2 - 150, 400, 30, WHITE);
                DrawRectangleRec(B_voltar, GREEN);
                DrawText("Voltar ao Menu", B_voltar.x + 20, B_voltar.y + 20, 30, WHITE);
                break;
                
            case GAME_OVER:
                DrawText("GAME OVER!", screenWidth/2 - 120, 300, 60, RED);
                DrawText(TextFormat("A palavra era: %s", todas_P[aleatorio]), screenWidth/2 - 150, 400, 30, WHITE);
                DrawRectangleRec(B_voltar, RED);
                DrawText("Voltar ao Menu", B_voltar.x + 20, B_voltar.y + 20, 30, WHITE);
                break;
        }

        EndDrawing();
    }

    CloseWindow();
}