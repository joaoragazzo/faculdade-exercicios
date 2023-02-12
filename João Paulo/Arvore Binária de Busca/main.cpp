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
int insere_valor(no * cabeca, int valor) {
    if (cabeca->valor == valor){
        return 0;
    }

    if (cabeca->valor > valor) { /* tem que ir para a esquerda */
        if (!cabeca->esquerda) {
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
        if (!cabeca->direita) {
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

/**
 * @brief Função utilizada para encontrar o ponteiro que aponta para o nó com o específico valor
 * 
 * @param no_ o primeiro nó de onde vai começar a busca
 * @param valor o valor a ser buscado
 * @return um ponteiro que aponta para o ponteiro que aponta para o nó em questão com o valor
 * FUNCIONANDO!
 */
no ** encontrar_no(no ** no_, int valor) {
    
    no * noAtual = *no_;
    no ** ponteiro = no_;

    while(noAtual->valor != valor) {
        if(noAtual->valor < valor) {
            ponteiro = &noAtual->direita;
            noAtual = noAtual->direita;
        }

        else if(noAtual->valor > valor) {
            ponteiro = &noAtual->esquerda;
            noAtual = noAtual->esquerda;
        }

        if(!noAtual)
            return NULL;
    }

    return ponteiro;

}

/**
 * Remove um valor da árvore binária
 * @param cabeca o primeiro nó da árvore
 * @param valor o primeiro valor da árvore
*/
void remover_valor(no ** cabeca, int valor) {
    no ** pontExcluir = encontrar_no(cabeca, valor);

    if (!pontExcluir) { /*Se excluir == NULL, entao quer dizer que não existe o valor específico na árvore*/ 
        return;
    }

    no * noExcluir = *&*pontExcluir;
    
    if (!noExcluir->esquerda && !noExcluir->direita) {
        *pontExcluir = NULL;
    }

    if (noExcluir->esquerda == NULL && noExcluir->direita) {
        *pontExcluir = noExcluir->direita;
        return;
    } 

    no * tmp = noExcluir->esquerda;
    no * tmp_pai = noExcluir;
    for(; tmp->direita ; tmp_pai = tmp, tmp = tmp->direita);
    
    if (noExcluir->direita != tmp) 
        tmp->direita = noExcluir->direita;

    if (noExcluir->esquerda != tmp)
        tmp->esquerda = noExcluir->esquerda;
    
    *pontExcluir = tmp;
    tmp_pai->direita = NULL;
    

}

/**
 * Imprime a árvore em pré-ordem
 * @param cabeca o primeiro nó da árvore
*/
void pre_ordem(no * cabeca) {
    if (!cabeca) {
        cout << "A árvore está vazia." << endl;
        return;
    }

    cout << cabeca->valor << endl;

    if (cabeca->esquerda) 
        pre_ordem(cabeca->esquerda);

    if (cabeca->direita) 
        pre_ordem(cabeca->direita);

    return;
}

/**
 * Imprime a árvore em-ordem
 * @param cabeca o primeiro nó da árvore
*/
void em_ordem(no * cabeca) {
    if (!cabeca) {
        cout << "A árvore está vazia." << endl;
        return;
    }

    if(cabeca->esquerda)
        em_ordem(cabeca->esquerda);

    cout << cabeca->valor << endl;

    if(cabeca->direita)
        em_ordem(cabeca->direita);

    return;
}

/**
 * Imprime a árvore em pós-ordem
 * @param cabeca o primeiro nó da árvore
*/
void pos_ordem(no * cabeca) {
    if (!cabeca) {
        cout << "A árvore está vazia" << endl;
        return;
    }

    if (cabeca->esquerda) 
        pos_ordem(cabeca->esquerda);
    
    if (cabeca->direita)
        pos_ordem(cabeca->direita);
    
    cout << cabeca->valor << endl;

    return;
}

int main(void) {

    no * cabeca = inicia_arvore(13);
    insere_valor(cabeca, 22);
    insere_valor(cabeca, 6);
    insere_valor(cabeca, 5);
    insere_valor(cabeca, 7);
    insere_valor(cabeca, 21);
    insere_valor(cabeca, 24);

    remover_valor(&cabeca, 13);
    remover_valor(&cabeca, 13);

    em_ordem(cabeca);

}