/*Aluno: Lucas Davi da Silva Paix√£o
  Turma: ADS000302B 
  Turno: Noite


  Lista circular
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista Lista;
typedef struct hardware Hardware;

struct lista
{
    Hardware *primeiro;
    Hardware *ultimo;
    int indice;
};

struct hardware
{
    char nome[50];
    int cdp;
    float preco;
    Hardware *proximo;
};



// Fun√ß√£o para criar uma nova lista vazia
Lista *criarLista() {
    Lista *novo = malloc(sizeof(Lista)); // Aloca mem√≥ria para a lista
    if (!novo) { // Verifica se a aloca√ß√£o falhou
        fprintf(stderr, "Erro: falha na alocacao de memoria.\n");
        return NULL; // Retorna NULL em caso de falha
    }
    novo->primeiro = NULL; // Inicializa o ponteiro para o primeiro n√≥ como NULL
    return novo; // Retorna a lista vazia criada
}

/*Fun√ß√£o para inserir um elemento no final da lista*/
void inserirElementoFim(Lista *lista, char *nome, int cdp, float preco) {
    Hardware *novo = malloc(sizeof(Hardware));
    if (!novo) {
        fprintf(stderr, "Erro: falha na alocaÁ„o de memÛria.\n");
        return;
    }

    // Copiando o nome do hardware para o campo correspondente do novo elemento
    strncpy(novo->nome, nome, 49);

    // Armazenando o CDP e o preÁo no novo elemento
    novo->cdp = cdp;
    novo->preco = preco;

    // Verificando se a lista est· vazia
    if (lista->primeiro == NULL) {
        lista->primeiro = novo;
        lista->ultimo = novo;
        novo->proximo = novo;  // O ˙nico elemento na lista aponta para si mesmo
    } else {
        novo->proximo = lista->primeiro;  // O novo elemento aponta para o primeiro elemento atual
        lista->ultimo->proximo = novo;  // O ˙ltimo elemento aponta para o novo elemento
        lista->ultimo = novo;  // O novo elemento È definido como o ˙ltimo elemento
    }
}



/*Fun√ß√£o para listar todos os elementos*/
void listarElementos(Lista *lista) {
    if (lista->primeiro == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    Hardware *atual = lista->primeiro;
    do {
        printf("Nome: %s\n", atual->nome);
        printf("CDP: %d\n", atual->cdp);
        printf("Preco: %.2f\n", atual->preco);
        printf("\n");
        atual = atual->proximo;
    } while (atual != lista->primeiro);
}

/*Fun√ß√£o para remover algum elemento*/
void removerElemento(Lista *lista, int cdp) {
    if (lista->primeiro != NULL) {
        Hardware *anterior = NULL;
        Hardware *atual = lista->primeiro;

        do {
            if (atual->cdp == cdp) {
                if (anterior == NULL) {
                    lista->primeiro = atual->proximo;
                } else {
                    anterior->proximo = atual->proximo;
                }

                // precisamos atualizar o ˙ltimo se for removido
                if (atual == lista->ultimo) {
                    lista->ultimo = anterior;
                }

                free(atual);
                return;
            }

            anterior = atual;
            atual = atual->proximo;
        } while (atual != lista->primeiro); // Note que nÛs agora paramos quando voltamos ao inÌcio devido ‡ natureza circular da lista
    }

    printf("Hardware com CDP %d n„o encontrado.\n", cdp);
}


/*Fun√ß√£o para remover algum elemento pelo seu nome*/
void removerElementoNome(Lista *lista, char nome[]) {
    Hardware *atual = lista->primeiro;
    Hardware *anterior = NULL;

    // Procura o elemento a ser removido na lista
    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    // Se o elemento n√£o foi encontrado, exibe uma mensagem de erro e retorna
    if (atual == NULL) {
        printf("Erro: hardware com nome %s nao encontrado.\n", nome);
        return;
    }

    // Se o elemento √© o primeiro da lista, atualiza o ponteiro para o primeiro elemento
    if (anterior == NULL) {
        lista->primeiro = atual->proximo;
    } else {
        // Se o elemento n√£o √© o primeiro da lista, atualiza o ponteiro do elemento anterior
        anterior->proximo = atual->proximo;
    }

    // Libera a mem√≥ria do elemento removido
    free(atual);
    printf("Hardware com nome %s removido com sucesso.\n", nome);
}


/*Fun√ß√£o para buscar/localizar elementos*/
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

    if (lista->primeiro == NULL) {
        return tamanho;
    }

    Hardware *atual = lista->primeiro;

    do {
        tamanho++;
        atual = atual->proximo;
    } while (atual != lista->primeiro);

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

/*Fun√ß√£o para atualizar o elemento*/
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
    Hardware *novo = malloc(sizeof(Hardware)); // Aloca memÛria para o novo elemento
    if (!novo) { // Verifica se a alocaÁ„o foi bem sucedida
        printf("Erro: falha na alocaÁ„o de memÛria.\n");
        return;
    }

    novo->cdp = cdp; // Atribui os valores para os campos do novo elemento
    novo->preco = preco;
    strcpy(novo->nome, nome);

    Hardware *anterior = NULL; // Inicializa ponteiros para o elemento anterior e o atual da lista
    Hardware *atual = lista->primeiro;
    int posicao = 0; // Inicializa a vari·vel que representa a posiÁ„o na lista

    while (atual != NULL && posicao != indice) { // Percorre a lista atÈ chegar na posiÁ„o desejada ou no fim da lista
        anterior = atual; // Salva o elemento atual como o elemento anterior
        atual = atual->proximo; // Vai para o prÛximo elemento da lista
        posicao++; // Incrementa a vari·vel que representa a posiÁ„o
    }

    if (posicao != indice) { // Verifica se a posiÁ„o encontrada È a desejada
        printf("Erro: posicao %d fora do limite da lista.\n", indice);
        free(novo); // Libera a memÛria alocada para o novo elemento
        return;
    }

    if (anterior == NULL) { // Caso o elemento seja inserido na primeira posiÁ„o da lista
        novo->proximo = lista->primeiro;
        lista->primeiro = novo;
    } else { // Caso o elemento seja inserido em qualquer outra posiÁ„o
        novo->proximo = atual;
        anterior->proximo = novo;
    }

    printf("Hardware inserido com sucesso na posiÁ„o %d.\n", indice);
}




void menu(Lista *lista) {
    int indice;
	int opcao, cdp;
    char nome[50];
    float preco;

    do {
        printf("\n---- MENU ----\n");
        printf("1. Inserir elemento\n");
        printf("2. Listar elementos\n");
        printf("3. Remover elemento\n");
        printf("4. Atualizar elemento\n");
        printf("5. Buscar elemento\n");
        printf("6. Tamanho da lista\n");
        printf("7. Inserir elemento em posicao especifica\n");
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
                printf("CDP do hardware a remover: ");
                scanf("%d", &cdp);
                removerElemento(lista, cdp);
                break;
            case 4:
                printf("CDP do hardware a atualizar: ");
                scanf("%d", &cdp);
                printf("Novo nome do hardware: ");
                scanf("%s", nome);
                printf("Novo pre√ßo: ");
                scanf("%f", &preco);
                atualizarElemento(lista, cdp, nome, preco);
                break;
            case 5:
                printf("CDP do hardware a buscar: ");
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
                printf("Tamanho da lista: %d\n", tamanho(lista));
                break;
            case 7:
                printf("Nome do hardware: ");
                scanf("%s", nome);
                printf("CDP: ");
                scanf("%d", &cdp);
                printf("Preco: ");
                scanf("%f", &preco);
                printf("Posicao de insercao: ");
                scanf("%d", &indice);
                inserirElementoID(lista, cdp, nome, preco, indice);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    // apos sair do loop do menu, exclui a lista
    excluirLista(lista);
}

int main() {
    // Criacao da lista
    Lista *lista = criarLista();

    // Chamar o menu
    menu(lista);

    return 0;
}