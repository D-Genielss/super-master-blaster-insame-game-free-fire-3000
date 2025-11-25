#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int ContaLinhas(FILE *arquivo){
    char c;
    int linhas = 0;

    while ((c = fgetc(arquivo)) != EOF){
        if (c == '\n') 
        linhas++;
    }

    fseek(arquivo, 0, SEEK_SET);
    return linhas;
}

int Aleatorio(int linhas){
    srand(time(NULL));
    return (rand() % linhas) + 1;
}


void Juntar(FILE *arquivo, char palavra[][30], char dica[][30]){
    int contador = 0;

    while (fscanf(arquivo, "%[^,],%[^,],%*s\n", palavra[contador], dica[contador]) != EOF) {
        contador++;
    }

}

int comparar(char descobrir[6], char palavra[][6], int linhas) {
    for (int i = 0; i < linhas; i++) {
        if (strcmp(descobrir, palavra[i]) == 0) {
            return 1;   // TRUE → encontrou
        }
    }
    return 0;           // FALSE → não encontrou
}



void compararLetras(char palavra[][6], int aleatorio, char descobrir[6], int resultado[5]) {

    for (int i = 0; i < 5; i++) {
        if (descobrir[i] == palavra[aleatorio][i]) {
            resultado[i] = 2; // letra certa no lugar certo
        } else {

            for (int j = 0; j < 5; j++) {
                if (descobrir[i] != '\0' && descobrir[i] == palavra[aleatorio][j]) {
                    resultado[i] = 1;
                    break;
                }
                else {
                resultado[i] = 0;  // não existe
            }
            }

        }
    }
}

/*int main(){
    int linhas;
    int contador = 0;
    int aleatorio;

    FILE *arquivo = fopen("../output/Palavras.csv","r");
    if(!arquivo){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    linhas = ContaLinhas(arquivo);

    char palavra[linhas][30];
    char dica[linhas][30];

    Procurar(arquivo, palavra, dica);
    fclose(arquivo);

    while (contador < linhas){
        printf("%s, %s\n", palavra[contador], dica[contador]);
        contador++;
    }

    aleatorio = Aleatorio(linhas);
    printf("%d",aleatorio);
        printf("%d",linhas);

        printf("\n%s\n", palavra[aleatorio-1]);

    return 0;
}*/
