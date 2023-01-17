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
    no * atual = db->lista;

    for(; atual != NULL; atual = atual->prox){
        cout << atual->valor->valor << endl;
    }

}

void ordenar_lista(tLista * db, tLista * ordenado){
    if (db->lista == NULL){
        cout << "Erro errado errôneo! (a lista db está vazia)" << endl;
        return;
    }

    no * ordenada = new no;
    ordenada->valor = db->lista->valor;
    ordenada->prox = NULL;

    for(no * atual = db->lista->prox; atual != NULL; atual = atual->prox){

        no * anterior = NULL;
        no * aux;
        bool Alocado = false;      

        for(aux = ordenada; aux != NULL; aux = aux->prox){

            if(aux->valor->valor > atual->valor->valor){  

                no * tmp = new no;
                tmp->valor = atual->valor;
                tmp->prox = aux;     

                if(anterior != NULL){
                    anterior->prox = tmp;
                } else {
                    ordenada = tmp; 
                }        

                Alocado = true;
                break;
            }

            anterior = aux;
        }
        
        if(!Alocado){
            anterior->prox = new no;
            anterior->prox->valor = atual->valor;
            anterior->prox->prox = NULL;
        }

    }
    ordenado->lista = ordenada;
}

int main(void){

    tLista * db = inicia_lista();
    tLista * ordenado = inicia_lista();

    alocar_valor(db, 50);
    alocar_valor(db, 40);
    alocar_valor(db, 30);
    alocar_valor(db, 20);
    alocar_valor(db, 10);
    alocar_valor(db, 100);
    alocar_valor(db, 14);
    alocar_valor(db, 15);
    alocar_valor(db, 16);
    alocar_valor(db, 17);
    alocar_valor(db, 18);
    alocar_valor(db, 19);
    alocar_valor(db, 11);
    alocar_valor(db, 12);
    alocar_valor(db, 13);
    alocar_valor(db, 144);
    alocar_valor(db, 145);
    alocar_valor(db, 146);

    ordenar_lista(db, ordenado);

    imprimir(ordenado);
    
    
    
    return 0;
};