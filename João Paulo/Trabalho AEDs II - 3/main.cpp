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
    cout << "\033[32mA lista foi alocada com sucesso.\033[0m" << endl;
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
int remover_veiculo(cabecalho * listaPrincipal, arvore ** avl, arvore ** binaria, string placa) {
    no_ * atual = listaPrincipal->primeiro;
    no_ * anterior = NULL;

    if (!atual) {
        cout << "A lista está vazia. Impossível de realizar a remoção." << endl;
        return 0;
    }

    while (atual && atual->carro->placa != placa) {
        anterior = atual;
        atual = atual->proximo;
    }

    if(!atual) {
        cout << "O carro com essa placa não foi encontrado no nosso banco de dados. Por favor, certifique-se de que a placa foi escrita corretamente. " << endl;
        return 0;
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
            noArv * novoNo = new noArv;
            folha->esquerda = novoNo;
            novoNo->esquerda = NULL;
            novoNo->direita = NULL;
            novoNo->placa = no->carro->placa;
            novoNo->no = no;
            return 1;
        }

        return inserir_arv_binaria(folha->esquerda, no);
    }

    if (folha->placa < no->carro->placa) {
        if (!folha->direita) {
            noArv * novoNo = new noArv;
            folha->direita = novoNo;
            novoNo->esquerda = NULL;
            novoNo->direita = NULL;
            novoNo->placa = no->carro->placa;
            novoNo->no = no;
            return 1;
        }

        return inserir_arv_binaria(folha->direita, no);
    }
}

/**
 * Insere um veículo na listaPrincipal, na árvore binária AVL e na arvore binária de busca simultâneamente
 * @param listaPrincipal a lista principal onde será inserido o novo veículo
 * @param avl a árvore binária AVL onde será inserido o novo veículo
 * @param binaria a árvore binária de busca onde será inserido o novo véiculo
 * @param carro o novo carro que será inserido nas estruturas
*/
int inserir_veiculo(cabecalho * listaPrincipal, arvore * avl, arvore * arvores, veiculo * carro) {

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

    if (1 /* Condição de filtro a ser implementada para arvore binária*/) {
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

    if(1 /* Condição de filtro a ser implementado para árvore binária */) {
        if(!arvores->arvore_avl) {
            noArvAVL * novaFolha = new noArvAVL;
            arvores->arvore_avl = novaFolha;
            novaFolha->bal = 0;
            novaFolha->direita = NULL;
            novaFolha->esquerda = NULL;
            novaFolha->placa = carro->placa;
            novaFolha->no = novoNo;
        } else {
            
        }
    }




}

/**
 * Exibe uma árvore binária
 * @param folha A primeira folha da árvore binária a qual deseja ser inserida
*/
void exibirArvore(noArv * folha) {
    if (!folha) {
        return;
    }
    cout << "\"" << folha->placa << "\"";
    cout << "(";
    exibirArvore(folha->esquerda);
    exibirArvore(folha->direita);
    cout << ")";
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
void relatorio_preordem_carros(noArv * cabeca) {
    
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
        relatorio_preordem_carros(cabeca->esquerda);

    if(cabeca->direita) 
        relatorio_preordem_carros(cabeca->direita);

}

/**
 * Imprime o relatório de uma árvore binária em pré-ordem com o cabeçalho
 * @param arvore_ o cabeçalho da árvore em que será impressa em pré-ordem
*/
void relatorio_preordem(arvore * arvore_) {
    cout << "+---------+-------------------+------------+---------+------+--------+-----+--------+------------+------------+----------+----+--------+" << endl;
    cout << "|  PLACA  |      MODELO       |    MARCA   |   TIPO  |  ANO |   KM   | POT |  COMB  |   CAMBIO   |   DIREÇAO  |    COR   | PT | PREÇO  |" << endl;
    cout << "+---------+-------------------+------------+---------+------+--------+-----+--------+------------+------------+----------+----+--------+" << endl;

    relatorio_preordem_carros(arvore_->arvore_binaria);

    cout << "+---------+-------------------+------------+---------+------+--------+-----+--------+------------+------------+----------+----+--------+\033[0m" << endl;

}

int main(void) {

    cout << "                                    _               __       _      "
            " \n                                   (_)             /_/      (_)  "
            "    \n   ___ ___  _ __   ___ ___  ___ ___ _  ___  _ __   __ _ _ __ "
            "_  __ _ \n  / __/ _ \\| '_ \\ / __/ _ \\/ __/ __| |/ _ \\| '_ \\ / "
            "_` | '__| |/ _` |\n | (_| (_) | | | | (_|  __/\\__ \\__ \\ | (_) | "
            "| | | (_| | |  | | (_| |\n  \\___\\___/|_| "
            "|_|\\___\\___||___/___/_|\\___/|_| |_|\\__,_|_|  |_|\\__,_|\n";

    ifstream bancoDeDados("DB_Veiculos");
    cabecalho * listaPrincipal = inicia_lista();
    arvore * avl = inicia_arvore();
    arvore * arvoreBinaria = inicia_arvore();

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

            inserir_veiculo(listaPrincipal, avl, arvoreBinaria, carro);
        }

    } 

    relatorio_preordem(arvoreBinaria);

}