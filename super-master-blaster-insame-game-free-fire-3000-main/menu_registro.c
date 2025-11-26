#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "menu_registro.h"

int Menu_Cadastro() {
    Pergunta *Dados = NULL;   
    size_t Tamanho = 0;
    int Opcao;

    Carregar_Palavras(&Dados, &Tamanho);  

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Adicionar palavra\n");
        printf("2 - Listar palavras\n");
        printf("3 - Pesquisar palavra\n");
        printf("4 - Alterar palavra\n");
        printf("5 - Excluir palavra\n");
        printf("6 - Exportar arquivo\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        
        if (scanf("%d", &Opcao) != 1) {
            printf("Entrada inválida!\n");
            while (getchar() != '\n'); // limpa buffer
            continue;
        }
        getchar(); // limpa o buffer

        switch (Opcao) {
            case 1:
                Adicionar_Palavra(&Dados, &Tamanho);
                Salvar_Palavras(Dados, Tamanho);
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
                Salvar_Palavras(Dados, Tamanho);
                break;
            case 5:
                Excluir_Palavra(&Dados, &Tamanho);
                Salvar_Palavras(Dados, Tamanho);
                break;
            case 6:
                Exportar_Arquivo(Dados, Tamanho);
                break;
            case 0:
                Salvar_Palavras(Dados, Tamanho);
                printf("Saindo e salvando os dados...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (Opcao != 0);

    free(Dados);
    return (int)Tamanho;
}

void Adicionar_Palavra(Pergunta **Lista, size_t *Tamanho) {
    Pergunta *nova_lista = realloc(*Lista, (*Tamanho + 1) * sizeof(Pergunta));
    if (nova_lista == NULL) {
        perror("Erro ao alocar memória");
        return;
    }
    *Lista = nova_lista;

    printf("Digite a palavra que quer inserir: ");
    fgets((*Lista)[*Tamanho].palavra, sizeof((*Lista)[*Tamanho].palavra), stdin);
    (*Lista)[*Tamanho].palavra[strcspn((*Lista)[*Tamanho].palavra, "\n")] = '\0';
    Converte_Maiusculo((*Lista)[*Tamanho].palavra);

    // Verificar se palavra já existe
    for (size_t i = 0; i < *Tamanho; i++) {
        if (strcmp((*Lista)[i].palavra, (*Lista)[*Tamanho].palavra) == 0) {
            printf("Erro: Esta palavra já existe na lista!\n");
            return;
        }
    }

    printf("Digite uma dica para ajudar: ");
    fgets((*Lista)[*Tamanho].dica, sizeof((*Lista)[*Tamanho].dica), stdin);
    (*Lista)[*Tamanho].dica[strcspn((*Lista)[*Tamanho].dica, "\n")] = '\0';

    // Validar dificuldade
    do {
        printf("Digite um nível de dificuldade (1 a 2): ");
        if (scanf("%d", &(*Lista)[*Tamanho].dificuldade) != 1) {
            printf("Entrada inválida!\n");
            while (getchar() != '\n'); // limpa buffer
            continue;
        }
        getchar(); // limpa o buffer
        
        if ((*Lista)[*Tamanho].dificuldade < 1 || (*Lista)[*Tamanho].dificuldade > 2) {
            printf("Dificuldade deve ser entre 1 e 2!\n");
        }
    } while ((*Lista)[*Tamanho].dificuldade < 1 || (*Lista)[*Tamanho].dificuldade > 2);

    (*Tamanho)++;
    printf("A sua palavra foi adicionada com sucesso!\n");
}

void Listar_Palavras(Pergunta *Lista, size_t Tamanho) {
    if (Tamanho == 0) {
        printf("Nenhuma palavra adicionada ainda.\n");
        return;
    }

    printf("\n===== PALAVRAS CADASTRADAS =====\n");
    for (size_t i = 0; i < Tamanho; i++) {
        printf("%zu) %s (Dificuldade %d) - Dica: %s\n",
               i + 1, Lista[i].palavra, Lista[i].dificuldade, Lista[i].dica);
    }
}

int Pesquisar_Palavra(Pergunta *Lista, size_t Tamanho, const char *busca) {
    if (Tamanho == 0) {
        printf("Nenhuma palavra cadastrada.\n");
        return -1;
    }

    for (size_t i = 0; i < Tamanho; i++) {
        if (strcmp(Lista[i].palavra, busca) == 0) {
            printf("\nPalavra encontrada!\n");
            printf("Palavra: %s\n", Lista[i].palavra);
            printf("Dica: %s\n", Lista[i].dica);
            printf("Dificuldade: %d\n", Lista[i].dificuldade);
            return (int)i;
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

    // Validar nova dificuldade
    do {
        printf("Digite o novo nível de dificuldade (1 a 2): ");
        if (scanf("%d", &Lista[indice].dificuldade) != 1) {
            printf("Entrada inválida!\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();
        
        if (Lista[indice].dificuldade < 1 || Lista[indice].dificuldade > 2) {
            printf("Dificuldade deve ser entre 1 e 2!\n");
        }
    } while (Lista[indice].dificuldade < 1 || Lista[indice].dificuldade > 2);

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

    // Confirmação
    printf("Tem certeza que deseja excluir '%s'? (s/n): ", (*Lista)[indice].palavra);
    char confirmacao;
    scanf(" %c", &confirmacao);
    getchar();
    
    if (confirmacao != 's' && confirmacao != 'S') {
        printf("Exclusão cancelada.\n");
        return;
    }

    // Move os elementos
    for (size_t i = (size_t)indice; i < *Tamanho - 1; i++) {
        (*Lista)[i] = (*Lista)[i + 1]; 
    }

    (*Tamanho)--;

    // Realoca a memória apenas se ainda houver elementos
    if (*Tamanho > 0) {
        Pergunta *nova_lista = realloc(*Lista, (*Tamanho) * sizeof(Pergunta));
        if (nova_lista == NULL) {
            perror("Erro ao realocar memória");
            return;
        }
        *Lista = nova_lista;
    } else {
        free(*Lista);
        *Lista = NULL;
    }

    printf("Palavra excluída com sucesso!\n");
}

void Converte_Maiusculo(char *Palavra) {
    for (int i = 0; Palavra[i]; i++) {
        Palavra[i] = toupper((unsigned char)Palavra[i]);
    }
}

void Carregar_Palavras(Pergunta **Lista, size_t *Tamanho) {
    FILE *arquivo = fopen("palavras.bin", "rb");
    if (arquivo == NULL) {
        printf("Nenhum arquivo encontrado. Iniciando lista vazia.\n");
        *Tamanho = 0;
        *Lista = NULL;
        return;
    }

    Pergunta temp;
    *Tamanho = 0;

    while (fread(&temp, sizeof(Pergunta), 1, arquivo) == 1) {
        Pergunta *nova_lista = realloc(*Lista, (*Tamanho + 1) * sizeof(Pergunta));
        if (nova_lista == NULL) {
            perror("Erro ao alocar memória");
            fclose(arquivo);
            free(*Lista);
            *Lista = NULL;
            *Tamanho = 0;
            return;
        }
        *Lista = nova_lista;
        (*Lista)[*Tamanho] = temp;
        (*Tamanho)++;
    }

    fclose(arquivo);
    printf("%zu palavras carregadas do arquivo!\n", *Tamanho);
}

void Salvar_Palavras(Pergunta *Lista, size_t Tamanho) {
    FILE *arquivo = fopen("palavras.bin", "wb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para salvar");
        return;
    }

    if (Tamanho > 0) {
        size_t escritos = fwrite(Lista, sizeof(Pergunta), Tamanho, arquivo);
        if (escritos != Tamanho) {
            perror("Erro ao escrever no arquivo");
        } else {
            printf("Arquivo salvo com sucesso! (%zu palavras)\n", Tamanho);
        }
    } else {
        printf("Nenhuma palavra para salvar.\n");
    }

    fclose(arquivo);
}

void Exportar_Arquivo(Pergunta Lista[], size_t Tamanho) {
    // Exportar para arquivo único (mantendo a função original)
    FILE* arquivo = fopen("Palavras.csv", "w");
    if (arquivo == NULL){
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    //fprintf(arquivo, "Palavra,Dica,Dificuldade\n");
    for (size_t i = 0; i < Tamanho; i++) {
        fprintf(arquivo, "%s,%s,%d\n", Lista[i].palavra, Lista[i].dica, Lista[i].dificuldade);
    }
    fclose(arquivo);
    printf("Arquivo Palavras.csv salvo com sucesso!\n");

    // Criar arquivos separados por dificuldade
    Exportar_Por_Dificuldade(Lista, Tamanho);
}

// Nova função para exportar por dificuldade
void Exportar_Por_Dificuldade(Pergunta Lista[], size_t Tamanho) {
    FILE* arquivo_dificuldade1 = fopen("Palavras_Dificuldade1.csv", "w");
    FILE* arquivo_dificuldade2 = fopen("Palavras_Dificuldade2.csv", "w");
    
    if (arquivo_dificuldade1 == NULL || arquivo_dificuldade2 == NULL) {
        perror("Erro ao abrir os arquivos de dificuldade");
        if (arquivo_dificuldade1) fclose(arquivo_dificuldade1);
        if (arquivo_dificuldade2) fclose(arquivo_dificuldade2);
        return;
    }

    // Cabeçalhos dos arquivos
    fprintf(arquivo_dificuldade1, "Palavra,Dica,Dificuldade\n");
    fprintf(arquivo_dificuldade2, "Palavra,Dica,Dificuldade\n");

    int count_dificuldade1 = 0;
    int count_dificuldade2 = 0;

    // Filtrar e salvar palavras por dificuldade
    for (size_t i = 0; i < Tamanho; i++) {
        int tamanho_palavra = strlen(Lista[i].palavra);
        
        if (Lista[i].dificuldade == 1 && tamanho_palavra <= 5) {
            fprintf(arquivo_dificuldade1, "%s,%s,%d\n", 
                   Lista[i].palavra, Lista[i].dica, Lista[i].dificuldade);
            count_dificuldade1++;
        }
        else if (Lista[i].dificuldade == 2 && tamanho_palavra <= 9) {
            fprintf(arquivo_dificuldade2, "%s,%s,%d\n", 
                   Lista[i].palavra, Lista[i].dica, Lista[i].dificuldade);
            count_dificuldade2++;
        }
    }

    fclose(arquivo_dificuldade1);
    fclose(arquivo_dificuldade2);

    printf("Arquivos por dificuldade criados com sucesso!\n");
    printf("- Palavras_Dificuldade1.csv: %d palavras (dificuldade 1, até 5 letras)\n", count_dificuldade1);
    printf("- Palavras_Dificuldade2.csv: %d palavras (dificuldade 2, até 9 letras)\n", count_dificuldade2);
}
