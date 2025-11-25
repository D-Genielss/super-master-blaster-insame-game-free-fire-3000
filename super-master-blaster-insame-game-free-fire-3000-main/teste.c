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
