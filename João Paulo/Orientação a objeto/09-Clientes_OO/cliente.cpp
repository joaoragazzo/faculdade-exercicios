
#include <cstdlib>
#include "cliente.h"

using namespace std;

Cliente::Cliente(){
  cpf = 0;
  nome = "";
  sobrenome = "";
  celular = 0;
}

Cliente::Cliente(int cp, string n, string s, int ce){
  cpf = cp;
  nome = n;
  sobrenome = s;
  celular = ce;
}

Cliente::~Cliente(){
  cpf = 0;
  nome = "";
  sobrenome = "";
  celular = 0;
}

No::No(){
    dado = NULL;
    prox = NULL;
}

No::No(Cliente* d, No* p){
    dado = d;
    prox = p;    
}

No::~No(){
}

/**
 * Inicializa os campos do cabeçalho da lista
 * @return valor do endereço da struct do cabeçalho
 */
Lista::Lista(){
    inicio = NULL;
    fim = NULL;
    qtde = 0;
}

/**
 * Desaloca todos os nós e registros de clientes da lista
 * O cabeçalho não é desalocado.
 * @param l ponteiro para o cabeçalho da lista
 */
Lista::~Lista(){
    No *p = inicio, *r;
    while (p != NULL){
        r = p;
        p = p->prox;
        free(r->dado);
        free(r);
    }
    qtde = 0;
    inicio = NULL;
    fim = NULL;
}

//int quantidade(tLista *l){
//    return l->qtde;
//}

Cliente * Lista::busca(int valor){
    if (qtde > 0){
        No *p = inicio;
        while(p != NULL){            
            if (p->dado->cpf == valor)
                return p->dado;
            p = p->prox;
        }
    }
    return NULL;
}

Cliente * Lista::buscaord(int valor){
    return NULL;
}

void Lista::insereord(int cp, string n, string s, int ce){
}
