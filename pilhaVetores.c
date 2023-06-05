/*Aluno: Lucas Davi da Silva Paix√£o
  Turma: ADS000302B 
  Turno: Noite


  Pilha com Vetores
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int *data;
    int top;
} Pilha;

Pilha *criarPilha() {
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
    pilha->data = (int *)malloc(MAX_SIZE * sizeof(int));
    pilha->top = -1;
    return pilha;
}

int ehVazia(Pilha *pilha) {
    return pilha->top == -1;
}

int verTopo(Pilha *pilha) {
    if (ehVazia(pilha)) {
        printf("A pilha esta vazia.\n");
        return -1;
    }
    return pilha->data[pilha->top];
}

void push(Pilha *pilha, int elemento) {
    if (pilha->top == MAX_SIZE - 1) {
        printf("A pilha esta cheia. Nao e possÌvel inserir o elemento %d.\n", elemento);
        return;
    }
    pilha->data[++(pilha->top)] = elemento;
    printf("Elemento %d inserido na pilha.\n", elemento);
}

void pop(Pilha *pilha) {
    if (ehVazia(pilha)) {
        printf("A pilha esta vazia. Nao e possivel remover nenhum elemento.\n");
        return;
    }
    printf("Elemento %d removido da pilha.\n", pilha->data[pilha->top]);
    --(pilha->top);
}

void excluirPilha(Pilha *pilha) {
    free(pilha->data);
    free(pilha);
    printf("Pilha excluida.\n");
}

void exibirMenu() {
    printf("\n==== Menu ====\n");
    printf("1. Inserir elemento\n");
    printf("2. Remover elemento\n");
    printf("3. Verificar elemento do topo\n");
    printf("4. Verificar se a pilha esta vazia\n");
    printf("5. Excluir pilha\n");
    printf("0. Sair\n");
    printf("==============\n");
}

int main() {
    Pilha *pilha = criarPilha();
    int escolha, elemento;

    do {
        exibirMenu();
        printf("Digite a opcao desejada: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("Digite o elemento a ser inserido: ");
                scanf("%d", &elemento);
                push(pilha, elemento);
                break;
            case 2:
                pop(pilha);
                break;
            case 3:
                printf("Elemento do topo da pilha: %d\n", verTopo(pilha));
                break;
            case 4:
                printf("A pilha %s vazia.\n", ehVazia(pilha) ? "esta" : "nao esta");
                break;
            case 5:
                excluirPilha(pilha);
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida. Digite novamente.\n");
                break;
        }
    } while (escolha != 0);

    return 0;
}
