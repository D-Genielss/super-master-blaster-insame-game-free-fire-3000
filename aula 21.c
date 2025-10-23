#include<stdio.h>
#include<stdlib.h>

int main(){

    FILE* arquivo = fopen("./texto.txt","w");

    if(arquivo == NULL){

        perror("Error ao abrir arquivo : ");
        exit(1);

    }

    fclose(arquivo);
    
    return 0;
}