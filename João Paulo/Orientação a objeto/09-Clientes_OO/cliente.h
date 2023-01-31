
#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>

using namespace std;

/** Struct com os dados do cliente.
 *  O campo 'cpf' possui o valor inteiro do CPF (5 dígitos).
 *  O campo 'nome' possui o conjunto de caracteres do nome do cliente.
 *  O campo 'sobrenome' possui o conjunto de caracteres do sobrenome do cliente.
 *  O campo 'celular' possui o valor inteiro do número do celular (5 dígitos).
 */
class Cliente{
public:
    Cliente();
    Cliente(int cp, string n, string s, int ce);  // Construtor
    ~Cliente(); // Destrutor
//private:
    int cpf;  //chave
    string nome, sobrenome;
    int celular;
};

/** Struct do nó da lista.
 *  O campo 'dado' aponta para o struct com os dados do cliente.
 *  O campo 'prox' aponta para o próximo nó ou NULL quando for o último nó.
 */
class No{
public:
    No();  // Construtor
    No(Cliente *d, No *p);  // Construtor
    ~No(); // Destrutor
    Cliente *dado;
    No *prox;
};

/** Struct do cabeçalho da lista. 
 * O campo 'inicio' aponta para o primeiro nó da lista.
 * O campo 'final' aponta para o último nó da lista.
 * o campo 'qtde' armazena o valor inteiro da quantidade de elementos.
 */
class Lista {
public:
    Lista();
    ~Lista();
    Cliente * busca(int valor);
    Cliente * buscaord(int valor);
    void insereord(int cp, string n, string s, int ce);
    Cliente * removeord(int cpf);
    void insereinicio(int cp, string n, string s, int ce);
    void inserefim(int cp, string n, string s, int c);
    Cliente * removeinicio();
    Cliente * removefim();
    No *inicio, *fim;
    int qtde;
};

/**
 * Devolve a quantidade de elementos da lista.
 * @param l Ponteiro para o cabeçalho da lista.
 * @return 
 */
//int quantidade(tLista *l);

#endif /* CLIENTE_H */

