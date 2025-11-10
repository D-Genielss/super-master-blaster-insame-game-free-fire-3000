typedef struct {
    char palavra[21];
    char dica[51];
    int dificuldade;
} Pergunta;

#ifndef MENU_REGISTRO_H
#define MENU_REGISTRO_H
#include<stddef.h>
int Menu_Cadastro(Pergunta **Dados, size_t Tamanho);
void Adicionar_Palavra(Pergunta **Lista, size_t *Tamanho);
void Listar_Palavras(Pergunta *Lista, size_t Tamanho);
int Pesquisar_Palavra(Pergunta *Lista, size_t Tamanho, const char *busca);
void Alterar_Palavra(Pergunta *Lista, size_t Tamanho);
void Excluir_Palavra(Pergunta **Lista, size_t *Tamanho);
void Converte_Maiusculo(char *Palavra);
void Carregar_Palavras(Pergunta **Lista, size_t *Tamanho);
void Salvar_Palavras(Pergunta *Lista, size_t Tamanho);
void Exportar_Arquivo(Pergunta Lista[], size_t Tamanho);

#endif // !1