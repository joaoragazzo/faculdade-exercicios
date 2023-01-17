#include <iostream>

using namespace std;


typedef struct no_{
    int chave;
    int valor;
    struct no_ *prox;
 } no;

no * ptLista;

 no *inicia_lista(){
    no* tmp = new no;
    tmp->prox = NULL;
    tmp->chave = 0;
    tmp->valor = 0;

    return tmp;
 }

void encerra_lista(no *ptlista){
    no * ant = ptLista->prox;
    no * pont = ant->prox;

    while(pont != NULL){
        delete(ant);
        ant = pont;
        pont = pont->prox;
    }
    delete(ant);
    
    delete(ptlista);
}

void busca_enc(int chave, no **ant, no **pont){
    *ant = ptLista;
    *pont = NULL;
    no * ptr = ptLista->prox;
    while(ptr != NULL){
        if (ptr->chave < chave){
            *ant = ptr;
            ptr = ptr->prox;
        }else {
            if (ptr->chave == chave) {
                *pont  = ptr;
            } ptr = NULL;
        }
    }
}

int insere_enc(int chave, int valor){
    int retorno = -1;
    no *ant;
    no *pont;
    busca_enc(chave, &ant, &pont);

    
    if(pont == NULL){
        no *temp = new no;
        temp->chave = chave;
        temp->valor = valor;
        temp->prox = ant->prox;
        ant->prox = temp;
        retorno = 0;
    }

    return retorno;
}

void imprime(){
    no *ptr = ptLista->prox;
    while(ptr != NULL ){
        cout << "Chave: " << ptr->chave << " | Valor: " << ptr->valor << endl;
        ptr = ptr->prox;
    }
}

int main(void){
    ptLista = inicia_lista();

    cout << insere_enc(1, 5) << endl;
    imprime();
    cout << "====================================" << endl;
    cout << insere_enc(2, 10) << endl;
    imprime();
    cout << "====================================" << endl;
    cout << insere_enc(3, 15) << endl;
    imprime();
    cout << "====================================" << endl;
    cout << insere_enc(2, 10) << endl;
    imprime();
    cout << "====================================" << endl;
    
    
    encerra_lista(ptLista);
    return (EXIT_SUCCESS);
}