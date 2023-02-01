/******************************************************************************/
/*              Este programa gerencia arvores AVL                            */
/*  Arvores AVL sao arvores balanceadas na altura.                            */
/*  O nome AVL vem de seus criadores Adelson Velsky e Landis, cuja primeira   */
/*    referência encontra-se no documento "Algoritmos para organização da     */
/*    informação" de 1962.                                                    */
/* http://www.each.usp.br/digiampietri/ACH2023/javaec/ArvoreAVL/arvoreAVL.c   */
/******************************************************************************/

#include <stdio.h>
#include <malloc.h>
#include <cstdlib>
#include <iostream>
#include "headers.h"

using namespace std;

#define true 1
#define false 0

//typedef int bool;
typedef int TIPOCHAVE;

typedef struct aux {
    TIPOCHAVE chave;
    struct aux *esquerda;
    struct aux *direita;
    int bal; // fator de balanceamento (0, -1 ou +1) => alt. direita - alt. esquerda
} NO, *PONT, NoArvAVL;

/* Cria um novo (aloca memoria e preenche valores) no com chave=ch e retorna 
   seu endereco. */
PONT criarNovoNo(TIPOCHAVE ch){
    PONT novoNo = (PONT)malloc(sizeof(NO));
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    novoNo->chave = ch;
    novoNo->bal = 0;
    return novoNo;
}

/* Retorna o maior valor entre dois inteiros. */
int max(int a, int b){
    if (a>b)
        return a;
    return b;
}

/* Retorna a altura de uma (sub-)arvore. */
int altura(PONT p){
    if (!p)
        return -1;
    else return 1 + max(altura(p->esquerda),altura(p->direita));
}

/* Exibe arvore Em Ordem.         */
void exibirArvoreEmOrdem(PONT raiz){
    if (raiz == NULL)
        return;
    exibirArvoreEmOrdem(raiz->esquerda);
    printf("%i ",raiz->chave);
    exibirArvoreEmOrdem(raiz->direita);
}

/* Exibe arvore Pre Ordem.         */
void exibirArvorePreOrdem(PONT raiz){
    if (raiz == NULL)
        return;
    printf("%i ",raiz->chave);
    exibirArvorePreOrdem(raiz->esquerda);
    exibirArvorePreOrdem(raiz->direita);
}

/* Exibe arvore Pos Ordem         */
void exibirArvorePosOrdem(PONT raiz){
    if (raiz == NULL)
        return;
    exibirArvorePreOrdem(raiz->esquerda);
    exibirArvorePreOrdem(raiz->direita);
    printf("%i ",raiz->chave);
}

/* Exibe arvore Em Ordem (com parenteses para os filhos)    */
void exibirArvore(PONT raiz){
    if (raiz == NULL)
        return;
    printf("%i[%i]",raiz->chave,raiz->bal);
    printf("(");     
    exibirArvore(raiz->esquerda);
    exibirArvore(raiz->direita);
    printf(")");     
}

/* Exibe arvore Pre-Ordem indicando pai de cada no    */
void exibirArvore2(PONT raiz, TIPOCHAVE chavePai){
    if (raiz == NULL)
        return;
    printf("(%i,%i) ",chavePai,raiz->chave);
    exibirArvore2(raiz->esquerda,raiz->chave);
    exibirArvore2(raiz->direita,raiz->chave);
}

// Verifica se árvore é AVL
bool ehAVL(PONT p){
    int e,d;
    bool ok = true;
    if(p){
	ok = ehAVL(p->esquerda);
	if(ok)
            ok = ehAVL(p->direita);
	if(ok){
            e = altura(p->esquerda);
            d = altura(p->direita);
            if(e-d > 1 || e-d < -1)
                ok = false;  
            else ok = true;
	}
    }
    return(ok);
}

/* Verifica se árvore é AVL. */
bool ehAVL2(PONT p, int* alt){
    if (!p){
       *alt=-1;
       return true;
    }
    bool res;
    int d, e;
    res = ehAVL2(p->direita,&d);
    if (!res)
        return false;
    res = ehAVL2(p->esquerda,&e);
    if (!res)
        return false;
    if (d-e != p->bal)
        printf("### O campo 'bal' do no '%i' esta com valor incorreto de balanceamento. ###\n",p->chave);
    if ((d-e<-1) || (d-e>1))
        return false;
    *alt = max(d,e)+1; 
    return true;	
}

int atualizarBalanceamentoTotal(PONT raiz){
    if (!raiz)
        return 0;
    int d = atualizarBalanceamentoTotal(raiz->direita);
    int e = atualizarBalanceamentoTotal(raiz->esquerda);
    raiz->bal = d-e;
    return max(d,e)+1;
}

/* Rotações à direita (LL e LR) 
   Retornará o endereço do nó que será a nova raiz da subárvore originalmente 
   iniciada por p */
PONT rotacaoL(PONT p){
    printf("Rotacao a esquerda, problema no no: %i\n",p->chave);
    PONT u, v;
    u = p->esquerda;
    if(u->bal == -1) {   // LL
        p->esquerda = u->direita;
        u->direita = p;
        p->bal = 0;
        u->bal = 0;
        return u;
    }
    else 
        if (u->bal == 1) {  // LR
            v = u->direita;
            u->direita = v->esquerda;
            v->esquerda = u;
            p->esquerda = v->direita;
            v->direita = p;
            if(v->bal == -1)
                p->bal = 1;
            else
                p->bal = 0;
            if(v->bal == 1)
                u->bal = -1;
            else
                u->bal = 0;
            v->bal = 0;
            return v;
	}else{   // caso necessario apenas para a exclusao (u->bal == 0)
            p->esquerda = u->direita;
            u->direita = p;
            // p->bal = -1;    desnecessario pois o balanceamento de p nao chegou a ser mudado para -2
            u->bal = 1;
            return u;
	}
}

/* Rotações à esquerda (RR e RL) 
   Retornará o endereço do nó que será a nova raiz da subárvore originalmente 
   iniciada por p */
PONT rotacaoR(PONT p){
    printf("Rotacao a direita, problema no no: %i\n",p->chave);
    PONT u, v;
    u = p->direita;
    if(u->bal == 1) {   // RR
        p->direita = u->esquerda;
        u->esquerda = p;
        p->bal = 0;
        u->bal = 0;
	return u;
    } 
    else 
        if (u->bal == -1){  // RL
            v = u->esquerda;
            u->esquerda = v->direita;
            v->direita = u;
            p->direita = v->esquerda;
            v->esquerda = p;
            if(v->bal == 1)
                p->bal = -1;
            else 
                p->bal = 0;
            if(v->bal == -1)
                u->bal = 1;
            else
                u->bal = 0;
            v->bal = 0;
            return v;
	}else{   // caso necessario apenas para a exclusao (u->bal == 0)
            p->direita = u->esquerda;
            u->esquerda = p;
            u->bal = -1;
            // p->bal = 1;    desnecessario pois o balanceamento de p nao chegou a ser mudado para 2
            return u;	
	}
}

/* Inserção AVL: p é inicializado com o endereco do nó raiz e 
   *alterou com false                                         */
void inserirAVL(PONT* pp, TIPOCHAVE ch, bool* alterou){
    PONT p = *pp;
    if(!p){
        *pp = criarNovoNo(ch);
        *alterou = true;
    } else {
        if(ch == p->chave)
            *alterou = false;
        else
            if(ch <= p->chave) {
                inserirAVL(&(p->esquerda), ch, alterou);
                if(*alterou)
                    switch (p->bal) {
                        case 1 :
                            p->bal = 0;
                            *alterou = false;
                            break;
			            case 0 : 
                            p->bal = -1;
                            break;
			            case -1:
                            *pp = rotacaoL(p);
                            *alterou = false;
                            break;
			}
		} else {
                    inserirAVL(&(p->direita), ch, alterou);
                    if(*alterou)
                        switch (p->bal) {
                            case -1:
                                p->bal = 0;
				*alterou = false;
                                break;
                            case 0 :
                                p->bal = 1;
				break;
                            case 1 :
                                *pp = rotacaoR(p);
				*alterou = false;
				break;
			}
		}
	}
}

/* Retorna o endereco do NO que contem chave=ch ou NULL caso a chave nao seja
       encontrada. Utiliza busca binaria recursiva                          */
PONT buscaBinaria(TIPOCHAVE ch, PONT raiz){
    if (raiz == NULL)
        return NULL;
    if (raiz->chave == ch)
        return raiz;
    if (raiz->chave<ch) 
        return buscaBinaria(ch,raiz->direita);
    return buscaBinaria(ch,raiz->esquerda);
}  

// Busca binária não recursiva devolvendo o nó pai
PONT buscaNo(PONT raiz, TIPOCHAVE ch, PONT *pai){
    PONT atual = raiz;
    *pai = NULL;
    while (atual) {
        if(atual->chave == ch)
            return(atual);
	*pai = atual;
	if(ch < atual->chave)
            atual = atual->esquerda;
	else
            atual = atual->direita;
    }
    return(NULL);
}

/* Auxilir da funcao excluirChave, procura a maior chave menor que a chave que 
   serah excluida.            */
PONT maiorAEsquerda(PONT p, PONT *ant){
    *ant = p;
    p = p->esquerda;
    while (p->direita) {
        *ant = p;
        p = p->direita;
    }
    return(p);
}

/* Exclui a chave com valor igual a ch.   */
bool excluirAVL(PONT* raiz, TIPOCHAVE ch, bool* alterou){
    PONT atual = *raiz;
    if (!atual) {
        *alterou = false;
        return false;
    }
    if (atual->chave == ch){
        PONT substituto, pai_substituto;
        if(!atual->esquerda || !atual->direita) { // tem zero ou um filho
            if(atual->esquerda)
                substituto = atual->esquerda;
            else 
                substituto = atual->direita;
            *raiz = substituto;
            free(atual);
            *alterou = true;
            return true;
        }
        else {   // tem dois filhos
            substituto = maiorAEsquerda(atual,&pai_substituto);
            atual->chave = substituto->chave;
            ch = substituto->chave; // continua o codigo excluindo o substituto
        }
    }
    bool res;
    if (ch > atual->chave) {
        res = excluirAVL(&(atual->direita), ch, alterou);
        printf("Excluir recursivo a direita: %i(%i)\n", atual->chave, atual->bal); 
        if (*alterou){
            switch (atual->bal){
                case 1:
                    atual->bal = 0;
                    return true;
                case 0:
                    atual->bal = -1;
                    *alterou = false;
                    return true;
                case -1:
                    *raiz = rotacaoL(atual);
                    if (atual->bal != 0)
                        *alterou = false;
                    return true;
            }
        }
    }else{
        res = excluirAVL(&(atual->esquerda), ch, alterou);
        printf("Excluir recursivo a esquerda: %i(%i)\n", atual->chave, atual->bal); 
        if (*alterou){
            switch (atual->bal){
                case -1:
                    atual->bal = 0;
                    return true;
                case 0:
                    atual->bal = 1;
                    *alterou = false;
                    return true;
                case 1:
                    *raiz = rotacaoR(atual);
                    if (atual->bal != 0)
                        *alterou = false;
                    return true;
            }
        }
    }
    return res;
}
/* Rotações à direita (LL e LR) */
void rotacaoL2(PONT *p) {
    printf("Rotacao a esquerda, problema no no: %i\n", (*p)->chave);
    PONT u, v;
    u = (*p)->esquerda;
    if (u->bal == -1) { // LL
        (*p)->esquerda = u->direita;
        u->direita = *p;
        (*p)->bal = 0;
        *p = u;
    } else { // LR
        v = u->direita;
        u->direita = v->esquerda;
        v->esquerda = u;
        (*p)->esquerda = v->direita;
        v->direita = *p;
        if (v->bal == -1)
            (*p)->bal = 1;
        else 
            (*p)->bal = 0;
        if (v->bal == 1)
            u->bal = -1;
        else 
            u->bal = 0;
        *p = v;
    }
    (*p)->bal = 0; // balanço final da raiz (p) da subarvore
}

/* Rotações à esquerda (RR e RL)    */
void rotacaoR2(PONT *p) {
    printf("Rotacao a direita, problema no no: %i\n", (*p)->chave);
    PONT u, v;
    u = (*p)->direita;
    if (u->bal == 1) { // RR
        (*p)->direita = u->esquerda;
        u->esquerda = *p;
        (*p)->bal = 0;
        *p = u;
    } else { // RL
        v = u->esquerda;
        u->esquerda = v->direita;
        v->direita = u;
        (*p)->direita = v->esquerda;
        v->esquerda = *p;
        if (v->bal == 1)
            (*p)->bal = -1;
        else 
            (*p)->bal = 0;
        if (v->bal == -1)
            u->bal = 1;
        else 
            u->bal = 0;
        *p = v;
    }
    (*p)->bal = 0; // balanço final da raiz (p) da subarvore
}
/* Inserção AVL2: p é inicializado com raiz e *alterou com false */
void inserirAVL2(PONT *pp, TIPOCHAVE ch, bool *alterou) {
    PONT p = *pp;
    if (!p) {
        *pp = criarNovoNo(ch);
        *alterou = true;
    } else {
        if (ch < p->chave) {
            inserirAVL2(&(p->esquerda), ch, alterou);
            if (*alterou)
                switch (p->bal) {
                    case 1: 
                        p->bal = 0;
                        *alterou = false;
                        break;
                    case 0: 
                        p->bal = -1;
                        break;
                    case -1: 
                        rotacaoL2(pp);
                        *alterou = false;
                        break;
                }
        } else {
            inserirAVL2(&(p->direita), ch, alterou);
            if (*alterou)
                switch (p->bal) {
                    case -1: 
                        p->bal = 0;
                        *alterou = false;
                        break;
                    case 0: 
                        p->bal = 1;
                        break;
                    case 1: 
                        rotacaoR2(pp);
                        *alterou = false;
                        break;
                }
        }
    }
}

/* funcao auxiliar na destruicao (liberacao da memoria) de uma arvore */
void destruirAux(PONT subRaiz){
    if (subRaiz){
	destruirAux(subRaiz->esquerda);
	destruirAux(subRaiz->direita);
	free(subRaiz);
    }
}

/* libera toda memoria de uma arvore e coloca NULL no valor da raiz    */
void destruirArvore(PONT * raiz){
    destruirAux(*raiz);
    *raiz = NULL;
}

/* inicializa arvore: raiz=NULL */
void inicializar(PONT * raiz){
    *raiz = NULL;
}

void travessiaAux(PONT p, int *niv, TIPOCHAVE ch, bool *achou) {
    if (p) {
        (*niv)++; // *niv = *niv + 1;
        if (p->chave == ch)
            *achou = true;
        else {
            travessiaAux(p->esquerda, niv, ch, achou);
            if (!(*achou)) 
                travessiaAux(p->direita, niv, ch, achou);
            if (!(*achou)) 
                *niv = *niv - 1;
        }
    }
}

/* Retorna true e o nivel de uma chave (caso seja encontrada) e false caso 
       contrario.                                                                */
bool travessia(PONT p, int *niv, TIPOCHAVE ch) {
    *niv = 0;
    PONT temp = buscaBinaria(ch, p);
    if (temp) {
        bool achou = false;
        travessiaAux(p, niv, ch, &achou);
        return true;
    } else 
        return false;
}

/*
 * 
 */
int main(int argc, char** argv) {
    PONT arvoreAVL;
    bool *mudou;
    int n;
    
    cout << "INICIANDO A ARVORE" << endl;
    inicializar(&arvoreAVL);


    return 0;
}

