#ifndef MENU_REGISTRO_H
#define MENU_REGISTRO_H
#include <stddef.h>
#include <stdio.h>

typedef struct {
    char palavra[21];
    char dica[51];
    int dificuldade;
} Pergunta;

int Menu_Cadastro(void);
void Adicionar_Palavra(Pergunta **Lista, size_t *Tamanho);
void Listar_Palavras(Pergunta *Lista, size_t Tamanho);
int Pesquisar_Palavra(Pergunta *Lista, size_t Tamanho, const char *busca);
void Alterar_Palavra(Pergunta *Lista, size_t Tamanho);
void Excluir_Palavra(Pergunta **Lista, size_t *Tamanho);
void Converte_Maiusculo(char *Palavra);
void Carregar_Palavras(Pergunta **Lista, size_t *Tamanho);
void Salvar_Palavras(Pergunta *Lista, size_t Tamanho);
void Exportar_Arquivo(Pergunta Lista[], size_t Tamanho);
void Exportar_Por_Dificuldade(Pergunta Lista[], size_t Tamanho);
int ContaLinhas(FILE *arquivo);
void Procurar(char palavra[], char dica[]);

#endif // MENU_REGISTRO_H
