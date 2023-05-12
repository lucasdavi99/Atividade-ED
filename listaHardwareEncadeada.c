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

void inserirElementoFim(Lista *lista, char *nome, int cdp, float preco) {
    Hardware *novo = malloc(sizeof(Hardware));
    if (!novo) {
        fprintf(stderr, "Erro: falha na alocacao de memoria.\n");
        return;
    }
    strncpy(novo->nome, nome, 49);
    novo->cdp = cdp;
    novo->preco = preco;
    novo->proximo = NULL;

    if (lista->primeiro == NULL) {
        lista->primeiro = novo;
    } else {
        Hardware *atual = lista->primeiro;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }
}

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

void removerElementoNome(Lista *lista, char nome[]) {
    Hardware *atual = lista->primeiro;
    Hardware *anterior = NULL;

    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Erro: hardware com nome %s nao encontrado.\n", nome);
        return;
    }

    if (anterior == NULL) {
        lista->primeiro = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Hardware com nome %s removido com sucesso.\n", nome);
}


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

int tamanho(Lista *lista) {
    int tamanho = 0;
    Hardware *atual = lista->primeiro;
    while (atual) {
        tamanho++;
        atual = atual->proximo;
    }
    return tamanho;
}

void excluirLista(Lista *lista) {
    Hardware *atual = lista->primeiro;
    while (atual) {
        Hardware *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    lista->primeiro = NULL;
}

void atualizarElemento(Lista *lista, int cdp, char nome[], float preco) {
    Hardware *atual = lista->primeiro;

    while (atual != NULL && atual->cdp != cdp) {
        atual = atual->proximo;
    }

    if (atual != NULL) {
        strcpy(atual->nome, nome);
        atual->preco = preco;
        printf("Hardware de CDP %d atualizado com sucesso.\n", cdp);
    } else {
        printf("\nErro: hardware de CDP %d nao encontrado.\n", cdp);
    }
}

void inserirElementoID(Lista *lista, int cdp, char nome[], float preco, int indice) {
    Hardware *novo = malloc(sizeof(Hardware));
    if (!novo) {
        printf("Erro: falha na alocação de memória.\n");
        return;
    }

    novo->cdp = cdp;
    novo->preco = preco;
    strcpy(novo->nome, nome);

    Hardware *anterior = NULL;
    Hardware *atual = lista->primeiro;
    int posicao = 0;

    while (atual != NULL && posicao != indice) {
        anterior = atual;
        atual = atual->proximo;
        posicao++;
    }

    if (posicao != indice) {
        printf("Erro: posicao %d fora do limite da lista.\n", indice);
        free(novo);
        return;
    }

    if (anterior == NULL) {
        novo->proximo = lista->primeiro;
        lista->primeiro = novo;
    } else {
        novo->proximo = atual;
        anterior->proximo = novo;
    }

    printf("Hardware inserido com sucesso na posicao %d.\n", indice);
}



int main() {
    // Cria��o da lista
    Lista *lista = criarLista();
    
    // Insercao de elementos
    inserirElementoFim(lista, "Processador", 1, 300.0);
    inserirElementoFim(lista, "Memoria RAM", 2, 150.0);
    inserirElementoFim(lista, "Placa de Video", 3, 800.0);
    
    
    // Listagem de elementos
    printf("Lista de elementos:\n");
    listarElementos(lista);
    
    // Remocao de um elemento
    removerElemento(lista, 2);
    
    // Listagem de elementos novamente
    printf("Lista de elementos apos remocao:\n");
    listarElementos(lista);
    
    // Atualizacao de um elemento
    atualizarElemento(lista, 4, "Nova Placa M�e", 550.0);
    
    // Listagem de elementos novamente
    printf("Lista de elementos apos atualizacao:\n");
    listarElementos(lista);
    
    // Busca de um elemento
    Hardware *elemento = buscarElemento(lista, 3);
    if (elemento) {
        printf("Elemento encontrado:\n");
        printf("Nome: %s\n", elemento->nome);
        printf("CDP: %d\n", elemento->cdp);
        printf("Preco: %.2f\n", elemento->preco);
    } else {
        printf("Elemento nao encontrado.\n");
    }
    
    Lista *Hardware = criarLista();
    if (!Hardware) {
        return 1;
    }

    inserirElementoID(Hardware, 1234, "Teclado", 100.0, 2);

    
    // Tamanho da lista
    int tam = tamanho(lista);
    printf("Tamanho da lista: %d\n", tam);
    
    // Exclusao da lista
    excluirLista(lista);
    
    return 0;
}
