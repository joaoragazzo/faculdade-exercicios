#include <stdio.h>
#include <stdlib.h>

void push(int *pilha, int **pilhaPtr, int valor){
    *pilha = valor;
    *pilhaPtr = *pilhaPtr + 1;
}

int pop(int *pilha, int **pilhaPtr){
    int retorno = *(pilha -1);
    *pilhaPtr = *pilhaPtr - 1;
    return retorno;
}

int main(void){
    int *pilha = malloc(100*sizeof(int));

    push(pilha, &pilha, 10); //coloca na posição 1 o valor 10
    push(pilha, &pilha, 20); //coloca na posição 2 o valor 20

    printf("%d\n", pop(pilha, &pilha)); //tira da posição 2 o valor 20
    printf("%d\n", pop(pilha, &pilha)); //tira da posição 1 o valor 10

    push(pilha, &pilha, 40); //coloca na posição 1 o valor 40
 
    printf("%d\n", pop(pilha, &pilha)); //tira da posição 1 o valor 40

    free(pilha);
}