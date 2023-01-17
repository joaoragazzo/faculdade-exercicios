#include <cstdlib>
#include <iostream>

using namespace std;

typedef struct no_ {
	int valor;  //'carga útil' do nó
                    //num cenario real, poderia ser: nome, endereco...
	struct no_ * prox;  // ponteiro para o próximo nó da lista encadeada
} no;

typedef struct {
	int tam;            //critério de busca da ordenação
	struct no_ * lista; // ponteiro para o próximo nó da lista encadeada
} tLista;

/**
 * Realiza a alocacao do espaco para que a lista possa comecar
 * a receber nos.
 * @return a lista vazia.
 */
tLista* inicia_lista() {
	tLista* tmp = new (tLista);
	tmp->tam = 0;
	tmp->lista = NULL;
	cout << "-A lista foi iniciada."<<endl;
	return tmp;
}

/**
 * Desaloca o espaco previamente alocado para a lista encadeada.
 * @param ptlista ponteiro para a lista.
 * @return NULL para atualizar o ponteiro da lista.
 */
tLista * encerra_lista(tLista * ptlista) {
	no * ant = ptlista->lista;
	no * pont = ptlista->lista;
	
	while(ant != NULL){
		pont = ant->prox;
		delete(ant);
		ant = pont;
	}
	delete(ptlista);
        cout << "-A lista foi removida."<<endl;
	
        return NULL;
}

/**
 * Busca pelo valor de chave passado dentro da lista encadeada.
 * @param chave a ser buscada.
 * @param ant ponteiro anterior a posicao encontrada.
 * @return verdareiro se o elemento foi encontrado.
 */
no * busca(tLista * ptlista, int valor) {
	no * atual = ptlista->lista;

	while(atual != NULL){
		if (atual->valor == valor){
			return atual;
		}

		atual = atual->prox;
	}

	return NULL;
}

/**
 * Realiza a insercao do elemento no início da lista ligada.
 * @param valor a ser inserido.
 */
void insere_inicio(tLista * ptlista, int valor){

	no * primeiro = ptlista->lista;
	ptlista->tam = ptlista->tam + 1;

	no * novo = new no;

	ptlista->lista = novo;
	novo->prox = primeiro;
	novo->valor = valor;

}

/**
 * Realiza a insercao do elemento no fim da lista ligada.
 * @param valor a ser inserido.
 */
void insere_fim(tLista * ptlista, int valor){
	no * atual = ptlista->lista;

	while(atual->prox != NULL){
		atual = atual->prox;
	}

	no * novo = new no;

	atual->prox = novo;
	novo->prox = NULL;
	novo->valor = valor;

	ptlista->tam = ptlista->tam + 1;

}

/**
 * Realiza a remocao do primeiro elemento da lista encadeada, se houver.
 * @return nulo em caso de lista vazia, senão retorna o nó removido.
 */
no * remove_inicio(tLista * ptlista){
	if(ptlista->lista == NULL) return NULL;
	
	no * atual = ptlista->lista;

	no * remover = atual;
	atual = atual->prox;

	ptlista->lista = atual;
	ptlista->tam = ptlista->tam - 1;

	return remover;
}

/**
 * Realiza a remocao do último elemento da lista encadeada, se houver.
 * @return nulo em caso de lista vazia, senão retorna o nó removido.
 */
no * remove_fim(tLista * ptlista){
	if(ptlista->lista == NULL) return NULL;
	
	no * atual = ptlista->lista;
	no * anterior;
	while(atual->prox != NULL) {
		anterior = atual;
		atual = atual->prox;
	}

	anterior->prox = NULL;
	ptlista->tam = ptlista->tam - 1;
	return atual;

}

/**
 * Imprime a lista encadeada.
 */
void imprime(tLista * ptlista){
	no * atual = ptlista->lista;

	cout << "[ ";

	while(atual != NULL){
		cout << atual->valor;

		if(atual->prox != NULL) {
			cout << " -> ";
		}

		atual = atual->prox;
	}
	cout << " ]" << endl;;
}

tLista * lista1;

int main(void){
	no * p;
    lista1 = inicia_lista();


    insere_inicio(lista1, 5);
	insere_inicio(lista1, 6);
	insere_inicio(lista1, 7);

	insere_fim(lista1, 1);
    imprime(lista1);

	p = remove_fim(lista1);
	delete(p);
	imprime(lista1);



}