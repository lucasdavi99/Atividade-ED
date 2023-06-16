#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct hardware Hardware;
typedef struct fila Fila;

struct hardware {
    char nome[50];
    int cdp;
    float preco;
};

struct fila {
    Hardware *elementos;
    int capacidade;
    int tamanho;
    int frente;
    int tras;
};

/*A função criarFila aloca dinamicamente um 
vetor de elementos com base na capacidade 
desejada e inicializa os demais campos da estrutura Fila.*/
Fila criarFila(int capacidade) {
    Fila fila;
    fila.elementos = (Hardware*)malloc(capacidade * sizeof(Hardware));
    fila.capacidade = capacidade;
    fila.tamanho = 0;
    fila.frente = 0;
    fila.tras = -1;
    return fila;
}

/*A função enqueue insere um novo elemento na traseira da fila, 
usando aritmética modular para calcular 
o novo índice da traseira e garantir que a fila seja circular.*/
void enqueue(Fila *fila, Hardware hardware) {
    if (fila->tamanho == fila->capacidade) {
        printf("A fila esta cheia. Nao e possível adicionar mais elementos.\n");
        return;
    }
    
    fila->tras = (fila->tras + 1) % fila->capacidade;
    fila->elementos[fila->tras] = hardware;
    fila->tamanho++;
}

/*A função dequeue remove o elemento da frente da fila, armazenando-o em uma variável temporária. 
O novo índice da frente é calculado usando aritmética modular, 
e o tamanho da fila é atualizado.*/
Hardware dequeue(Fila *fila) {
    if (fila->tamanho == 0) {
        printf("A fila esta vazia. Nao e possível remover elementos.\n");
        Hardware hardware_vazio;
        memset(&hardware_vazio, 0, sizeof(Hardware));
        return hardware_vazio;
    }
    
    Hardware hardware_removido = fila->elementos[fila->frente];
    fila->frente = (fila->frente + 1) % fila->capacidade;
    fila->tamanho--;
    
    return hardware_removido;
}

/*A função excluirFila libera a memória alocada para o vetor de elementos da fila.*/
void excluirFila(Fila *fila) {
    free(fila->elementos);
    fila->capacidade = 0;
    fila->tamanho = 0;
    fila->frente = 0;
    fila->tras = -1;
}

/*A função exibirFila percorre os elementos da fila usando um laço 
for e calcula o índice real do elemento usando aritmética modular.*/
void exibirFila(Fila fila) {
    if (fila.tamanho == 0) {
        printf("A fila está vazia.\n");
        return;
    }
    
    printf("Elementos na fila:\n");
    int i;
    for (i = 0; i < fila.tamanho; i++) {
        int index = (fila.frente + i) % fila.capacidade;
        printf("Nome: %s\n", fila.elementos[index].nome);
        printf("CDP: %d\n", fila.elementos[index].cdp);
        printf("Preco: %.2f\n", fila.elementos[index].preco);
        printf("\n");
    }
}


/*Aqui e feito a chamada de todas as funções, 
optei fazer um menu onde o usuário possa interagir com as funções*/
int main() {
    Fila fila = criarFila(5);
    
    int opcao = 0;
    
    while (opcao != 4) {
        printf("=== MENU ===\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Exibir Fila\n");
        printf("4. Sair\n");
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: {
                printf("Digite o nome do hardware: ");
                scanf("%s", fila.elementos[(fila.tras + 1) % fila.capacidade].nome);
                printf("Digite o CDP do hardware: ");
                scanf("%d", &fila.elementos[(fila.tras + 1) % fila.capacidade].cdp);
                printf("Digite o preco do hardware: ");
                scanf("%f", &fila.elementos[(fila.tras + 1) % fila.capacidade].preco);
                
                enqueue(&fila, fila.elementos[(fila.tras + 1) % fila.capacidade]);
                
                printf("Hardware adicionado a fila.\n\n");
                break;
            }
            case 2: {
                Hardware hardware_removido = dequeue(&fila);
                printf("Elemento removido da fila:\n");
                printf("Nome: %s\n", hardware_removido.nome);
                printf("CDP: %d\n", hardware_removido.cdp);
                printf("Preco: %.2f\n", hardware_removido.preco);
                printf("\n");
                break;
            }
            case 3: {
                exibirFila(fila);
                break;
            }
            case 4: {
                excluirFila(&fila);
                printf("Fila excluida. Encerrando o programa.\n");
                break;
            }
            default: {
                printf("Opcao invalida. Por favor, tente novamente.\n");
                break;
            }
        }
    }
    
    return 0;
}
