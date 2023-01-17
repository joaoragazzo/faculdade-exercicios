#include <iostream>

using namespace std;

typedef struct valor_{
    int valor;
} valora;

typedef struct no_{
    valor_ * valor;
    struct no_ * prox;
} no;

typedef struct{
    int tamanho;
    struct no_ * lista;
} tLista;


tLista * inicia_lista(void){
    tLista * tmp = new tLista;
    tmp->lista = NULL;
    tmp->tamanho = 0;
    return tmp;
}

void alocar_valor(tLista * db, int valor){
    if(db->lista == NULL){
        db->lista = new no;
        db->lista->prox = NULL;
        db->lista->valor = new valor_;
        db->lista->valor->valor = valor;

        return;
    }
    
    no * atual = db->lista;
    
    while(atual->prox != NULL){
        atual = atual->prox;
    }

    atual->prox = new no;
    atual->prox->valor = new valor_;
    atual->prox->valor->valor = valor;
    atual->prox->prox = NULL;

}

void imprimir(tLista * db){
    for(no * atual = db->lista; atual != NULL; atual = atual->prox){
        cout << atual->valor->valor << endl;
    }

}

void ordenar_lista(tLista * db, tLista * ordenado){
    
    if (db->lista == NULL){
        cout << "Erro errado errôneo! (a lista db está vazia)" << endl;
        return;
    }

    no * cabeca = new no;
    cabeca->valor = db->lista->valor;

    for(no * atual = db->lista->prox; atual != NULL; atual = atual->prox){

        no * anterior = NULL;
        no * aux = cabeca;      
        no * tmp = new no;

        while(aux){

            if(aux->valor->valor > atual->valor->valor) 
                break;
            

            anterior = aux;
            aux = aux->prox;
        }

        //for(aux = cabeca; aux != NULL && aux->valor->valor < atual->valor->valor; anterior = aux, aux = aux->prox)

        tmp->valor = atual->valor;
        tmp->prox = aux;    

        if(anterior != NULL){
            anterior->prox = tmp;
        } else {
            cabeca = tmp; 
        }        

        if(aux == NULL){
            anterior->prox = tmp;
        }
        
    }

    ordenado->lista = cabeca;
}

int main(void){

    tLista * db = inicia_lista();
    tLista * ordenado = inicia_lista();

    alocar_valor(db, 3);
    alocar_valor(db, 7);
    alocar_valor(db, 5);
    alocar_valor(db, 42);
    alocar_valor(db, 2);
    alocar_valor(db, 100);
    alocar_valor(db, 242);
    alocar_valor(db, 0);
    alocar_valor(db, 1);
    alocar_valor(db, -1);
    alocar_valor(db, -10);

    ordenar_lista(db, ordenado);

    imprimir(ordenado);
    
    
    
    return 0;
};