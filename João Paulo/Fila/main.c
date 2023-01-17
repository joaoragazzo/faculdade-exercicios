#include <stdio.h>
#include <stdlib.h>

void enqueue(int valor, int *fim, int **fimPtr){
    *fim = valor;
    *fimPtr = *fimPtr + 1;
}

int dequeue(int *comeco, int *fim, int **fimPtr){
    int retorno = *comeco;
    for(int i = 0; comeco + i <= fim; i++){
        *(comeco + i) = *(comeco + i + 1);
    }
    *fimPtr = *fimPtr -1;
    return retorno;

}

int main(void){
    int *comeco = malloc(100*sizeof(int));
    int *fim = comeco;

    enqueue(10, fim, &fim);
    enqueue(20, fim, &fim);
    enqueue(30, fim, &fim);
    printf("%d\n", dequeue(comeco, fim, &fim));
    printf("%d\n", dequeue(comeco, fim, &fim));
    printf("%d\n", dequeue(comeco, fim, &fim));

    return (EXIT_SUCCESS);
}