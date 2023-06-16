#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct hardware {
    char nome[50];
    int cdp;
    float preco;
    struct hardware* proximo;
} Hardware;

typedef struct fila {
    Hardware* primeiro;
    Hardware* ultimo;
} Fila;


/*A fun��o criarFila aloca dinamicamente a estrutura 
Fila e inicializa os apontadores primeiro e ultimo como NULL.*/
Fila* criarFila() {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    fila->primeiro = NULL;
    fila->ultimo = NULL;
    return fila;
}

/*A fun��o enqueue cria um novo elemento Hardware e o adiciona no final da fila. 
Se a fila estiver vazia, o novo elemento se torna o primeiro e o �ltimo. 
Caso contr�rio, o novo elemento � adicionado ap�s o �ltimo elemento existente e se torna o novo �ltimo.*/
void enqueue(Fila* fila, const char* nome, int cdp, float preco) {
    Hardware* novoHardware = (Hardware*)malloc(sizeof(Hardware));
    strcpy(novoHardware->nome, nome);
    novoHardware->cdp = cdp;
    novoHardware->preco = preco;
    novoHardware->proximo = NULL;
    
    if (fila->ultimo == NULL) {
        fila->primeiro = novoHardware;
        fila->ultimo = novoHardware;
    } else {
        fila->ultimo->proximo = novoHardware;
        fila->ultimo = novoHardware;
    }
}

/*A fun��o dequeue remove o primeiro elemento da fila e atualiza o apontador do primeiro. 
Se a fila ficar vazia ap�s a remo��o, o apontador do �ltimo tamb�m � atualizado para NULL.*/
Hardware* dequeue(Fila* fila) {
    if (fila->primeiro == NULL) {
        printf("A fila est� vazia. N�o � poss�vel remover elementos.\n");
        return NULL;
    }
    
    Hardware* hardwareRemovido = fila->primeiro;
    fila->primeiro = fila->primeiro->proximo;
    
    if (fila->primeiro == NULL) {
        fila->ultimo = NULL;
    }
    
    return hardwareRemovido;
}

/*A fun��o excluirFila remove todos os elementos da fila, liberando a mem�ria alocada para cada um deles. 
Por fim, libera a mem�ria alocada para a estrutura da fila.*/
void excluirFila(Fila* fila) {
    while (fila->primeiro != NULL) {
        Hardware* hardwareRemovido = dequeue(fila);
        free(hardwareRemovido);
    }
    
    free(fila);
}

/*A fun��o exibirFila percorre a fila usando um loop while e exibe os elementos na ordem em que foram inseridos.*/
void exibirFila(Fila* fila) {
    if (fila->primeiro == NULL) {
        printf("A fila est� vazia.\n");
        return;
    }
    
    printf("Elementos na fila:\n");
    Hardware* hardwareAtual = fila->primeiro;
    while (hardwareAtual != NULL) {
        printf("Nome: %s\n", hardwareAtual->nome);
        printf("CDP: %d\n", hardwareAtual->cdp);
        printf("Preco: %.2f\n", hardwareAtual->preco);
        printf("\n");
        hardwareAtual = hardwareAtual->proximo;
    }
}

/*Aqui � onde chama as fun��es e foi criado o menu para o usu�rio poder interagir com o codigo*/
int main() {
    Fila* fila = criarFila();
    
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
                char nome[50];
                int cdp;
                float preco;
                
                printf("Digite o nome do hardware: ");
                scanf("%s", nome);
                printf("Digite o CDP do hardware: ");
                scanf("%d", &cdp);
                printf("Digite o preco do hardware: ");
                scanf("%f", &preco);
                
                enqueue(fila, nome, cdp, preco);
                
                printf("Hardware adicionado � fila.\n\n");
                break;
            }
            case 2: {
                Hardware* hardwareRemovido = dequeue(fila);
                if (hardwareRemovido != NULL) {
                    printf("Elemento removido da fila:\n");
                    printf("Nome: %s\n", hardwareRemovido->nome);
                    printf("CDP: %d\n", hardwareRemovido->cdp);
                    printf("Preco: %.2f\n", hardwareRemovido->preco);
                    printf("\n");
                    free(hardwareRemovido);
                }
                break;
            }
            case 3: {
                exibirFila(fila);
                break;
            }
            case 4: {
                excluirFila(fila);
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
