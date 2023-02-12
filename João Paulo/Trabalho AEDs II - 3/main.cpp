/*  Universidade Federal de Alfenas (UNIFAL) - 2023
*   Discentes: Joao Paulo Martyr Ragazzo (RA: 2022.1.08.009)
*              Matheus Martins dos Santos (RA: 2022.1.08.025)
*              Luca Barbosa de Oliveira Vieira (RA: 2022.1.08.022)
*
*   Docente: Paulo Alexandre Bressan - Algoritimo e Estrutura de Dados II
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

/**
 * Struct veiculo e a principal Struct desse projeto. Ela guarda os seguintes valores:
 * Modelo -> O modelo do carro que sera guardado
 * Marca - > A marca do carro que sera guardado
 * Tipo -> O tipo do carro que sera guardado
 * Ano -> O ano em que o carro foi fabricado
 * Km -> A kilometragem atual do carro
 * Potência -> A potência do motor
 * Combustível -> Disel, gasolina ou flex
 * Câmbio -> Automatico ou manual
 * Direçao -> Mecânica, hidraulica ou eletrica
 * Cor -> A cor do carro em questao
 * Portas -> A quantidade de portas presentes no carro
 * Placa -> A placa do carro que sera guardado
 * Preço -> O preço do carro
 * 
*/
struct veiculo {
    string modelo; 
    string marca;
    string tipo;
    int ano;
    int km;
    float potencia;
    string combustivel;
    string cambio;
    string direcao;
    string cor;
    int portas;
    string placa;
    float preco;
};

/**
 * Struct que representa o nó da Lista Principal
 * carro -> Ponteiro que aponta para o carro do nó
 * proximo -> Ponteiro que aponta para o próximo elemento da lista encadeada
*/
struct no_ {
    veiculo * carro;
    no_ * proximo;
};

/**
 * Struct que representa o nó de uma árvore binária
 * placa -> A placa do veículo em que o noArv está representado
 * no -> o nó em que o noArv está apontando da ListaPrincipal
 * esquerda -> proxima folha a esquerda da ListaPrincipal
 * direita -> próxima folha a direita da ListaPrincipal
*/
struct noArv {
    string placa;
    no_ * no;
    noArv * esquerda;
    noArv * direita; 
};

/**
 * Struct que representa o nó de uma árvore AVL, com o coeficiente de balanceamento
 * placa -> A placa ao qual o nó está apontando
 * no -> O nó da lista principal representado por uma folha da árvore
 * esquerda -> a próxima folha a esquerda
 * direita -> a próxima folha a direita
 * bal -> coeficiente de balanceamento da árvore AVL
*/
struct noArvAVL {
    string placa;
    no_ * no;
    noArvAVL * esquerda;
    noArvAVL * direita;
    int bal;
};

/**
 * Cabeçalho da árvore
 * cabeca aponta para o primeiro nó da arvore
*/
struct arvore {
    noArv * arvore_binaria;
    noArvAVL * arvore_avl;
};

/**
 * Cabeçalho da lista principal
 * primeiro -> aponta para o primeiro nó da lista principal
 * ultimo -> aponta para o último nó da lista principal
*/
struct cabecalho {
    no_ * primeiro;
    no_ * ultimo;
};

/**
 * Inicia a lista principal
 * @return A lista principal
*/
cabecalho * inicia_lista(void) {
    cabecalho * tmp = new cabecalho;
    tmp->primeiro = NULL;
    tmp->ultimo = NULL;
    return tmp;
}

/**
 * Inicia uma árvore binária
 * @return A árvore binária
*/
arvore * inicia_arvore(void) {
    arvore * tmp = new arvore;
    tmp->arvore_binaria = NULL;
    tmp->arvore_avl = NULL;
    return tmp;
}

/**
 * Procura um nó em uma árvore binária
 * @param cabeca O endereço do primeiro ponteiro que aponta para o primeiro nó da árvore
 * @param placa A placa a ser procurada na árvore binária
 * @returns Um ponteiro que aponta para o ponteiro que aponta para o nó da placa
 * @returns NULL, caso não seja possível encontrar o nó
*/
noArv ** encontrar_no(noArv ** cabeca, string placa) {
    noArv * noAtual = *&*cabeca;
    noArv ** ponteiro = cabeca;

    while(noAtual->placa != placa) {

        if(noAtual->placa < placa) {
            ponteiro = &noAtual->direita;
            noAtual = noAtual->direita;

        } else if (noAtual->placa > placa) {
            ponteiro = &noAtual->esquerda;
            noAtual = noAtual->esquerda;
        }

        if(!noAtual) {
            return NULL;
        }
    }

    /**
     * Observação: Ao chamar a função, não tentar usar o *&* antes de checar 
     * se o ponteiro que retorna ser diferente de NULL. Caso contrário, poderá
     * dar algum tipo de falha na segmentação. 
    */


    return ponteiro;
}

/**
 * Cria um novo nó para a árvore binária de busca
 * @param no o nó ao qual a nova folha da árvore binária de busca estará apontando
 * @return o novo nó criado
*/
noArv * criarNovoNo_(no_ * no) {
    noArv * novoNo = new noArv;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    novoNo->placa = no->carro->placa;
    novoNo->no = no;
    return novoNo;
}

/**
 * Realiza a criação de um novo nó para a árvore AVL
 * @param no O nó da lista principal ao qual a nova folha da árvore AVL vai estar apontando
 * @return o ponteiro para o novo nó de folha criado para a árvore AVL
 * @authors http://www.each.usp.br/digiampietri/ACH2023/javaec/ArvoreAVL/arvoreAVL.c
*/
noArvAVL * criarNovoNo(no_ * no){
    noArvAVL * novoNo = new noArvAVL;
    novoNo->no = no;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    novoNo->placa = no->carro->placa;
    novoNo->bal = 0;
    return novoNo;
}

/**
 * Exibe o relatório da lista principal
 * @param listaPrincipal o cabeçalho da lista principal que será inserida.
*/
void relatorio(cabecalho * listaPrincipal) {
    no_ * atual = listaPrincipal->primeiro;

    if (!atual) {
        cout << "A lista principal está vazia. Impossível imprimir o relatório." << endl;
        return;
    }

    cout << "+---------+-------------------+------------+---------+------+--------+-----+--------+------------+------------+----------+----+--------+" << endl;
    cout << "|  PLACA  |      MODELO       |    MARCA   |   TIPO  |  ANO |   KM   | POT |  COMB  |   CAMBIO   |   DIREÇAO  |    COR   | PT | PREÇO  |" << endl;
    cout << "+---------+-------------------+------------+---------+------+--------+-----+--------+------------+------------+----------+----+--------+" << endl;

    while(atual) {
        cout << "| " << setw(6) << atual->carro->placa;
        cout << " | " << setw(17) << atual->carro->modelo;
        cout << " | " << setw(10) << atual->carro->marca;
        cout << " | " << setw(7) << atual->carro->tipo;
        cout << " | " << setw(4) << atual->carro->ano;
        cout << " | " << setw(6) << atual->carro->km;
        cout << " | " << setw(3) << atual->carro->potencia;

        if(atual->carro->combustivel == "Gasolina") {
            cout << " | " << setw(6) << "Gaso.";
        } else {
            cout << " | " << setw(6) << atual->carro->combustivel;
        }

        cout << " | " << setw(10) << atual->carro->cambio;
        cout << " | " << setw(10) << atual->carro->direcao;
        cout << " | " << setw(8) << atual->carro->cor;
        cout << " | " << setw(2) << atual->carro->portas;
        cout << " | " << setw(6) << atual->carro->preco << " |" << endl;
        atual = atual->proximo;
    }

    cout << "+---------+-------------------+------------+---------+------+--------+-----+--------+------------+------------+----------+----+--------+\033[0m" << endl;

}

/**
 * Imprime a lista de todos os carros de uma árvore em pré-ordem sem o cabecalho das informações
 * @param cabeca o primeiro nó da árvore binária
*/
void relatorio_binaria(noArv * cabeca) {
    
    if (!cabeca) {
        cout << "Impossível mostrar o relatório. A árvore está vazia" << endl;
        return;
    }

    cout << "| " << setw(6) << cabeca->no->carro->placa;
    cout << " | " << setw(17) << cabeca->no->carro->modelo;
    cout << " | " << setw(10) << cabeca->no->carro->marca;
    cout << " | " << setw(7) << cabeca->no->carro->tipo;
    cout << " | " << setw(4) << cabeca->no->carro->ano;
    cout << " | " << setw(6) << cabeca->no->carro->km;
    cout << " | " << setw(3) << cabeca->no->carro->potencia;

    if(cabeca->no->carro->combustivel == "Gasolina") {
        cout << " | " << setw(6) << "Gaso.";
    } else {
        cout << " | " << setw(6) << cabeca->no->carro->combustivel;
    }

    cout << " | " << setw(10) << cabeca->no->carro->cambio;
    cout << " | " << setw(10) << cabeca->no->carro->direcao;
    cout << " | " << setw(8) << cabeca->no->carro->cor;
    cout << " | " << setw(2) << cabeca->no->carro->portas;
    cout << " | " << setw(6) << cabeca->no->carro->preco << " |" << endl;

    if(cabeca->esquerda) 
        relatorio_binaria(cabeca->esquerda);

    if(cabeca->direita) 
        relatorio_binaria(cabeca->direita);

}

/**
 * Faz o relatório da árvore principal em pre-ordem
 * @param cabeca o primeiro nó da árvore AVL
*/
void relatorio_avl(noArvAVL * cabeca) {
    if (!cabeca) {
        cout << "Impossível mostrar o relatório. A árvore está vazia." << endl;
        return;
    }

    cout << "| " << setw(6) << cabeca->no->carro->placa;
    cout << " | " << setw(17) << cabeca->no->carro->modelo;
    cout << " | " << setw(10) << cabeca->no->carro->marca;
    cout << " | " << setw(7) << cabeca->no->carro->tipo;
    cout << " | " << setw(4) << cabeca->no->carro->ano;
    cout << " | " << setw(6) << cabeca->no->carro->km;
    cout << " | " << setw(3) << cabeca->no->carro->potencia;

    if(cabeca->no->carro->combustivel == "Gasolina") {
        cout << " | " << setw(6) << "Gaso.";
    } else {
        cout << " | " << setw(6) << cabeca->no->carro->combustivel;
    }

    cout << " | " << setw(10) << cabeca->no->carro->cambio;
    cout << " | " << setw(10) << cabeca->no->carro->direcao;
    cout << " | " << setw(8) << cabeca->no->carro->cor;
    cout << " | " << setw(2) << cabeca->no->carro->portas;
    cout << " | " << setw(6) << cabeca->no->carro->preco << " |" << endl;

    if(cabeca->esquerda) 
        relatorio_avl(cabeca->esquerda);

    if(cabeca->direita) 
        relatorio_avl(cabeca->direita);
}

/**
 * Imprime o relatório de uma árvore binária em pré-ordem com o cabeçalho
 * Observação: colocar apenas uma arvore, e a outra deixar como NULL
 * @param binaria a arvore binaria que irá realizar o relatório em préordem 
 * @param avl a arvore avl que irá realizar o relatório em préordem
*/
void relatorio_preordem(noArv * binaria = NULL, noArvAVL * avl = NULL) {
    if (binaria && avl) 
        return;
    

    cout << "+---------+-------------------+------------+---------+------+--------+-----+--------+------------+------------+----------+----+--------+" << endl;
    cout << "|  PLACA  |      MODELO       |    MARCA   |   TIPO  |  ANO |   KM   | POT |  COMB  |   CAMBIO   |   DIREÇAO  |    COR   | PT | PREÇO  |" << endl;
    cout << "+---------+-------------------+------------+---------+------+--------+-----+--------+------------+------------+----------+----+--------+" << endl;

    if (binaria)
        relatorio_binaria(binaria);
    else if (avl) 
        relatorio_avl(avl);

    cout << "+---------+-------------------+------------+---------+------+--------+-----+--------+------------+------------+----------+----+--------+\033[0m" << endl;

}

/**
 * Realiza a rotação do tipo L para manter a árvore AVL equilibrada
 * @param p o ponteiro de um nó da árvore AVL
 * @return um ponteiro para o nó da árvore AVL
 * @authors http://www.each.usp.br/digiampietri/ACH2023/javaec/ArvoreAVL/arvoreAVL.c
*/
noArvAVL * rotacaoL(noArvAVL * p){
    noArvAVL * u, * v;
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
 
/**
 *  Rotações à esquerda (RR e RL) 
 *  Retornará o endereço do nó que será a nova raiz da subárvore originalmente
 *  @param p o ponteiro de um nó da árvore AVL onde será relizada a rotação
 *  @authors http://www.each.usp.br/digiampietri/ACH2023/javaec/ArvoreAVL/arvoreAVL.c
*/
noArvAVL * rotacaoR(noArvAVL * p){
    noArvAVL * u, * v;
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
 
/**
 * Realiza uma inserção na árvore AVL
 * @param pp o nó raiz da árvore
 * @param placa a placa do carro ao qual o nó da lista principal se refere
 * @param alterou 
 * @param no o nó da lista principal que será indicado pela folha da raiz
 * @author http://www.each.usp.br/digiampietri/ACH2023/javaec/ArvoreAVL/arvoreAVL.c
*/                                       
void inserir_arv_avl(noArvAVL ** pp, string placa, bool* alterou, no_ * no){
    noArvAVL * p = *pp;
    if(!p){
        *pp = criarNovoNo(no);
        *alterou = true;
    } else {
        if(placa == p->placa)
            *alterou = false;
        else
            if(placa <= p->placa) {
                inserir_arv_avl(&(p->esquerda), placa, alterou, no);
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
                    inserir_arv_avl(&(p->direita), placa, alterou, no);
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

/**
 * Insere um novo nó na árvore binária
 * @param folha a primeira folha da árvore binária de onde será inserido o novo nó
 * @param no o nó que a struct da folha irá apontar
 * @return 1 caso seja possível realizar a inserção
 * @return 0 caso não seja possível realizar a inserção
*/
int inserir_arv_binaria(noArv * folha, no_ * no) {
    if (folha->placa == no->carro->placa) {
        return 0;
    }

    if (folha->placa > no->carro->placa) {
        if (!folha->esquerda) {
            folha->esquerda = criarNovoNo_(no);
            return 1;
        }

        return inserir_arv_binaria(folha->esquerda, no);
    }

    if (folha->placa < no->carro->placa) {
        if (!folha->direita) {
            folha->direita = criarNovoNo_(no);
            return 1;
        }

        return inserir_arv_binaria(folha->direita, no);
    }

    return 0;
}

/**
 * Insere um veículo na listaPrincipal, na árvore binária AVL e na arvore binária de busca simultâneamente
 * @param listaPrincipal a lista principal onde será inserido o novo veículo
 * @param avl a árvore binária AVL onde será inserido o novo veículo
 * @param binaria a árvore binária de busca onde será inserido o novo véiculo
 * @param carro o novo carro que será inserido nas estruturas
*/
int inserir_veiculo(cabecalho * listaPrincipal, arvore * arvores, veiculo * carro, bool alterou) {

    no_ * novoNo = new no_; /* O novo nó que será inserido na listaPrincipal*/
    novoNo->carro = carro;
    novoNo->proximo = NULL;

    if (!listaPrincipal->primeiro) {
        listaPrincipal->primeiro = novoNo;
        listaPrincipal->ultimo = novoNo;
    } else {
        listaPrincipal->ultimo->proximo = novoNo;
        listaPrincipal->ultimo = novoNo;
    }

    if (carro->ano <= 2016) {
        if (!arvores->arvore_binaria) {
            noArv * novaFolha = new noArv;
            arvores->arvore_binaria = novaFolha;
            novaFolha->direita = NULL;
            novaFolha->esquerda = NULL;
            novaFolha->placa = carro->placa;
            novaFolha->no = novoNo;
        } else {
            inserir_arv_binaria(arvores->arvore_binaria, novoNo);
        } 
    }

    if(carro->ano > 2016) { /*Filtro para carro manual AVL*/
        if(!arvores->arvore_avl) {
            noArvAVL * novaFolha = new noArvAVL;
            arvores->arvore_avl = novaFolha;
            novaFolha->bal = 0;
            novaFolha->direita = NULL;
            novaFolha->esquerda = NULL;
            novaFolha->placa = carro->placa;
            novaFolha->no = novoNo;
        } else {
            inserir_arv_avl(&arvores->arvore_avl, carro->placa, &alterou, novoNo);
        }
    }

    return 1;
}

/**
 * Função desenvolvida como auxiliar da função excluirChave, procura a maior placa menor que a placa que será excluida.
 * @authors http://www.each.usp.br/digiampietri/ACH2023/javaec/ArvoreAVL/arvoreAVL.c 
 */ 
noArvAVL * maiorAEsquerda(noArvAVL *p, noArvAVL **ant){
    *ant = p;
    p = p->esquerda;
    while (p->direita) {
        *ant = p;
        p = p->direita;
    }
    return(p);
}
 
/**
 * Exclui um nó da árvore AVL
 * @param raiz o ponteiro que aponta para o ponteiro que aponta para a raiz da árvore
 * @param placa a placa do veículo que será excluido da árvore
 * @param alterou 
 * @param no o nó da lista principal ao qual o nó da folha está se referindo
 * @returns true para casp tenha sido possível realizar a remoção 
 * @returns false para caso não tenha sido possível realizar a remoção
 * @authors http://www.each.usp.br/digiampietri/ACH2023/javaec/ArvoreAVL/arvoreAVL.c
*/
int excluir_arv_avl(noArvAVL ** raiz, string placa, bool* alterou){
    noArvAVL * atual = *raiz;
    if (!atual) {
        *alterou = false;
        return 0;
    }

    if (atual->placa == placa){
        noArvAVL * substituto, *pai_substituto;
        if (!atual->esquerda || !atual->direita) { // tem zero ou um filho
            if (atual->esquerda)
                substituto = atual->esquerda;
            else 
                substituto = atual->direita;
            *raiz = substituto;
            delete atual;
            *alterou = true;
            return 1;
        }
        else {
            substituto = maiorAEsquerda(atual->direita,&pai_substituto);
            atual->placa = substituto->placa;
            atual->no = substituto->no;
            placa = substituto->placa; // continua o codigo excluindo o substituto
        }
    }

    int res;

    if (placa > atual->placa) {
        res = excluir_arv_avl(&(atual->direita), placa, alterou);
        if (*alterou) {
            switch (atual->bal) {
                case 1:
                    atual->bal = 0;
                    return 1;
                case 0:
                    atual->bal = -1;
                    *alterou = false;
                    return 1;
                case -1:
                    *raiz = rotacaoL(atual);
                    if (atual->bal != 0)
                        *alterou = false;
                    return 1;
            }
        }
    } else {
        res = excluir_arv_avl(&(atual->esquerda), placa, alterou);
        if (*alterou){
            switch (atual->bal){
                case -1:
                    atual->bal = 0;
                    return 1;
                case 0:
                    atual->bal = 1;
                    *alterou = false;
                    return 1;
                case 1:
                    *raiz = rotacaoR(atual);
                    if (atual->bal != 0)
                        *alterou = false;
                    return 1;
            }
        }
    }
    return res;
}

/**
 * Remove um nó da árvore binária
 * @param cabeca O endereço do primeiro ponteiro que aponta para o primeiro nó da árvore
 * @param placa A placa a ser procurada na árvore binária
 * @returns 1 caso seja possível realizar a remoção
 * @returns 0 caso não seja possível realizar a remoção
*/
int remover_arv_binaria(noArv ** cabeca, string placa) {
    
    noArv ** pontExcluir = encontrar_no(cabeca, placa);

    if (!pontExcluir) { /* Caso pontExcluir == NULL, então quer dizer que não foi encontrado */
        return 0;
    }
    
    noArv * noExcluir = *&*pontExcluir;

    if (!noExcluir->esquerda && !noExcluir->direita) { /* Caso noExcluir seja o último da árvore */
        *pontExcluir = NULL;
        delete noExcluir;
        return 1;
    }

    if (!noExcluir->esquerda && noExcluir->direita) {
        *pontExcluir = noExcluir->direita;
        delete noExcluir;
        return 1;
    }

    noArv * tmp = noExcluir->esquerda;
    noArv * tmp_pai = noExcluir;

    while(tmp->direita) {
        tmp_pai = tmp;
        tmp = tmp->direita;
    }

    tmp->direita = noExcluir->direita;
    tmp->esquerda = noExcluir->esquerda;
    tmp_pai->direita = NULL;
    *pontExcluir = tmp;


    return 1;
}

/**
 * Remove um veículo da lista principal, da árvore AVL e da árvore binária simultâneamente
 * @param listaPrincipal a ListaPrincipal de onde será removido o vepiculo
 * @param avl a árvore binária AVL de onde será removido o veículo
 * @param binaria a árvore binária de busca de onde será removido o veículo
 * @param placa a placa do veículo que será removido das estruturas
 * @returns 1 caso seja possível realizar a remoção
 * @returns 0 caso não seja possível realizar a remoção
*/
int remover_veiculo(cabecalho * listaPrincipal, string placa) {
    no_ * atual = listaPrincipal->primeiro;
    no_ * anterior = NULL;

    while (atual && atual->carro->placa != placa) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (!anterior) {
        listaPrincipal->primeiro = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    delete atual->carro;
    delete atual;

    return 1;
}

/**
 * Mostra o menu de opções principais para o usuario
 * @return A string com a opçao escolhida pelo usuario
*/
string menu_opcoes(void) {
    string option;
    string opcoes = "\033[1mO que você deseja fazer? \033[0m(I)nserir, (C)onsulta, (R)elatório, (B)inaria, (A)VL, (S)air => ";
    cout << "\n" << opcoes;
    cin >> option;

    while(toupper(option[0]) != 'I' && toupper(option[0]) != 'C' && toupper(option[0]) != 'R' && toupper(option[0]) != 'B' && 
          toupper(option[0]) != 'A' && toupper(option[0]) != 'S') {
            cout << "\033[31mOpçao invalida. Por favor, tente novamente.\033[0m" << endl;
            cout << opcoes;
            cin >> option;
          }
    
    return option;
}

/**
 * Torna todas as letras da string em maiúsculas
 * @param info A string que será colocada modificada
 * @return A string com todas as letras maiúsculas
*/
string all_upper(string info){
    for(int i = 0; i < info.length(); i++){
        info[i] = toupper(info[i]);
    }

    return info;
}


/**
 * Realiza uma consulta na lista principal, depois mostra as opções de exclusão e informações
 * @param listaPrincipal a lista principal
 * @param arvores o cabeçalho das arvores
 * @param alterou variavel auxiliar para o balanceamento da arvore AVL
*/
void consulta(cabecalho * listaPrincipal, arvore * arvores, bool * alterou) {

    string placa;

    if(!listaPrincipal->primeiro) {
        cout << "\033[31mImpossível realizar uma consulta. O banco de dados está vazio." << endl;
        return;
    }

    cout << "\033[1mDigite a placa que você deseja consultar =>\033[0m ";
    cin >> placa;

    placa = all_upper(placa);

    no_ * atual = listaPrincipal->primeiro;

    if(!atual) {
        cout << "A lista principal está vazia." << endl;
        return;
    }

    while(atual->carro->placa != placa) {
        atual = atual->proximo;
        
        if (!atual)
            break;
    }

    if(!atual) {
        cout << "\033[31mNão foi encontrado nenhum carro com essa placa. Por favor, tente novamente.\033[0m";
        return;
    }

    cout << "\033[32mVeículo encontrado com sucesso no banco de dados!\033[0m" << endl;
    cout << "\033[1mO que você deseja fazer com o veículo encontrado?\033[0m (I)nformações, (E)xcluir, (V)oltar => ";
    string option;
    cin >> option;
                
    while(toupper(option[0]) != 'I' && toupper(option[0]) != 'E' && toupper(option[0]) != 'V'){
        cout << "\033[31mOpçao invalida. Por favor, tente novamente.\033[0m" << endl;
        cout << "\033[1mO que você deseja fazer com o veículo encontrado?\033[0m (I)nformações, (R)emover, (V)oltar => ";
        cin >> option;
    }

    if(toupper(option[0]) == 'V') 
        return;

    if(toupper(option[0]) == 'I') {
        cout << "+---------+-------------------+------------+---------+------+--------+-----+----------+------------+------------+----------+----+--------+" << endl;
        cout << "|  PLACA  |      MODELO       |    MARCA   |   TIPO  | ANO  |   KM   | POT |   COMB   |   CAMBIO   |   DIREÇAO  |    COR   | PT | PREÇO  |" << endl;
        cout << "+---------+-------------------+------------+---------+------+--------+-----+----------+------------+------------+----------+----+--------+" << endl;
        cout << "| " << setw(6) << atual->carro->placa;
        cout << " | " << setw(17) << atual->carro->modelo;
        cout << " | " << setw(10) << atual->carro->marca;
        cout << " | " << setw(7) << atual->carro->tipo;
        cout << " | " << setw(4) << atual->carro->ano;
        cout << " | " << setw(6) << atual->carro->km;
        cout << " | " << setw(3) << atual->carro->potencia;
        cout << " | " << setw(8) << atual->carro->combustivel;
        cout << " | " << setw(10) << atual->carro->cambio;
        cout << " | " << setw(10) << atual->carro->direcao;
        cout << " | " << setw(8) << atual->carro->cor;
        cout << " | " << setw(2) << atual->carro->portas;
        cout << " | " << setw(6) << atual->carro->preco << " |" << endl;
        cout << "+---------+-------------------+------------+---------+------+--------+-----+----------+------------+------------+----------+----+--------+\033[0m" << endl;
        return;
    }

    if(toupper(option[0]) == 'E') {
        if(remover_veiculo(listaPrincipal, placa)) {
            excluir_arv_avl(&arvores->arvore_avl, placa, alterou);
            remover_arv_binaria(&arvores->arvore_binaria, placa);
            cout << "\033[32mVeículo deletado com sucesso no banco de dados!\033[0m" << endl;
        };
        return;
    }  

}

/**
 * Checa se uma determinada string contem o parametro e se encaixa como uma placa válida,
 * no formato LLL0000, (3 letras seguidos de 4 números).
 * @param placa A string placa a ser checada se é ou não é uma placa
 * @return true caso seja válida, false caso seja inválida
*/
bool e_placa(string placa){
    if(placa.length() != 7)
        return false;

    for(int i = 0; i <= 2; i++){
        if(!isalpha(placa[i])) 
            return false;
    }

    for(int i = 3; i <= 6; i++){
        if(!isdigit(placa[i]))
            return false;
    }

    return true;
}

/**
 * Busca um carro na lista principal
 * @param listaPrincipal a lista ao qual será realizado o procedimento de busca
 * @param placa a placa que será pesquisada na listaPrincipal
 * @return true caso o veículo exista
 * @return false caso o veículo não exista
*/
bool busca(cabecalho * listaPrincipal, string placa) {
    no_ * atual = listaPrincipal->primeiro;

    while(atual->carro->placa != placa) {
        atual = atual->proximo;

        if(!atual)
            break;
    }

    if(atual)
        return true;
    
    return false;
}

/**
 * Checa se todos os valores passados por uma string sao números (0, 1, 2, 3, 4, 5, 6, 7, 8, 9)
 * @param info A informaçao a ser checada 
 * @return 1 Caso todos os valores sao números / 0 Caso exista algum outro char na string
*/
int sao_digitos(string info){
    return info.find_first_not_of("0123456789.") == string::npos;
}

/**
 * heca se todos os valores passados por uma string sao caracteres (a, b, c, d, e, f...)
 * @param info A informaçao a ser checada
 * @return 1 Caso todos os valores sao caracteres / 0 Caso exista algum número
*/
int sao_chars(string info){
    return info.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZçÇ-_") == string::npos;
}

/**
 * Coloca apenas a primeira letra da string em letra maiúsculas, o resto ficará em letras minusculas
 * @param info A string que será modificada
 * @return A string com a primeira letra maiúscula, e as restantes minusculas
*/
string first_upper(string info){
    info[0] = toupper(info[0]);

    for(int i = 1; i < info.length(); i++){
        info[i] = tolower(info[i]);
    }

    return info;
}

/**
 * @return  ano atual de acordo com o horario do sistema
*/
int ano_atual(void){
    time_t now = time(0);
    tm *data = localtime(&now);
    return data->tm_year + 1900;
}

/**
 * Insere um novo carro no banco de dados 
 * @param listaPrincipal a lista principal a qual o carro será inserido
 * @param arvores cabeçalho das arvores ao qual o carro será inserido
 * @param alterou parametro para auxiliar no equilibrio da arvore AVL
*/
void novo_carro(cabecalho * listaPrincipal, arvore * arvores, bool * alterou) {
    string stringInput;
    veiculo * carro = new veiculo;

    cout << "Por favor, forneça as seguintes informações sobre o veículo que deseja inserir: " << endl;
    cout << "\033[1;33mImportante: \033[0mDigite \033[1m\"!sair\"\033[0m a qualquer momento para sair." << endl;
    cout << "\033[1mPlaca (AAA0000): \033[0m";
    cin >> stringInput;

    if(stringInput == "!sair")
        return;

    stringInput = all_upper(stringInput);

    bool existe = busca(listaPrincipal, stringInput);
    bool valido = e_placa(stringInput);

    while((existe || !valido) && stringInput != "!sair"){
        if(existe){
            cout << "\033[31mEsse veículo ja existe em nosso Banco de Dados. Por favor, tente novamente!\033[0m" << endl;
        } else if (!valido){
            cout << "\033[31mPlaca não possui o formato certo. Por favor, tente novamente!\033[0m" << endl;
        }

        cout << "\033[1mPlaca (AAA0000): \033[0m";
        cin >> stringInput;
        stringInput = all_upper(stringInput);
        existe = busca(listaPrincipal, stringInput);
        valido = e_placa(stringInput);
    }

    if(stringInput == "!sair")
        return;

    for(int i = 0; i <= 2; i++){
        stringInput[i] = toupper(stringInput[i]);
    }

    carro->placa = stringInput;

    cout << "\033[1mModelo: \033[0m";
    cin >> stringInput;

    if(stringInput == "!sair")
        return;

    carro->modelo = all_upper(stringInput);

    cout << "\033[1mMarca: \033[0m";
    cin >> stringInput;

    if(stringInput == "!sair")
        return;

    while(!sao_chars(stringInput) && stringInput != "!sair"){
        cout << "\033[31mMarca inválido. Por favor, use apenas letras ou '-'.\033[0m" << endl;
        cout << "\033[1mMarca: \033[0m";
        cin >> stringInput;
    }

    if(stringInput == "!sair")
        return;

    carro->marca = all_upper(stringInput);

    cout << "\033[1mTipo: \033[0m";
    cin >> stringInput;

    while(!sao_chars(stringInput) && stringInput != "!sair"){
        cout << "\033[31mTipo inválido. Por favor, utilize apenas letras ou '-'.\033[0m" << endl;
        cout << "\033[1mTipo: \033[0m";
        cin >> stringInput;
    }

    if(stringInput == "!sair")
        return;

    carro->tipo = first_upper(stringInput);

    cout << "\033[1mAno: \033[0m";
    cin >> stringInput;

    if(stringInput == "!sair")
        return;

    while((!sao_digitos(stringInput) || stoi(stringInput) < 1900 || stoi(stringInput) > ano_atual() + 2) && stringInput != "!sair"){
        cout << "\033[31mAno invalido. Por favor, tente novamente!\033[0m" << endl;
        cout << "\033[1mAno: \033[0m";
        cin >> stringInput;
    }
            
    if(stringInput == "!sair")
        return;
            
    carro->ano = stoi(stringInput);

    cout << "\033[1mKm: \033[0m";
    cin >> stringInput;

    if(stringInput == "!sair")
        return;

    while((!sao_digitos(stringInput) || stoi(stringInput) < 0) && stringInput != "!sair"){
        cout << "\033[31mKilometragem invalida. Por favor, tente novamente!\033[0m" << endl;
        cout << "\033[1mKm: \033[0m";
        cin >> stringInput;
    }
            
    if(stringInput == "!sair")
        return;
            
    carro->km = stoi(stringInput);

    cout << "\033[1mPotência: \033[0m";
    cin >> stringInput;

    while((!sao_digitos(stringInput) || stof(stringInput) < 1.0) && stringInput != "!sair"){
        cout << "\033[31mPotência invalida. Por favor, tente novamente!\033[0m" << endl;
        cout << "\033[1mPotência: \033[0m";
        cin >> stringInput;
    }

    if(stringInput == "!sair")
        return;

    carro->potencia = stof(stringInput);

    cout << "\033[1mCombustível:\033[0m (D)iesel, (G)asolina, (F)lex => ";
    cin >> stringInput;

    if(stringInput == "!sair")
        return;

    while(toupper(stringInput[0]) != 'F' && toupper(stringInput[0]) != 'D' && toupper(stringInput[0]) != 'G' && stringInput != "!sair"){
        cout << "\033[31mCombustível invalido. Por favor, tente novamente!\033[0m" << endl;
        cout << "\033[1mCombustível:\033[0m (D)iesel, (G)asolina, (F)lex => ";
        cin >> stringInput;
    }

    if(stringInput == "!sair")
        return;

    switch (toupper(stringInput[0])) {
        case 'D':
            carro->combustivel = "Diesel";
            break;

        case 'G':
            carro->combustivel = "Gasolina";
            break;

        case 'F':
            carro->combustivel = "Flex";
            break;
    }

    cout << "\033[1mCâmbio:\033[0m (A)utomatico, (M)anual => ";
    cin >> stringInput;

    if(stringInput == "!sair")
        return;


    while(toupper(stringInput[0]) != 'A' && toupper(stringInput[0]) != 'M' && stringInput != "!sair"){
        cout << "\033[31mCâmbio invalido. Por favor, tente novamente!\033[0m" << endl;
        cout << "\033[1mCâmbio:\033[0m (A)utomatico, (M)anual => ";
        cin >> stringInput;
    }

    if(stringInput == "!sair")
        return;

    switch (toupper(stringInput[0])) {
        case 'A':
            carro->cambio = "Automatico";
            break;
                
        case 'M':
            carro->cambio = "Manual";
            break;    
    }

    cout << "\033[1mDireçao: \033[0m (H)idraulica, (M)ecânica, (E)letrica => ";
    cin >> stringInput;

    if(stringInput == "!sair")
        return;

    while(toupper(stringInput[0]) != 'H' && toupper(stringInput[0]) != 'M' && toupper(stringInput[0]) != 'E' && stringInput != "sair"){
        cout << "\033[31mDireçao invalida. Por favor, tente novamente!\033[0m" << endl;
        cout << "\033[1mDireçao: \033[0m (H)idraulica, (M)ecânica, (E)letrica => ";
        cin >> stringInput;
    }

    if(stringInput == "!sair")
        return;

    switch (toupper(stringInput[0])) {
        case 'H':
            carro->direcao = "Hidraulica";
            break;
                
        case 'M':
            carro->direcao = "Mecanica";
            break;
                
        case 'E':
            carro->direcao = "Eletrica";
            break;
    }

    cout << "\033[1mCor: \033[0m";
    cin >> stringInput;

    if(stringInput == "!sair")
        return;

    while(!sao_chars(stringInput) && stringInput != "!sair"){
        cout << "\033[31mCor inválida. Por favor, digite apenas letras.\033[0m" << endl;
        cout << "\033[1mCor: \033[0m";
        cin >> stringInput;
    }

    if(stringInput == "!sair")
        return;

    carro->cor = first_upper(stringInput);

    cout << "\033[1mPortas: \033[0m";
    cin >> stringInput;

    if(stringInput == "!sair")
        return;

    while((!sao_digitos(stringInput) || stoi(stringInput) <= 0) && stringInput != "!sair" ){
        cout << "\033[31mNúmero de portas invalidas. Por favor, tente novamente!\033[0m" << endl;
        cout << "\033[1mPortas: \033[0m";
        cin >> stringInput;
    }

    if(stringInput == "!sair")
        return;

    carro->portas = stoi(stringInput);

    cout << "\033[1mPreço: \033[0m";
    cin >> stringInput;

    if(stringInput == "!sair")
        return;

    while((!sao_digitos(stringInput) || stoi(stringInput) < 0) && stringInput != "!sair"){
        cout << "\033[31mPreço invalido. Por favor, tente novamente!\033[0m" << endl;
        cout << "\033[1mPreço: \033[0m";
        cin >> stringInput;
    }

    if(stringInput == "!sair")
        return;

    carro->preco = stoi(stringInput);
    inserir_veiculo(listaPrincipal, arvores, carro, alterou);

    cout << "\033[32mCarro adicionado com sucesso!\033[0m" << endl;
}

/**
 * Realiza a remoção da arvore binária da memória
 * @param folha o primeiro nó da arvore binária
*/
void desalocar_arv_binaria(noArv * folha) {
    if(!folha)
        return;

    if(folha->esquerda)
        desalocar_arv_binaria(folha->esquerda);
    
    if(folha->direita)
        desalocar_arv_binaria(folha->direita);

    delete folha;
}

/**
 * Realiza a remoção da árvore AVL da memória
 * @param folha a primeira folha da árvore AVL
*/
void desalocar_arv_avl(noArvAVL * folha) {
    if(!folha)
        return;
    
    if(folha->esquerda)
        desalocar_arv_avl(folha->esquerda);
    
    if(folha->direita)
        desalocar_arv_avl(folha->direita);

    delete folha;
}

/**
 * Remove a lista principal da memória
 * @param no o primeiro nó da lista principal
*/
void desalocar_lp(no_ * no) {
    if(!no)
        return;
    
    if(no->proximo)
        desalocar_lp(no->proximo);
    
    delete no->carro;
    delete no;
}

int main(void) {

    cout << "                                    _               __       _      "
            " \n                                   (_)             /_/      (_)  "
            "    \n   ___ ___  _ __   ___ ___  ___ ___ _  ___  _ __   __ _ _ __ "
            "_  __ _ \n  / __/ _ \\| '_ \\ / __/ _ \\/ __/ __| |/ _ \\| '_ \\ / "
            "_` | '__| |/ _` |\n | (_| (_) | | | | (_|  __/\\__ \\__ \\ | (_) | "
            "| | | (_| | |  | | (_| |\n  \\___\\___/|_| "
            "|_|\\___\\___||___/___/_|\\___/|_| |_|\\__,_|_|  |_|\\__,_|\n\n";

    ifstream bancoDeDados("DB_Veiculos");
    cabecalho * listaPrincipal = inicia_lista();
    arvore * arvores = inicia_arvore();

    if(listaPrincipal && arvores) 
        cout << "\033[32mAs listas e arvores foram alocadas com sucesso.\033[0m\n" << endl;
    else {
        cout << "\033[31mAs listas e arvores não foram alocadas com sucesso.\033[0m]" << endl;
        cout << "\033[31mFinalizando programa...\033[0m]" << endl;
        return EXIT_FAILURE;
    }

    cout << "\033[33;1mFiltro da árvore binária: \033[0m Carros datados antes ou de 2016\n"
            "\033[33;1mFiltro da árvore AVL: \033[0m     Carros datados depois de 2016\n";

    bool alterou = false;

    if (bancoDeDados.is_open()) {
        while (!bancoDeDados.eof()) {
            veiculo * carro = new veiculo;
            bancoDeDados >> carro->modelo;
            bancoDeDados >> carro->marca;
            bancoDeDados >> carro->tipo;
            bancoDeDados >> carro->ano;
            bancoDeDados >> carro->km;
            bancoDeDados >> carro->potencia;
            bancoDeDados >> carro->combustivel;
            bancoDeDados >> carro->cambio;
            bancoDeDados >> carro->direcao;
            bancoDeDados >> carro->cor;
            bancoDeDados >> carro->portas;
            bancoDeDados >> carro->placa;
            bancoDeDados >> carro->preco;

            inserir_veiculo(listaPrincipal, arvores, carro, alterou);
        }

    } 

    string option = menu_opcoes();

    while(toupper(option[0]) != 'S') {

        if(toupper(option[0]) ==  'A') 
            relatorio_preordem(NULL, arvores->arvore_avl);
        
        if(toupper(option[0]) == 'B')
            relatorio_preordem(arvores->arvore_binaria);
        
        if(toupper(option[0]) == 'R')
            relatorio(listaPrincipal);
        
        if(toupper(option[0]) == 'C')
            consulta(listaPrincipal, arvores, &alterou);

        if(toupper(option[0]) == 'I')
            novo_carro(listaPrincipal, arvores, &alterou);

        option = menu_opcoes();
    }

    desalocar_arv_binaria(arvores->arvore_binaria);
    desalocar_arv_avl(arvores->arvore_avl);
    desalocar_lp(listaPrincipal->primeiro);

    cout << "\033[32mTodas as estruturas foram desalocadas com sucesso!\033[0m" << endl;
    return EXIT_SUCCESS;
}