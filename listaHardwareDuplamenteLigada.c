#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista Lista;
typedef struct hardware Hardware;

struct lista
{
    Hardware *primeiro;
    int indice;
};

struct hardware
{
    char nome[50];
    int cdp;
    float preco;
    Hardware *proximo;
};

Lista *criarLista();
void inserirElementoFim(Lista *lista, char *nome, int cdp, float preco);
void listarElementos(Lista *lista);
void removerElemento(Lista *lista, int cdp);
void removerElementoNome(Lista *lista, char nome[]);
Hardware *buscarElemento(Lista *lista, int cdp);
int tamanho(Lista *lista);
void excluirLista(Lista *lista);
void atualizarElemento(Lista *lista, int cdp, char nome[], float preco);
void inserirElementoID(Lista *lista, int cdp, char nome[], float preco, int indice);
void listarElementosOrdemInversa(Lista *lista);
void exibirMenu();

int main()
{
    Lista *lista = criarLista();
    int escolha = 0;

    do
    {
        exibirMenu();
        scanf("%d", &escolha);
        getchar(); // Captura o caractere de nova linha após a leitura da escolha

        switch (escolha)
        {
        case 1:
        {
            char nome[50];
            int cdp;
            float preco;

            printf("Digite o nome do hardware: ");
            fgets(nome, 50, stdin);
            nome[strcspn(nome, "\n")] = '\0'; // Remove o caractere de nova linha

            printf("Digite o CDP do hardware: ");
            scanf("%d", &cdp);

            printf("Digite o preco do hardware: ");
            scanf("%f", &preco);

            inserirElementoFim(lista, nome, cdp, preco);
            printf("Hardware inserido com sucesso!\n");
            break;
        }
        case 2:
        {
            listarElementos(lista);
            break;
        }
        case 3:
        {
            int cdp;
            printf("Digite o CDP do hardware a ser removido: ");
            scanf("%d", &cdp);
            removerElemento(lista, cdp);
            break;
        }
        case 4:
        {
            char nome[50];
            printf("Digite o nome do hardware a ser removido: ");
            fgets(nome, 50, stdin);
            nome[strcspn(nome, "\n")] = '\0'; // Remove o caractere de nova linha
            removerElementoNome(lista, nome);
            break;
        }
        case 5:
        {
            int cdp;
            printf("Digite o CDP do hardware a ser buscado: ");
            scanf("%d", &cdp);
            Hardware *elemento = buscarElemento(lista, cdp);
            if (elemento)
            {
                printf("Elemento encontrado:\n");
                printf("Nome: %s\n", elemento->nome);
                printf("CDP: %d\n", elemento->cdp);
                printf("Preco: %.2f\n", elemento->preco);
            }
            else
            {
                printf("Elemento nao encontrado.\n");
            }
            break;
        }
        case 6:
        {
            int cdp;
            char nome[50];
            float preco;

            printf("Digite o CDP do hardware a ser atualizado: ");
            scanf("%d", &cdp);

            printf("Digite o novo nome do hardware: ");
            fgets(nome, 50, stdin);
            nome[strcspn(nome, "\n")] = '\0'; // Remove o caractere de nova linha

            printf("Digite o novo preco do hardware: ");
            scanf("%f", &preco);

            atualizarElemento(lista, cdp, nome, preco);
            break;
        }
        case 7:
        {
            int cdp;
            char nome[50];
            float preco;
            int indice;

            printf("Digite o CDP do hardware: ");
            scanf("%d", &cdp);

            printf("Digite o nome do hardware: ");
            fgets(nome, 50, stdin);
            nome[strcspn(nome, "\n")] = '\0'; // Remove o caractere de nova linha

            printf("Digite o preco do hardware: ");
            scanf("%f", &preco);

            printf("Digite o indice do hardware: ");
            scanf("%d", &indice);

            inserirElementoID(lista, cdp, nome, preco, indice);
            break;
        }
        case 8:
        {
            listarElementosOrdemInversa(lista);
            break;
        }
        case 9:
        {
            int tam = tamanho(lista);
            printf("Tamanho da lista: %d\n", tam);
            break;
        }
        case 10:
        {
            excluirLista(lista);
            printf("Lista excluida com sucesso!\n");
            break;
        }
        case 0:
        {
            printf("Saindo...\n");
            break;
        }
        default:
        {
            printf("Opcao invalida!\n");
            break;
        }
        }

        printf("\n");

    } while (escolha != 0);

    return 0;
}

Lista *criarLista()
{
    Lista *novo = malloc(sizeof(Lista));
    if (!novo)
    {
        fprintf(stderr, "Erro: falha na alocacao de memoria.\n");
        return NULL;
    }
    novo->primeiro = NULL;
    return novo;
}

void inserirElementoFim(Lista *lista, char *nome, int cdp, float preco)
{
    Hardware *novo = malloc(sizeof(Hardware));

    if (!novo)
    {
        fprintf(stderr, "Erro: falha na alocacao de memoria.\n");
        return;
    }

    strncpy(novo->nome, nome, 49);
    novo->cdp = cdp;
    novo->preco = preco;
    novo->proximo = NULL;

    if (lista->primeiro == NULL)
    {
        lista->primeiro = novo;
    }
    else
    {
        Hardware *atual = lista->primeiro;
        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }
}

void listarElementos(Lista *lista)
{
    Hardware *atual = lista->primeiro;
    while (atual != NULL)
    {
        printf("Nome: %s\n", atual->nome);
        printf("CDP: %d\n", atual->cdp);
        printf("Preco: %.2f\n", atual->preco);
        printf("\n");
        atual = atual->proximo;
    }
}

void removerElemento(Lista *lista, int cdp)
{
    if (lista->primeiro == NULL)
    {
        return;
    }
    if (lista->primeiro->cdp == cdp)
    {
        Hardware *removido = lista->primeiro;
        lista->primeiro = removido->proximo;
        free(removido);
    }
    else
    {
        Hardware *anterior = lista->primeiro;
        Hardware *atual = anterior->proximo;
        while (atual != NULL)
        {
            if (atual->cdp == cdp)
            {
                anterior->proximo = atual->proximo;
                free(atual);
                return;
            }
            anterior = atual;
            atual = atual->proximo;
        }
    }
}

void removerElementoNome(Lista *lista, char nome[])
{
    Hardware *atual = lista->primeiro;
    Hardware *anterior = NULL;

    while (atual != NULL && strcmp(atual->nome, nome) != 0)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL)
    {
        printf("Erro: hardware com nome %s nao encontrado.\n", nome);
        return;
    }

    if (anterior == NULL)
    {
        lista->primeiro = atual->proximo;
    }
    else
    {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Hardware com nome %s removido com sucesso.\n", nome);
}

Hardware *buscarElemento(Lista *lista, int cdp)
{
    Hardware *atual = lista->primeiro;
    while (atual)
    {
        if (atual->cdp == cdp)
        {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

int tamanho(Lista *lista)
{
    int tamanho = 0;
    Hardware *atual = lista->primeiro;
    while (atual)
    {
        tamanho++;
        atual = atual->proximo;
    }
    return tamanho;
}

void excluirLista(Lista *lista)
{
    Hardware *atual = lista->primeiro;
    while (atual)
    {
        Hardware *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    lista->primeiro = NULL;
}

void atualizarElemento(Lista *lista, int cdp, char nome[], float preco)
{
    Hardware *atual = lista->primeiro;

    while (atual != NULL && atual->cdp != cdp)
    {
        atual = atual->proximo;
    }

    if (atual != NULL)
    {
        strcpy(atual->nome, nome);
        atual->preco = preco;
        printf("Hardware de CDP %d atualizado com sucesso.\n", cdp);
    }
    else
    {
        printf("\nErro: hardware de CDP %d nao encontrado.\n", cdp);
    }
}

void inserirElementoID(Lista *lista, int cdp, char nome[], float preco, int indice)
{
    Hardware *novo = malloc(sizeof(Hardware));

    if (!novo)
    {
        printf("Erro: falha na alocacao de memoria.\n");
        return;
    }

    novo->cdp = cdp;
    novo->preco = preco;
    strcpy(novo->nome, nome);

    Hardware *anterior = NULL;
    Hardware *atual = lista->primeiro;
    int posicao = 0;

    while (atual != NULL && posicao != indice)
    {
        anterior = atual;
        atual = atual->proximo;
        posicao++;
    }

    if (posicao != indice)
    {
        printf("Erro: posicao %d fora do limite da lista.\n", indice);
        free(novo);
        return;
    }

    if (anterior == NULL)
    {
        novo->proximo = lista->primeiro;
        lista->primeiro = novo;
    }
    else
    {
        novo->proximo = atual;
        anterior->proximo = novo;
    }

    printf("Hardware inserido com sucesso na posicao %d.\n", indice);
}

void listarElementosOrdemInversa(Lista *lista)
{
    if (lista == NULL || lista->primeiro == NULL)
    {
        printf("Lista vazia.\n");
        return;
    }

    Hardware *atual = lista->primeiro;
    Hardware *anterior = NULL;
    Hardware *proximo = NULL;

    while (atual != NULL)
    {
        proximo = atual->proximo;
        atual->proximo = anterior;
        anterior = atual;
        atual = proximo;
    }

    printf("Elementos da lista em ordem inversa:\n");
    atual = anterior;
    while (atual != NULL)
    {
        printf("Nome: %s\n", atual->nome);
        printf("CDP: %d\n", atual->cdp);
        printf("Preco: %.2f\n", atual->preco);
        printf("\n");
        atual = atual->proximo;
    }
}

void exibirMenu()
{
    printf("----- MENU -----\n");
    printf("1. Inserir elemento\n");
    printf("2. Listar elementos\n");
    printf("3. Remover elemento por CDP\n");
    printf("4. Remover elemento por nome\n");
    printf("5. Buscar elemento por CDP\n");
    printf("6. Atualizar elemento\n");
    printf("7. Inserir elemento em posicao especifica\n");
    printf("8. Listar elementos em ordem inversa\n");
    printf("9. Tamanho da lista\n");
    printf("10. Excluir lista\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}
