#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int ContaLinhas(FILE *arquivo){
    char c;
    int linhas = 0;

    while ((c = fgetc(arquivo)) != EOF)
        if (c == '\n') linhas++;

    fseek(arquivo, 0, SEEK_SET);
    return linhas;
}

int Aleatorio(int linhas){
    srand(time(NULL));
    return (rand() % linhas) + 1;
}


void Procurar(char palavra[][30], char dica[][30]){
    int contador = 0;

    FILE *arquivo = fopen("../output/Palavras.csv","r");
    if(!arquivo){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    while (fscanf(arquivo, "%[^,],%[^,],%*s\n", palavra[contador], dica[contador]) == 2) {
        contador++;
    }

    fclose(arquivo);
}

int main(){
    int linhas;
    int contador = 0;
    int aleatorio;

    FILE *arquivo = fopen("../output/Palavras.csv","r");
    if(!arquivo){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    linhas = ContaLinhas(arquivo);
    fclose(arquivo);

    char palavra[linhas][30];
    char dica[linhas][30];

    Procurar(palavra, dica);

    while (contador < linhas){
        printf("%s, %s\n", palavra[contador], dica[contador]);
        contador++;
    }

    aleatorio = Aleatorio(linhas);
    printf("%d",aleatorio);
        printf("%d",linhas);

    return 0;
}
