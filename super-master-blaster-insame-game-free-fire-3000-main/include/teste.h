#ifndef TESTE_H
#define TESTE_H
#include <time.h>

int Aleatorio(int linhas);
int ContaLinhas(FILE *arquivo);
void Juntar(FILE *arquivo, char palavra[][30], char dica[][30]);
bool comparar(char *palavra, char todas_palavras[][30], int total_linhas);
void compararLetras(char todas_palavras[][30], int aleatorio, char *palavra, int *resultado);

#endif