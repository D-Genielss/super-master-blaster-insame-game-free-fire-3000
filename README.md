#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char palavra[21];
    char dica[51];
    int dificuldade;
} Pergunta;

void Adicionar_Palavra(Pergunta **Lista, size_t *Tamanho);
void Listar_Palavras(Pergunta *Lista, size_t Tamanho);
int Pesquisar_Palavra(Pergunta *Lista, size_t Tamanho, const char *busca);
void Alterar_Palavra(Pergunta *Lista, size_t Tamanho);
void Excluir_Palavra(Pergunta **Lista, size_t *Tamanho);
void Converte_Maiusculo(char *Palavra);

int main() {
    Pergunta *Dados = NULL;
    size_t Tamanho = 0;
    int Opcao;

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Adicionar palavra\n");
        printf("2 - Listar palavras\n");
        printf("3 - Pesquisar palavra\n");
        printf("4 - Alterar palavra\n");
        printf("5 - Excluir palavra\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &Opcao);
        getchar(); // limpa o buffer

        switch (Opcao) {
            case 1:
                Adicionar_Palavra(&Dados, &Tamanho);
                break;
            case 2:
                Listar_Palavras(Dados, Tamanho);
                break;
            case 3: {
                char busca[21];
                printf("\nDigite a palavra para pesquisar: ");
                fgets(busca, sizeof(busca), stdin);
                busca[strcspn(busca, "\n")] = '\0';
                Converte_Maiusculo(busca);
                Pesquisar_Palavra(Dados, Tamanho, busca);
                break;
            }
            case 4:
                Alterar_Palavra(Dados, Tamanho);
                break;
            case 5:
                Excluir_Palavra(&Dados, &Tamanho);
                break;
            case 0:
                printf("Iniciando o jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (Opcao != 0);

    free(Dados);
    return 0;
}

void Adicionar_Palavra(Pergunta **Lista, size_t *Tamanho) {
    *Lista = realloc(*Lista, (*Tamanho + 1) * sizeof(Pergunta));
    if (*Lista == NULL) {
        perror("Erro ao alocar memória");
        exit(1);
    }

    printf("Digite a palavra que quer inserir: ");
    fgets((*Lista)[*Tamanho].palavra, sizeof((*Lista)[*Tamanho].palavra), stdin);
    (*Lista)[*Tamanho].palavra[strcspn((*Lista)[*Tamanho].palavra, "\n")] = '\0';
    Converte_Maiusculo((*Lista)[*Tamanho].palavra);

    printf("Digite uma dica para ajudar: ");
    fgets((*Lista)[*Tamanho].dica, sizeof((*Lista)[*Tamanho].dica), stdin);
    (*Lista)[*Tamanho].dica[strcspn((*Lista)[*Tamanho].dica, "\n")] = '\0';

    printf("Digite um nível de dificuldade (1 a 5): ");
    scanf("%d", &(*Lista)[*Tamanho].dificuldade);
    getchar();

    (*Tamanho)++;
    printf("A sua palavra foi adicionada com sucesso!\n");
}

void Listar_Palavras(Pergunta *Lista, size_t Tamanho) {
    if (Tamanho == 0) {
        printf("Nenhuma palavra adicionada ainda.\n");
        return;
    }

    printf("\n===== PALAVRAS CADASTRADAS =====\n");
    for (int i = 0; i < (int)Tamanho; i++) {
        printf("%d) %s\n", i + 1, Lista[i].palavra);
    }
}

int Pesquisar_Palavra(Pergunta *Lista, size_t Tamanho, const char *busca) {
    char palavra_temp[21];

    for (int i = 0; i < (int)Tamanho; i++) {
        strcpy(palavra_temp, Lista[i].palavra);
        Converte_Maiusculo(palavra_temp);

        if (strcmp(palavra_temp, busca) == 0) {
            printf("Palavra encontrada!\n");
            printf("Palavra: %s\n", Lista[i].palavra);
            printf("Dica: %s\n", Lista[i].dica);
            printf("Dificuldade: %d\n", Lista[i].dificuldade);
            return i;
        }
    }

    printf("Palavra não encontrada.\n");
    return -1;
}

void Alterar_Palavra(Pergunta *Lista, size_t Tamanho) {
    if (Tamanho == 0) {
        printf("Nenhuma palavra cadastrada para alterar.\n");
        return;
    }

    char busca[21];
    printf("Digite a palavra que deseja alterar: ");
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = '\0';
    Converte_Maiusculo(busca);

    int indice = Pesquisar_Palavra(Lista, Tamanho, busca);
    if (indice == -1) return;

    printf("Digite a nova dica: ");
    fgets(Lista[indice].dica, sizeof(Lista[indice].dica), stdin);
    Lista[indice].dica[strcspn(Lista[indice].dica, "\n")] = '\0';

    printf("Digite o novo nível de dificuldade (1 a 5): ");
    scanf("%d", &Lista[indice].dificuldade);
    getchar();

    printf("Palavra alterada com sucesso!\n");
}

void Excluir_Palavra(Pergunta **Lista, size_t *Tamanho) {
    if (*Tamanho == 0) {
        printf("Nenhuma palavra cadastrada para excluir.\n");
        return;
    }

    char busca[21];
    printf("Digite a palavra que deseja excluir: ");
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = '\0';
    Converte_Maiusculo(busca);

    int indice = Pesquisar_Palavra(*Lista, *Tamanho, busca);
    if (indice == -1) return;

    for (size_t i = indice; i < *Tamanho - 1; i++) {
        (*Lista)[i] = (*Lista)[i + 1];
    }

    (*Tamanho)--;
    *Lista = realloc(*Lista, (*Tamanho) * sizeof(Pergunta));
    printf("Palavra excluída com sucesso!\n");
}

void Converte_Maiusculo(char *Palavra) {
    for (int i = 0; Palavra[i]; i++) {
        Palavra[i] = toupper((unsigned char)Palavra[i]);
    }
}
