/**
 * João Paulo Martyr Ragazzo - 22 de Janeiro de 2023
 * Universidade Federal de Alfenas (UNIFAL)
*/
#include <iostream>

using namespace std;

/**
 * Professor vai cobrar a remoção em 1-Esquerda/Todos-direita
*/

typedef struct no {
    int valor;
    no * direita; //maior
    no * esquerda; //menor
} no;

/**
 * Inicia a árvore com um valor em específico
 *  @param valor o primeiro valor da arvore binária
 *  @return O primeiro nó da árvore
*/
no * inicia_arvore (int valor) {
    no * tmp = new no;
    tmp->direita = NULL;
    tmp->esquerda = NULL;
    tmp->valor = valor;
    return tmp;
}

/**
 * Insere um valor na árvore binária
 * @param cabeca o primeiro nó da árvore
 * @param valor o valor a ser inserido
 * @return 1 caso foi possível realizar a inserção e 0 caso não tenha sido possível realizar a inserção
*/
int insere_valor (no * cabeca, int valor) {
    if (cabeca->valor == valor){
        return 0;
    }

    if (cabeca->valor > valor) { /* tem que ir para a esquerda */
        if (cabeca->esquerda == NULL) {
            no * tmp = new no;
            cabeca->esquerda = tmp;
            tmp->esquerda = NULL;
            tmp->direita = NULL;
            tmp->valor = valor;
            return 1;
        }
        
        return insere_valor(cabeca->esquerda, valor);
    }

    if (cabeca->valor < valor) {
        if (cabeca->direita == NULL) {
            no * tmp = new no;
            cabeca->direita = tmp;
            tmp->esquerda = NULL;
            tmp->direita = NULL;
            tmp->valor = valor;
            return 1;
        }

        return insere_valor(cabeca->direita, valor);
    }
};

no ** encontrar_no(no * no_, int valor) {
    while(no_->valor != valor && no_->valor != NULL) {

    }
}

void remover_valor (no ** cabeca, int valor) {
    no ** excluir = encontrar_no(*&*cabeca, valor);
    no * tmp = NULL;

    if (excluir == NULL) { /*Se excluir == NULL, entao quer dizer que não existe o valor específico na árvore*/ 
        return;
    }

    if (excluir->esquerda == NULL ) {
        
    }

}


int main(void) {

    no * cabeca = inicia_arvore(10);
    insere_valor(cabeca, 20);
    insere_valor(cabeca, 3);
    insere_valor(cabeca, 7);
    insere_valor(cabeca, 8);
    insere_valor(cabeca, 6);
    insere_valor(cabeca, 5);

    remover_valor(&cabeca, 5);


    return EXIT_SUCCESS;
}