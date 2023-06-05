/*Aluno: Lucas Davi da Silva PaixÃ£o
  Turma: ADS000302B 
  Turno: Noite


  Pilha com Apontador
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} Pilha;

Pilha* criarPilha() {
    Pilha* pilha = (Pilha*)malloc(sizeof(Pilha));
    pilha->top = NULL;
    return pilha;
}

int ehVazia(Pilha* pilha) {
    return pilha->top == NULL;
}

int verTopo(Pilha* pilha) {
    if (ehVazia(pilha)) {
        printf("A pilha esta vazia.\n");
        return -1;
    }
    return pilha->top->data;
}

void push(Pilha* pilha, int elemento) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = elemento;
    newNode->next = pilha->top;
    pilha->top = newNode;
    printf("Elemento %d inserido na pilha.\n", elemento);
}

void pop(Pilha* pilha) {
    if (ehVazia(pilha)) {
        printf("A pilha esta vazia. Nao e possivel remover nenhum elemento.\n");
        return;
    }
    Node* temp = pilha->top;
    pilha->top = pilha->top->next;
    printf("Elemento %d removido da pilha.\n", temp->data);
    free(temp);
}

void excluirPilha(Pilha* pilha) {
    while (!ehVazia(pilha)) {
        pop(pilha);
    }
    free(pilha);
    printf("Pilha excluída.\n");
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
    Pilha* pilha = criarPilha();
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
