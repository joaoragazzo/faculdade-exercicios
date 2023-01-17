#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int chave;
    int valor;
} Lista;

void inserir(int chave, int valor, Lista *lista, int *tamanho){
    
    if (lista->chave == chave){
        lista->valor = valor;
        *tamanho = *tamanho + 1;
        return;
    }
    
    for(int i = 0; i < *tamanho; i++){
        if((lista + i)->chave + 1 == chave){
            (lista + i + 1)->chave = chave;
            (lista + i + 1)->valor = valor;
            *tamanho = *tamanho + 1;
            return;
        }
    }

    printf("Chave não existente na lista. Alocando o valor %d na posição máxima %d", valor, *tamanho);

    (lista + *tamanho)->chave = *tamanho;
    (lista + *tamanho)->valor = valor;

    *tamanho = *tamanho + 1;
    return;
}

void consulta(int chave, Lista *lista, int tamanho){
    if(chave >= tamanho){
        printf("Valor de chave impróprio. Escolha uma chave com de acordo com o tamanho máximo de %d", tamanho - 1);
        return;
    }
    
    for(int i = 0; i < tamanho; i++){
        if((lista+i)->chave == chave){
            printf("O valor da chave %d é %d.", chave, (lista+i)->valor);
            return;
        }
    }

    printf("Aconteceu algum erro...");
    return;
}

void remocao(int chave, Lista *lista, int *tamanho){
    if(chave >= *tamanho){
        printf("Valor de chave impróprio. Escolha uma chave com de acordo com o tamanho máximo de %d", tamanho - 1);
        return;
    }

    for(int i = chave; chave < *tamanho; chave++){
        (lista + i)->valor = (lista + i + 1)->valor;
    }

    (lista + *tamanho - 1)->chave = (lista + *tamanho)->chave;
    *tamanho = *tamanho - 1;

    printf("A chave %d foi removido com sucesso.", chave);
}

int main(void){
    Lista * lista = malloc(100*sizeof(Lista));
    int tamanho = 1;

    lista->chave = 0;
    lista->valor = 0;

    inserir(1, 10, lista, &tamanho);
    inserir(2, 12, lista, &tamanho);
    consulta(2, lista, tamanho);



}