/*Aluno: Lucas Davi da Silva Paixão
  Turma: ADS000302B 
  Turno: Noite


  Lista com Vetores
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 5

// Estruturas
typedef struct{
    char nome[50];
    int CDP;
    float preco;
} Hardware;
    
typedef struct{
    int ID;
    Hardware *elementos;
} Lista;

//CRIANDO AS FUNÇÕES

Lista* criarLista();
Lista* excluirLista(Lista*);
int atualizarElemento(Lista*,char*, char*, int, float);
int buscarElemento(Lista*, char*);
void imprimirElementos(Lista*);
int inserirElemento(Lista*, char*, int, float);
int inserirElementoID(Lista*, char*, int, float, int);
int inserirElementoInicio(Lista*, char*, int, float);
int removerElemento(Lista*, int);
int removerElementoNome(Lista*, char*);


//CRIANDO AS FUNÇÕES

// Função para criar uma nova lista vazia
Lista* criarLista(){

    // Aloca espaço para uma nova lista
    Lista *nova = (Lista*)malloc(sizeof(Lista));

    // Verifica se há espaço disponível
    if(nova == NULL){
        printf("Nao tem espaco\n");
        return NULL;
    }

    // Inicializa o ID da lista como zero
    nova->ID = 0;

    // Aloca espaço para o array de elementos da lista
    nova->elementos = (Hardware*)malloc(TAM*sizeof(Hardware));

    // Verifica se há espaço disponível
    if(nova->elementos == NULL){
        printf("Nao tem espaco\n");
        free(nova);
        return NULL;
    }

    // Retorna a lista criada
    return nova;
}


// Fun��o para retornar o tamanho da lista
int tamanhoLista(Lista *lista){

    // Verifica se a lista foi criada
    if(lista == NULL){
        printf("A lista n�o foi criada\n");
        return -1;
    }

    // Retorna o n�mero de elementos da lista
    return lista->ID;
}



int main(){
    int opcao = 0;
    Lista *lista = criarLista();
    char nome[50];
    int CDP;
    float preco;
    int id;

    while(1){
        printf("\n--------------------------------\n");
        printf("1 - Criar nova lista\n");
        printf("2 - Inserir elemento\n");
        printf("3 - Remover elemento por nome\n");
        printf("4 - Remover elemento por ID\n");
        printf("5 - Atualizar elemento\n");
        printf("6 - Buscar elemento\n");
        printf("7 - Imprimir elementos\n");
        printf("8 - Excluir lista\n");
        printf("9 - Verificar tamanho da lista\n");
        printf("10 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                lista = criarLista();
                printf("\nLista criada com sucesso!\n");
                break;
            case 2:
                printf("\nInsira o nome do hardware: ");
                scanf("%s", nome);
                printf("\nInsira o CDP: ");
                scanf("%d", &CDP);
                printf("\nInsira o preco: ");
                scanf("%f", &preco);
                inserirElemento(lista, nome, CDP, preco);
                break;
            case 3:
                printf("\nInsira o nome do hardware a ser removido: ");
                scanf("%s", nome);
                removerElementoNome(lista, nome);
                break;
            case 4:
                printf("\nInsira o ID do hardware a ser removido: ");
                scanf("%d", &id);
                removerElemento(lista, id);
                break;
            case 5:
                printf("\nInsira o nome do hardware a ser atualizado: ");
                scanf("%s", nome);
                printf("\nInsira o novo nome: ");
                scanf("%s", nome);
                printf("\nInsira o novo CDP: ");
                scanf("%d", &CDP);
                printf("\nInsira o novo preco: ");
                scanf("%f", &preco);
                atualizarElemento(lista, nome, nome, CDP, preco);
                break;
            case 6:
                printf("\nInsira o nome do hardware a ser buscado: ");
                scanf("%s", nome);
                buscarElemento(lista, nome);
                break;
            case 7:
                imprimirElementos(lista);
                break;
            case 8:
                excluirLista(lista);
                printf("\nLista exclu�da com sucesso!\n");
                break;
            case 9:
                printf("\nO tamanho da lista e: %d\n", tamanhoLista(lista));
                break;
            case 10:
                printf("\nSaindo do programa...\n");
                exit(0);
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
                break;
        }
    }

    return 0;
}



/*Funcao responsavel por atualizar a informacoes de uma pessoa da lista, caso a mesma esteja na lista indicada*/
int atualizarElemento(Lista *lista, char *busca, char *nome, int CDP, float preco){
    int i;

    // Verifica se a lista foi criada
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    // Percorre a lista procurando pelo elemento a ser atualizado
    for(i = 0; i < lista->ID; ++i){
        
        // Verifica se o nome do elemento atual é igual ao nome buscado
        if(strcmp(lista->elementos[i].nome, busca) == 0){
            
            // Atualiza as informações do elemento
            strcpy(lista->elementos[i].nome, nome);
            lista->elementos[i].CDP = CDP;
            lista->elementos[i].preco = preco;

            // Retorna 1 indicando que o elemento foi atualizado com sucesso
            return 1;
        }
    }

    // Retorna 0 indicando que o elemento não foi encontrado na lista
    return 0;
}


/*Funcao criada para buscar o nome de uma pessoa na lista*/
int buscarElemento(Lista *lista, char *nome){
    int i;

    // Verifica se a lista foi criada
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return -1;
    }

    // Percorre a lista procurando pelo elemento com o nome buscado
    for(i = 0; i < lista->ID; ++i){
       
        // Verifica se o nome do elemento atual é igual ao nome buscado
        if(strcmp(lista->elementos[i].nome, nome) == 0){
            // Retorna a posição do elemento encontrado
            return i;
        }
    }

    // Retorna -1 indicando que o elemento não foi encontrado na lista
    return -1;
}




/*Funcao responsavel pela exclusao da lista*/
Lista* excluirLista(Lista *lista){
    
    free(lista->elementos);
    
    free(lista);
    
    return NULL;
}

/*Funcao criada para apresentar todas pessoas presentes na lista*/
void imprimirElementos(Lista *lista){
    int i;

    // Verifica se a lista foi criada
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return ;
    }

    // Verifica se a lista está vazia
    if(lista->ID == 0){
        printf("Lista vazia\n");
        return ;
    }

    // Percorre a lista e imprime os dados de cada elemento
    for(i = 0; i < lista->ID; ++i){
        printf("Nome: %s \t", lista->elementos[i].nome);
        printf("CDP: %d \t", lista->elementos[i].CDP);
        printf("preco: %.2f \t", lista->elementos[i].preco);
    }

    // Imprime uma nova linha no final para separar a saída
    printf("\n");
}


/*Funcao criada para inserir uma pessoa no final da lista*/
int inserirElemento(Lista *lista, char *nome, int CDP, float preco){
    
    // Verifica se a lista foi criada
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    // Verifica se ainda há espaço na lista para adicionar um elemento
    if(lista->ID < TAM){
        
        // Adiciona um novo elemento ao final da lista
        strcpy(lista->elementos[lista->ID].nome, nome);
        lista->elementos[lista->ID].CDP = CDP;
        lista->elementos[lista->ID].preco =preco;
    
        // Incrementa o contador de elementos da lista
        ++(lista->ID);
    }else{
        printf("Espaco esgotado\n");
        return 0;
    }

    // Retorna 1 indicando que o elemento foi inserido com sucesso
    return 1;
}



/*Funcao criada para inserir uma pessoa na posicao indicada na lista
Retorno: 1 se a pessoa foi adicionada, 0 - caso contrario*/
int inserirElementoID(Lista *lista, char *nome, int CDP, float preco, int posicao){
    int i;

    // Verifica se a lista foi criada
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    // Verifica se ainda há espaço disponível na lista
    if(lista->ID < TAM){

        // Verifica se a posição informada está dentro do intervalo permitido
        if(posicao < lista->ID){
            
            // Desloca os elementos que estão à direita da posição a ser inserida para a direita
            for(i = lista->ID; i > posicao; --i){
                strcpy(lista->elementos[i].nome, lista->elementos[i-1].nome);
                lista->elementos[i].CDP = lista->elementos[i-1].CDP;
                lista->elementos[i].preco = lista->elementos[i-1].preco;
            }
            
            // Insere o novo elemento na posição indicada
            strcpy(lista->elementos[posicao].nome, nome);
            lista->elementos[posicao].CDP = CDP;
            lista->elementos[posicao].preco = preco;
            
            ++(lista->ID); // Incrementa o número de elementos da lista
        }else{
            printf("Posicao fora o intervalo permitido\n");
            return 0;
        }
    }else{
        printf("Espaco esgotado\n");
        return 0;
    }

    return 1;
}



/**
 * Insere um novo elemento no início da lista.
 * Retorna 1 se o elemento foi inserido com sucesso e 0 caso contrário.
 **/
int inserirElementoInicio(Lista *lista, char *nome, int CDP, float preco){
    int i;

    // Verifica se a lista foi criada
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    // Verifica se há espaço na lista
    if(lista->ID < TAM){

        // Desloca todos os elementos uma posição para o final da lista
        for(i = lista->ID; i > 0; --i){
            strcpy(lista->elementos[i].nome, lista->elementos[i-1].nome);
            lista->elementos[i].CDP = lista->elementos[i-1].CDP;
            lista->elementos[i].preco = lista->elementos[i-1].preco;
        }

        // Insere o novo elemento na primeira posição da lista
        strcpy(lista->elementos[0].nome, nome);
        lista->elementos[0].CDP = CDP;
        lista->elementos[0].preco = preco;

        ++(lista->ID); // Incrementa o contador de elementos na lista

    }else{
        printf("Espaco esgotado\n");
        return 0;
    }

    // Retorna 1 indicando sucesso
    return 1;
}





/**
 * Remove o elemento na posição especificada da lista.
 * Retorna 1 se o elemento foi removido com sucesso e 0 caso contrário.
 **/
int removerElemento(Lista *lista, int valor){
    int j;

    // Verifica se a lista existe
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    // Verifica se o índice está dentro dos limites da lista
    if (valor < lista->ID){
        
        // Move os elementos posteriores uma posição para a esquerda
        for(j = valor; j < lista->ID-1; ++j){
            strcpy(lista->elementos[j].nome, lista->elementos[j+1].nome);
            lista->elementos[j].CDP = lista->elementos[j+1].CDP;
            lista->elementos[j].preco = lista->elementos[j+1].preco;
        }

        // Decrementa o tamanho da lista e retorna 1 indicando sucesso
        --(lista->ID);
        return 1;
    }else{
        printf("Posicao invalida\n");
    }

    // Retorna 0 indicando falha
    return 0;
}





/**
 * Remove o elemento com o nome especificado da lista.
 * Retorna 1 se o elemento foi removido com sucesso e 0 caso contrário.
 **/
int removerElementoNome(Lista *lista, char *nome){
    int i, j;

    // Verifica se a lista existe
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    // Procura pelo elemento com o nome especificado
    for(i = 0; i < lista->ID; ++i){
        
        if(strcmp(lista->elementos[i].nome, nome) == 0){
            
            // Move os elementos posteriores uma posição para a esquerda
            for(j = i; j < lista->ID-1; ++j){
                strcpy(lista->elementos[j].nome, lista->elementos[j+1].nome);
                lista->elementos[j].CDP = lista->elementos[j+1].CDP;
                lista->elementos[j].preco = lista->elementos[j+1].preco;
            }
            
            // Decrementa o tamanho da lista e retorna 1 indicando sucesso
            --(lista->ID);
            return 1;
        }
    }

    // Se o elemento não foi encontrado, retorna 0 indicando falha
    return 0;
}

