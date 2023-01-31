#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "cliente.h"

using namespace std;

int main(int argc, char** argv) {
    Lista *clientes = new Lista();
    ifstream cadastro ("clientes_ord.txt");
    if (cadastro.is_open() && !cadastro.eof()){
        int i = 0;
        No *novo = new No();
        clientes->inicio = novo;
        clientes->fim = novo;
        clientes->qtde = 1;
        novo->dado = new Cliente();
        cadastro >> novo->dado->cpf;
        cout << "CPF " << i << " -> " << novo->dado->cpf;
        cadastro >> novo->dado->nome;
        cout << " Nome " << i << " -> " << novo->dado->nome;
        cadastro >> novo->dado->sobrenome;
        cout << " Sobrenome " << i << " -> " << novo->dado->sobrenome;
        cadastro >> novo->dado->celular;
        cout << " Celular " << i << " -> " << novo->dado->celular << endl;
        novo->prox = NULL;
       
        while ( !cadastro.eof() ){
            No *novo = new No();
            clientes->fim = novo;
            clientes->qtde++;
            novo->dado = new Cliente();
            cadastro >> novo->dado->cpf;
            cout << "CPF " << i << " -> " << novo->dado->cpf;
            cadastro >> novo->dado->nome;
            cout << " Nome " << i << " -> " << novo->dado->nome;
            cadastro >> novo->dado->sobrenome;
            cout << " Sobrenome " << i << " -> " << novo->dado->sobrenome;
            cadastro >> novo->dado->celular;
            cout << " Celular " << i << " -> " << novo->dado->celular << endl;
            novo->prox = NULL;
            i++;
        }
        cadastro.close();
    }
    else
        cout << "Arquivo não encontrado."; 

    delete clientes;
    return 0;
}
