#include <stdio.h>
#include <stdlib.h>

void endInsertion(int value, int *final, int **finalPtr){
    *final = value;
    *finalPtr = *finalPtr + 1;
}

void startInsertion(int value, int *lista, int *final, int **finalPtr){
    for(int i = (final - lista); i >= 0; i--){
        *(lista + i + 1) = *(lista + i);
    }
    *lista = value;
    *finalPtr = *finalPtr + 1;
}

int endRemoval(int *final, int **finalPtr){
    int retorno = *(final - 1);
    *finalPtr = *finalPtr - 1;
    return retorno;
}

int startRemoval(int *lista, int *final, int **finalPtr){
    int retorno = *lista;    
    for(int i = 0; (lista + i) <= final; i++){
        *(lista + i) = *(lista + i + 1);
    }
    
    *finalPtr = *finalPtr - 1;
    return retorno;
}

int main(void){
    int *lista = malloc(100*sizeof(int));
    int *final = lista;

    startInsertion(1, lista, final, &final);
    endInsertion(2, final, &final);
    endInsertion(3, final, &final);
    startInsertion(4, lista, final, &final);
    startInsertion(5, lista, final, &final);
    startInsertion(6, lista, final, &final);
    endRemoval(final, &final);
    startRemoval(lista, final, &final);
    startRemoval(lista, final, &final);
    startRemoval(lista, final, &final);
    startInsertion(7, lista, final, &final);
    endRemoval(final, &final);
    printf("%d\n", startRemoval(lista, final, &final));
    printf("%d\n", startRemoval(lista, final, &final));


    free(lista);
    return(EXIT_SUCCESS);
}