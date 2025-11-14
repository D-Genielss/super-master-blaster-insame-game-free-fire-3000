#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>



int ContaLinhas(FILE *arquivo){
char c;
int linhas = 1;

while ((c = fgetc(arquivo)) != EOF)
{
    if (c == '\n')
    {
        linhas++;
    }
}
fseek(arquivo,0,0);
return(linhas);
}


void Procurar(char palavra[],char dica[]){

    int linhas;
    int linhas2 = 0;
    int aleatorio;
    int c;



FILE *arquivo = fopen("../output/Palavras.csv","r");

if(arquivo == NULL){
printf("Erro ao abrir o arquivo!\n");
exit(1);// 1 significa erro
}

linhas = ContaLinhas(arquivo);

srand(time(NULL));
while (aleatorio <= 0 ){
aleatorio = (rand()%linhas);
aleatorio--;
}


while ((c = fgetc(arquivo)) != EOF)
{
    if (c == '\n')
    {
        linhas2++;
        if (linhas2 == aleatorio)
        {
            fscanf(arquivo,"%[^,],%[^,]",palavra,dica);
            break;
        }
        
    }
}

printf("%d",aleatorio);

fclose(arquivo);
}


int main(){
    char palavra[30];
    char dica[30];
Procurar(palavra,dica);
printf("\n%s\n",palavra);
printf("%s\n",dica);
}