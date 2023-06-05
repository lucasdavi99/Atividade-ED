/*Aluno: Lucas Davi da Silva Paixão
  Turma: ADS000302B 
  Turno: Noite


  Lista Encadeada
*/

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



// Função para criar uma nova lista vazia
Lista *criarLista() {
    Lista *novo = malloc(sizeof(Lista)); // Aloca memória para a lista
    if (!novo) { // Verifica se a alocação falhou
        fprintf(stderr, "Erro: falha na alocacao de memoria.\n");
        return NULL; // Retorna NULL em caso de falha
    }
    novo->primeiro = NULL; // Inicializa o ponteiro para o primeiro nó como NULL
    return novo; // Retorna a lista vazia criada
}

/*Função para inserir um elemento no final da lista*/
void inserirElementoFim(Lista *lista, char *nome, int cdp, float preco) {
    // Alocando memória para um novo elemento da lista
    Hardware *novo = malloc(sizeof(Hardware));

    // Verificando se a alocação de memória foi bem-sucedida
    if (!novo) {
        // Se não foi, exibe uma mensagem de erro e retorna da função
        fprintf(stderr, "Erro: falha na alocacao de memoria.\n");
        return;
    }

    // Copiando o nome do hardware para o campo correspondente do novo elemento
    strncpy(novo->nome, nome, 49);

    // Armazenando o CDP e o preço no novo elemento
    novo->cdp = cdp;
    novo->preco = preco;

    // Definindo o próximo elemento como nulo, já que o novo elemento será o último da lista
    novo->proximo = NULL;

    // Verificando se a lista está vazia
    if (lista->primeiro == NULL) {
        // Se estiver, o novo elemento é definido como o primeiro da lista
        lista->primeiro = novo;
    } else {
        // Se não estiver, percorre-se a lista até encontrar o último elemento
        Hardware *atual = lista->primeiro;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        // Definindo o próximo do último elemento como o novo elemento
        atual->proximo = novo;
    }
}

/*Função para listar todos os elementos*/
void listarElementos(Lista *lista) {
    Hardware *atual = lista->primeiro;
    while (atual != NULL) {
        printf("Nome: %s\n", atual->nome);
        printf("CDP: %d\n", atual->cdp);
        printf("Preco: %.2f\n", atual->preco);
        printf("\n");
        atual = atual->proximo;
    }
}

/*Função para remover algum elemento*/
void removerElemento(Lista *lista, int cdp) {
    if (lista->primeiro == NULL) {
        return;  // lista vazia
    }
    if (lista->primeiro->cdp == cdp) {
        // remover o primeiro elemento da lista
        Hardware *removido = lista->primeiro;
        lista->primeiro = removido->proximo;
        free(removido);
    } else {
        // procurar o elemento a ser removido
        Hardware *anterior = lista->primeiro;
        Hardware *atual = anterior->proximo;
        while (atual != NULL) {
            if (atual->cdp == cdp) {
                anterior->proximo = atual->proximo;
                free(atual);
                return;
            }
            anterior = atual;
            atual = atual->proximo;
        }
    }
}

/*Função para remover algum elemento pelo seu nome*/
void removerElementoNome(Lista *lista, char nome[]) {
    Hardware *atual = lista->primeiro;
    Hardware *anterior = NULL;

    // Procura o elemento a ser removido na lista
    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    // Se o elemento não foi encontrado, exibe uma mensagem de erro e retorna
    if (atual == NULL) {
        printf("Erro: hardware com nome %s nao encontrado.\n", nome);
        return;
    }

    // Se o elemento é o primeiro da lista, atualiza o ponteiro para o primeiro elemento
    if (anterior == NULL) {
        lista->primeiro = atual->proximo;
    } else {
        // Se o elemento não é o primeiro da lista, atualiza o ponteiro do elemento anterior
        anterior->proximo = atual->proximo;
    }

    // Libera a memória do elemento removido
    free(atual);
    printf("Hardware com nome %s removido com sucesso.\n", nome);
}


/*Função para buscar/localizar elementos*/
Hardware *buscarElemento(Lista *lista, int cdp) {
    Hardware *atual = lista->primeiro;
    while (atual) {
        if (atual->cdp == cdp) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

/*retorna o tamanho da lista*/
int tamanho(Lista *lista) {
    int tamanho = 0;
    Hardware *atual = lista->primeiro;
    while (atual) {
        tamanho++;
        atual = atual->proximo;
    }
    return tamanho;
}

/*Deleta a Lista*/
void excluirLista(Lista *lista) {
    Hardware *atual = lista->primeiro;
    while (atual) {
        Hardware *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    lista->primeiro = NULL;
}

/*Função para atualizar o elemento*/
void atualizarElemento(Lista *lista, int cdp, char nome[], float preco) {
    Hardware *atual = lista->primeiro;

    // Procura o elemento com o CDP informado
    while (atual != NULL && atual->cdp != cdp) {
        atual = atual->proximo;
    }

    // Se o elemento foi encontrado, atualiza seus campos
    if (atual != NULL) {
        strcpy(atual->nome, nome);
        atual->preco = preco;
        printf("Hardware de CDP %d atualizado com sucesso.\n", cdp);
    } else {
        printf("\nErro: hardware de CDP %d nao encontrado.\n", cdp);
    }
}

void inserirElementoID(Lista *lista, int cdp, char nome[], float preco, int indice) {
    Hardware *novo = malloc(sizeof(Hardware)); // Aloca memória para o novo elemento
    if (!novo) { // Verifica se a alocação foi bem sucedida
        printf("Erro: falha na alocação de memória.\n");
        return;
    }

    novo->cdp = cdp; // Atribui os valores para os campos do novo elemento
    novo->preco = preco;
    strcpy(novo->nome, nome);

    Hardware *anterior = NULL; // Inicializa ponteiros para o elemento anterior e o atual da lista
    Hardware *atual = lista->primeiro;
    int posicao = 0; // Inicializa a variável que representa a posição na lista

    while (atual != NULL && posicao != indice) { // Percorre a lista até chegar na posição desejada ou no fim da lista
        anterior = atual; // Salva o elemento atual como o elemento anterior
        atual = atual->proximo; // Vai para o próximo elemento da lista
        posicao++; // Incrementa a variável que representa a posição
    }

    if (posicao != indice) { // Verifica se a posição encontrada é a desejada
        printf("Erro: posicao %d fora do limite da lista.\n", indice);
        free(novo); // Libera a memória alocada para o novo elemento
        return;
    }

    if (anterior == NULL) { // Caso o elemento seja inserido na primeira posição da lista
        novo->proximo = lista->primeiro;
        lista->primeiro = novo;
    } else { // Caso o elemento seja inserido em qualquer outra posição
        novo->proximo = atual;
        anterior->proximo = novo;
    }

    printf("Hardware inserido com sucesso na posicao %d.\n", indice);
}



/*Aqui é chamada as funções*/
int main() {
    Lista *lista = criarLista();
    int opcao = 0;
    char nome[50];
    int cdp;
    float preco;
    int indice;

    do {
        printf("\n---Menu---\n");
        printf("1. Inserir hardware\n");
        printf("2. Listar hardware\n");
        printf("3. Remover hardware por CDP\n");
        printf("4. Remover hardware por nome\n");
        printf("5. Buscar hardware\n");
        printf("6. Atualizar hardware\n");
        printf("7. Inserir hardware em posicao especifica\n");
        printf("8. Tamanho da lista\n");
        printf("9. Excluir lista\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                printf("Nome do hardware: ");
                scanf("%s", nome);
                printf("CDP: ");
                scanf("%d", &cdp);
                printf("Preco: ");
                scanf("%f", &preco);
                inserirElementoFim(lista, nome, cdp, preco);
                break;
            case 2:
                listarElementos(lista);
                break;
            case 3:
                printf("CDP do hardware a ser removido: ");
                scanf("%d", &cdp);
                removerElemento(lista, cdp);
                break;
            case 4:
                printf("Nome do hardware a ser removido: ");
                scanf("%s", nome);
                removerElementoNome(lista, nome);
                break;
            case 5:
                printf("CDP do hardware a ser buscado: ");
                scanf("%d", &cdp);
                Hardware *elemento = buscarElemento(lista, cdp);
                if (elemento) {
                    printf("Elemento encontrado:\n");
                    printf("Nome: %s\n", elemento->nome);
                    printf("CDP: %d\n", elemento->cdp);
                    printf("Preco: %.2f\n", elemento->preco);
                } else {
                    printf("Elemento nao encontrado.\n");
                }
                break;
            case 6:
                printf("CDP do hardware a ser atualizado: ");
                scanf("%d", &cdp);
                printf("Nome do hardware: ");
                scanf("%s", nome);
                printf("Preco: ");
                scanf("%f", &preco);
                atualizarElemento(lista, cdp, nome, preco);
                break;
            case 7:
                printf("Nome do hardware: ");
                scanf("%s", nome);
                printf("CDP: ");
                scanf("%d", &cdp);
                printf("Preco: ");
                scanf("%f", &preco);
                printf("Indice: ");
                scanf("%d", &indice);
                inserirElementoID(lista, cdp, nome, preco, indice);
                break;
            case 8:
                printf("Tamanho da lista: %d\n", tamanho(lista));
                break;
            case 9:
                excluirLista(lista);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
