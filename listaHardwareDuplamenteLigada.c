#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista Lista;
typedef struct hardware Hardware;

struct lista {
    Hardware *primeiro;
};

struct hardware {
    char nome[50];
    int cdp;
    float preco;
    Hardware *proximo;
    Hardware *anterior;
};

void insereInicio(Lista *l, char nome[], int cdp, float preco) {
    Hardware *novo_hardware = (Hardware *) malloc(sizeof(Hardware));
    strcpy(novo_hardware->nome, nome);
    novo_hardware->cdp = cdp;
    novo_hardware->preco = preco;
    novo_hardware->proximo = l->primeiro;
    novo_hardware->anterior = NULL;
    if (l->primeiro != NULL) {
        l->primeiro->anterior = novo_hardware;
    }
    l->primeiro = novo_hardware;
}

void insereFim(Lista *l, char nome[], int cdp, float preco) {
    Hardware *novo_hardware = (Hardware *) malloc(sizeof(Hardware));
    strcpy(novo_hardware->nome, nome);
    novo_hardware->cdp = cdp;
    novo_hardware->preco = preco;
    novo_hardware->proximo = NULL;
    if (l->primeiro == NULL) {
        novo_hardware->anterior = NULL;
        l->primeiro = novo_hardware;
        return;
    }
    Hardware *atual = l->primeiro;
    while (atual->proximo != NULL) {
        atual = atual->proximo;
    }
    atual->proximo = novo_hardware;
    novo_hardware->anterior = atual;
}

void removeHardware(Lista *l, int cdp) {
    if (l->primeiro == NULL) {
        return;
    }
    Hardware *atual = l->primeiro;
    while (atual != NULL && atual->cdp != cdp) {
        atual = atual->proximo;
    }
    if (atual == NULL) {
        return;
    }
    if (atual->anterior != NULL) {
        atual->anterior->proximo = atual->proximo;
    } else {
        l->primeiro = atual->proximo;
    }
    if (atual->proximo != NULL) {
        atual->proximo->anterior = atual->anterior;
    }
    free(atual);
}

void imprimeLista(Lista *l) {
    Hardware *atual = l->primeiro;
    while (atual != NULL) {
        printf("Nome: %s\n", atual->nome);
        printf("CDP: %d\n", atual->cdp);
        printf("Preco: %.2f\n", atual->preco);
        atual = atual->proximo;
    }
}

int main() {
    Lista *lista_hardware = (Lista *) malloc(sizeof(Lista));
    lista_hardware->primeiro = NULL;
    
    insereInicio(lista_hardware, "Processador Intel Core i7", 123, 1200.50);
    insereFim(lista_hardware, "Placa de Video NVIDIA GeForce GTX 1080", 456, 2500.00);
    insereInicio(lista_hardware, "Memoria RAM Kingston 8GB DDR4", 789, 350.00);
    
    imprimeLista(lista_hardware);
    
    removeHardware(lista_hardware, 56);

printf("\nLista apos remocao:\n");
imprimeLista(lista_hardware);

return 0;
}
