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


// CRIANDO A LISTA

Lista* criarLista(){
    
    Lista *nova = (Lista*)malloc(sizeof(Lista));

    if(nova == NULL){
        printf("Nao tem espaco\n");
        return NULL;
    }

    nova->ID = 0; 
    nova->elementos = (Hardware*)malloc(TAM*sizeof(Hardware));
    
   if(nova->elementos == NULL){
        printf("Nao tem espaco\n");
        free(nova);
        return NULL;
    }

    return nova;
}



int main(){
    Lista *lista = NULL;
    imprimirElementos(lista);
    
    lista = criarLista();
    imprimirElementos(lista);

    printf("\nInserindo Processador\n");
    inserirElemento(lista, "Processador", 1, 949.9);
    imprimirElementos(lista);

    printf("\nInserindo Placa de Video\n");
    inserirElemento(lista, "Placa de Video", 10, 2259.00);
    imprimirElementos(lista);
    
    printf("\nInserindo Mouse\n");
    inserirElemento(lista, "Mouse", 11, 2599.00);
    imprimirElementos(lista);

    printf("\nInserindo Placa mae\n");
    inserirElemento(lista, "Placa mae", 20, 899.99);
    imprimirElementos(lista);

    printf("\nInserindo SSD\n");
    inserirElemento(lista, "SSD", 30, 124.99);
    imprimirElementos(lista);

    printf("\nRetirando Mouse\n");
    removerElementoNome(lista, "Mouse");
    imprimirElementos(lista);
    
    int busca = buscarElemento(lista, "Cooler");


    if(busca != -1){
        printf("Encontrou o elemento: %d\n", busca);
        printf("Nome: %s \n", lista->elementos[busca].nome);
        printf("CDP: %d \n", lista->elementos[busca].CDP);
        printf("preco: %.2f \n", lista->elementos[busca].preco);
    }else{
        printf("Produto nao encontrado\n");
    }
    
    atualizarElemento(lista, "Processador", "Watercooler", 2, 1.290);
    imprimirElementos(lista);

    removerElemento(lista, 5);
    imprimirElementos(lista);

    inserirElementoInicio(lista, "Fonte Asus", 060, 2.849);
    imprimirElementos(lista);

    inserirElementoID(lista, "Memória XPG", 070, 700.00, 07);
    imprimirElementos(lista);
    
    lista = excluirLista(lista);
    imprimirElementos(lista);
    return 0;
}


int atualizarElemento(Lista *lista, char *busca, char *nome, int CDP, float preco){
    int i;

    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    for(i = 0; i < lista->ID; ++i){
        
        if(strcmp(lista->elementos[i].nome, busca) == 0){
            
            strcpy(lista->elementos[i].nome, nome);
            lista->elementos[i].CDP = CDP;
            lista->elementos[i].preco = preco;
            return 1;
        }
    }
    return 0;
}


int buscarElemento(Lista *lista, char *nome){
    int i;

    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return -1;
    }

   for(i = 0; i < lista->ID; ++i){
       
        if(strcmp(lista->elementos[i].nome, nome) == 0){
            return i;
        }
    }

    return -1;
}




Lista* excluirLista(Lista *lista){
    
    free(lista->elementos);
    
    free(lista);
    
    return NULL;
}


void imprimirElementos(Lista *lista){
    int i;

    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return ;
    }

    if(lista->ID == 0){
        printf("Lista vazia\n");
        return ;
    }

    for(i = 0; i < lista->ID; ++i){
        printf("Nome: %s \t", lista->elementos[i].nome);
        printf("CDP: %d \t", lista->elementos[i].CDP);
        printf("preco: %.2f \t", lista->elementos[i].preco);
    }
    printf("\n");
}


int inserirElemento(Lista *lista, char *nome, int CDP, float preco){
    
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    if(lista->ID < TAM){
        
        strcpy(lista->elementos[lista->ID].nome, nome);
        lista->elementos[lista->ID].CDP = CDP;
        lista->elementos[lista->ID].preco =preco;
    
        ++(lista->ID);
    }else{
        printf("Espaco esgotado\n");
        return 0;
    }

    return 1;
}



int inserirElementoID(Lista *lista, char *nome, int CDP, float preco, int posicao){
    int i;

    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    if(lista->ID < TAM){

        if(posicao < lista->ID){
        
            for(i = lista->ID; i > posicao; --i){
                strcpy(lista->elementos[i].nome, lista->elementos[i-1].nome);
                lista->elementos[i].CDP = lista->elementos[i-1].CDP;
                lista->elementos[i].preco = lista->elementos[i-1].preco;
            }
           
            strcpy(lista->elementos[posicao].nome, nome);
            lista->elementos[posicao].CDP = CDP;
            lista->elementos[posicao].preco = preco;
            
            ++(lista->ID);
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


int inserirElementoInicio(Lista *lista, char *nome, int CDP, float preco){
    int i;

    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    /*Verificando se existe espaco para inserir mais uma pessoa na lista*/
    if(lista->ID < TAM){
        /*Deslocando todas as pessoas para o final da lista*/
        for(i = lista->ID; i > 0; --i){
            strcpy(lista->elementos[i].nome, lista->elementos[i-1].nome);
            lista->elementos[i].CDP = lista->elementos[i-1].CDP;
            lista->elementos[i].preco = lista->elementos[i-1].preco;
        }

        strcpy(lista->elementos[0].nome, nome);
        lista->elementos[0].CDP = CDP;
        lista->elementos[0].preco =preco;
       
        ++(lista->ID);
    }else{
        printf("Espaco esgotado\n");
        return 0;
    }
    return 1;
}



int removerElemento(Lista *lista, int valor){
    int j;

    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    
    if (valor < lista->ID){
        
        for(j = valor; j < lista->ID-1; ++j){
            strcpy(lista->elementos[j].nome, lista->elementos[j+1].nome);
            lista->elementos[j].CDP = lista->elementos[j+1].CDP;
            lista->elementos[j].preco = lista->elementos[j+1].preco;
        }
        --(lista->ID);
        return 1;
    }else{
        printf("Posicao invalida\n");
    }

    return 0;
}




int removerElementoNome(Lista *lista, char *nome){
    int i, j;

    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    for(i = 0; i < lista->ID; ++i){
        
        if(strcmp(lista->elementos[i].nome, nome) == 0){
            
            for(j = i; j < lista->ID-1; ++j){
                strcpy(lista->elementos[j].nome, lista->elementos[j+1].nome);
                lista->elementos[j].CDP = lista->elementos[j+1].CDP;
                lista->elementos[j].preco = lista->elementos[j+1].preco;
            }
            
            --(lista->ID);
            return 1;
        }
    }

    return 0;
}
