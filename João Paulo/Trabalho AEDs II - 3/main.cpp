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

struct no_ {
    veiculo * carro;
    no_ * proximo;
};

struct noArv {
    string placa;
    no_ * no;
    noArv * esquerda;
    noArv * direita; 
};

struct arvore {
    noArv * cabeca;
};

struct cabecalho {
    no_ * primeiro;
    no_ * ultimo;
};

cabecalho * inicia_lista(void) {
    cabecalho * tmp = new cabecalho;
    tmp->primeiro = NULL;
    tmp->ultimo = NULL;
    cout << "\033[32mA lista foi alocada com sucesso.\033[0m" << endl;
    return tmp;
}

int remover_veiculo(cabecalho * listaPrincipal, arvore * AVL, arvore * binaria, string placa) {
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

int relatorio(cabecalho * listaPrincipal) {
    no_ * atual = listaPrincipal->primeiro;

    if (!atual) {
        cout << "A lista principal está vazia. Impossível imprimir o relatório." << endl;
        return 0;
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
    arvore * AVL;

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

            no_ * tmp = new no_;
            tmp->carro = carro;
            tmp->proximo = NULL;

            if (!listaPrincipal->primeiro) {
                listaPrincipal->primeiro = tmp;
                listaPrincipal->ultimo = tmp;
            } else {
                listaPrincipal->ultimo->proximo = tmp;
                listaPrincipal->ultimo = tmp;
            }
        }

    }


    remover_veiculo(listaPrincipal, NULL, NULL, "MAN7774");
    relatorio(listaPrincipal);

}