/*  Universidade Federal de Alfenas (UNIFAL) - 2022
*   Discentes: Joao Paulo Martyr Ragazzo (RA: 2022.1.08.009)
*              Matheus Martins dos Santos (RA: 2022.1.08.025)
*              Luca Barbosa de Oliveira Vieira (RA: 2022.1.08.022)
*
*   Docente: Paulo Alexandre Bressan - Algoritimo e Estrutura de Dados II
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
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
 * Estrutura do nó para a lista encadeada 
 * carro -> Ponteiro para a struct de carro
 * prox  -> Ponteiro para o próximo nó 
*/
typedef struct no_ {
    veiculo * carro;
    struct no_ * prox;
} no;

/**
 * Cabeçalho padrao para a lista encadeada.
 * tamanho -> O tamanho atual da lista.
 * lista   -> Um ponteiro do tipo nó para o início da lista.
 * ultimo  -> Um ponteiro para o último nó da lista. 
*/
typedef struct {
    int tamanho;
    struct no_ * lista;
    struct no_ * ultimo;
} tLista;

/**
 * Realiza uma alocaçao de espaço para começar a receber os nós.
 * Guarda o tamanho lista e o primeiro nó em questao.
 * @return  A lista vazia.
*/
tLista * inicia_lista(int * i){
    tLista * tmp = new tLista;
    tmp->lista = NULL;
    tmp->ultimo = NULL;
    tmp->tamanho = 0;
    *i = *i + 1;
    cout << "\r\033[32mA lista foi alocada com sucesso. (" << *i << ")\033[0m";
    return tmp;
}

/**
 * Percore a lista encadeada em busca de uma placa em questao
 * @param lista A lista a ser percorrida
 * @param placa A placa a ser buscada
 * @return o nó caso o veículo seja encontrado.
 * @return NULL caso o carro nao seja encontrado.
*/
no * busca(tLista * lista, string placa){
    for(no * atual = lista->lista; atual != NULL; atual = atual->prox){
        if(atual->carro->placa == placa)
            return atual;
    }

    return NULL;
}

/**
 * Realiza uma inserçao de um nó no final da lista.
 * @param lista A lista onde sera realizada a inserçao.
 * @param carro O ponteiro do carro a ser inserido na lista em questao.
 * @return 1 caso seja possível realizar a inserçao
*/
int inserir(tLista * lista, veiculo * carro){
    ///Checa, atraves da funçao de busca, se ja existe um veículo com a mesma placa na lista encadeada.
    if(busca(lista, carro->placa)) {
        cout << "\033[31mEssa placa ja foi encontrada em nossa lista. Veículo nao inserido.\033[0m" << endl;
        return 0;
    }

    no * ultimo = lista->ultimo;
    no * novo = new no;
    novo->prox = NULL;
    novo->carro = carro;

    if(ultimo != NULL)
        ultimo->prox = novo;
    else 
        lista->lista = novo;

    lista->ultimo = novo;
    lista->tamanho++;
    return 1;
}

/**
 * Insere um veículo na pilha
 * @return 1 caso foi possível realizar a inserçao
 * @param pilha A pilha que sera efetuada a inserçao
 * @param carro Um ponteiro para o carro que sera adicionado na pilha
*/
int pilha_in(tLista * pilha, veiculo * carro){
    no *atual = pilha->lista;
    no *novo = new no;
    novo->carro = carro;
    
    pilha->lista = novo;
    novo->prox = atual;
    pilha->tamanho++;
    return 1;
}

/**
 * Remove um veículo da pilha
 * @return 1 caso foi possível realizar a remoçao, 0 caso nao seja possível realizar a remoçao
 * @param pilha A pilha a qual sera realizada a remoçao
*/
int pilha_out(tLista * pilha){
    if (pilha->lista == NULL) 
        return 0;

    no *remover = pilha->lista;
    
    if(remover->prox)
        pilha->lista = remover->prox;
    else 
        pilha->lista = NULL;
    
    pilha->tamanho--;
    delete remover;

}

/**
 * Insere um veículo na fila 
 * @param fila A fila onde sera efetuada a inserçao do veículo
 * @param carro Um ponteiro para o carro que sera aicionado a fila
 * @return 1 Caso seja possível realizar a inserçao. 
*/
int fila_in(tLista * fila, veiculo * carro){
    no * ultimo = fila->ultimo;
   
    no * novo = new no;
    novo->prox = NULL;
    novo->carro = carro;

    if(ultimo != NULL)
        ultimo->prox = novo;
    else 
        fila->lista = novo;

    fila->ultimo = novo;
    fila->tamanho++;
    return 1;
}

/**
 * Remove um veículo da fila
 * @param fila A fila onde sera realizada a remoçao.
 * @return 1 Caso tenha sido possível realizar a remoçao. 0 Caso nao tenha sido possível realizar a remoçao.
*/
int fila_out(tLista * fila){
    if (fila->lista == NULL) 
        return 0;

    no * remover = fila->lista;

    if(remover->prox)
        fila->lista = remover->prox;
    else {
        fila->lista = NULL;
        fila->ultimo = NULL;
    }
    
    delete remover;
    fila->tamanho--;
    return 1;
}

/**
 * Uma formulazinha para determinar as cores que irão sair no console
 * @param i O número da linha
 * @param j O número da coluna
*/
void verde_amarelo(int * i, int j, bool possivel) {

    if(!possivel){
        return;
    }

    *i = *i + 1;
    if(*i > 4 && *i < 10 && *i - 1.5*abs(j) >= 1 && *i + 1.5*abs(j) <= 13){
        if(j == -1 && *i <= 7){
            cout << "\033[0;1m";
            return;
        }
        if(j == 0 && *i > 7){
            cout << "\033[0;1m";
            return;
        }     
        cout << "\033[34m";
        return;
    }
    
    if (*i - abs(j) >= 1 && *i + abs(j) <= 13){
        cout << "\033[033m";
        return;
    }
        
    cout << "\033[1;32m";
    return;    
}

/**
 * Imprime, na mesma ordem de inserçao, os veículos dentro da lista encadeada.
 * @param lista A lista a ser impressa.
*/
void imprimir(tLista * lista){

    int j = -lista->tamanho/2;

    bool possivel = true;

    if(abs(j) < 7) {
        possivel = false;
    }

    no * atual = lista->lista;
    cout << "\033[1;32m";
    cout << "+---------+-------------------+------------+---------+------+--------+-----+--------+------------+------------+----------+----+--------+" << endl;
    cout << "|  PLACA  |      MODELO       |    MARCA   |   TIPO  |  ANO |   KM   | POT |  COMB  |   CAMBIO   |   DIREÇAO  |    COR   | PT | PREÇO  |" << endl;
    cout << "+---------+-------------------+------------+---------+------+--------+-----+--------+------------+------------+----------+----+--------+" << endl;
    for(; atual !=  NULL; atual = atual->prox, j++) {
        int i = 0;

        verde_amarelo(&i, j, possivel);
        veiculo * carro = atual->carro;
        cout << "| " << setw(6) << carro->placa;
        verde_amarelo(&i, j, possivel);
        cout << " | " << setw(17) << carro->modelo;
        verde_amarelo(&i, j, possivel);
        cout << " | " << setw(10) << carro->marca;
        verde_amarelo(&i, j, possivel);
        cout << " | " << setw(7) << carro->tipo;
        verde_amarelo(&i, j, possivel);
        cout << " | " << setw(4) << carro->ano;
        verde_amarelo(&i, j, possivel);
        cout << " | " << setw(6) << carro->km;
        verde_amarelo(&i, j, possivel);
        cout << " | " << setw(3) << carro->potencia;
        verde_amarelo(&i, j, possivel);

        if(carro->combustivel == "Gasolina") {
            cout << " | " << setw(6) << "Gaso.";
        } else {
            cout << " | " << setw(6) << carro->combustivel;
        }

        verde_amarelo(&i, j, possivel);
        cout << " | " << setw(10) << carro->cambio;
        verde_amarelo(&i, j, possivel);
        cout << " | " << setw(10) << carro->direcao;
        verde_amarelo(&i, j, possivel);
        cout << " | " << setw(8) << carro->cor;
        verde_amarelo(&i, j, possivel);
        cout << " | " << setw(2) << carro->portas;
        verde_amarelo(&i, j, possivel);
        cout << " | " << setw(6) << carro->preco << " |" << endl;
        verde_amarelo(&i, j, possivel);
    }
    cout << "+---------+-------------------+------------+---------+------+--------+-----+--------+------------+------------+----------+----+--------+\033[0m" << endl;
}

/**
 * Funçao para remover um carro com determinada placa do banco de dados
 * @param lista A lista ao qual o veículo sera removido
 * @param placa A placa que sera buscada na lista para ser removida
 * @return 1 caso seja possível realizar a remoçao/0 caso nao seja possível realizar a remoçao
*/
int remover(tLista * lista, string placa){

    if(lista->tamanho == 0) {
        cout << "\033[31mImpossível remover veículos. A lista se encontra atualmente vazia.\033[0m" << endl;
        return 0;
    }

    no * remover = lista->lista;
    no * anterior;

    if(remover->carro->placa == placa){
        lista->lista = remover->prox;
        return 1;
    }

    /// Percorre todos os veículos da lista em busca do veículo com a placa @param placa. 
    for(; remover && remover->carro->placa != placa; anterior = remover, remover = remover->prox); 

    /// Caso remover == NULL, entao nao foi encontrado o veículo com essa placa na lista. 
    if(!remover){
        cout << "\033[31mNao foi possível encontrar o veículo com a placa inserida.\033[0m" << endl;
        return 0;
    }

    /// Caso seja o ultimo elemento da lista, ou seja, remover->prox == NULL, entao o ponteiro lista->ultimo e movido para o anterior
    if(!remover->prox)
        lista->ultimo = anterior;
        
    anterior->prox = remover->prox;
    lista->tamanho--;
    
    delete remover->carro;
    delete remover;
    return 1;
}

/**
 * Desaloca a estruta de lista juntamente com as structs
 * @param lista A lista que sera desalocada
 * @return 1 caso a desalocaçao tenha sido efetuada com sucesso
*/
int desalocar(tLista * lista, int * i){

    if(lista->lista) {
        no * prox = lista->lista;

        while(prox != NULL){
            no * remover = prox;
            prox = prox->prox;
            if(i == 0){
                delete remover->carro;
            }
            delete remover;
        }
    }

    *i = *i + 1;
    cout << "\r\033[32mLista desalocada com sucesso! (" << *i << ")\033[0m";
    delete lista;
    return 1;
}

/**
 * Ordena a uma lista de veículos pela placa em uma segunda lista (ja anteriormente alocada).
 * @param lista A lista desordenada  que sera ordenada
 * @param ordenado A lista onde sera armazenado a lista ja ordenada
 * @return 1 Caso tenha sido possível realizar a ordenaçao. 0 Caso nao tenha sido possível realizar a ordenadaçao.
*/
int ordenar_lista(tLista * lista, tLista * ordenado){
    
    if (lista->tamanho == 0){
        cout << "\033[31mA lista esta vazia. Impossível realizar a ordenaçao.\033[0m" << endl;
        return 0;
    }

    no * cabeca = new no;
    cabeca->carro = lista->lista->carro;
    cabeca->prox = NULL;

    for(no * atual = lista->lista->prox; atual != NULL; atual = atual->prox){

        no * anterior = NULL;
        no * aux;      
        no * tmp = new no;

        for(aux = cabeca; aux != NULL && aux->carro->placa < atual->carro->placa; anterior = aux, aux = aux->prox);

        tmp->carro = atual->carro;
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

    ordenado->tamanho = lista->tamanho;
    ordenado->lista = cabeca;
    return 1;
}

/**
 * Mostra o menu de opções principais para o usuario
 * @return A string com a opçao escolhida pelo usuario
*/
string menu_opcoes(void) {
    string option;
    cout << "\n\033[1mO que você deseja fazer? \033[0m(I)nserir, (C)onsulta, (R)elatório, (O)rdenaçao, (P)ilha, (F)ila, (S)air => ";
    cin >> option;

    while(toupper(option[0]) != 'I' && toupper(option[0]) != 'C' && toupper(option[0]) != 'R' && toupper(option[0]) != 'O' && 
          toupper(option[0]) != 'P' && toupper(option[0]) != 'F' && toupper(option[0]) != 'S') {
            cout << "\033[31mOpçao invalida. Por favor, tente novamente.\033[0m" << endl;
            cout << "\033[1mO que você deseja fazer? \033[0m(I)nserir, (C)onsulta, (R)elatório, (O)rdenaçao, (P)ilha, (F)ila, (S)air => ";
            cin >> option;
          }
    
    return option;
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

int main(void){

    cout << "\033[1;33m                                    _               __       _      "
            " \n\033[1;32m                                   (_)             /_/      (_)  "
            "    \n\033[1;33m   ___ ___  _ __   ___ ___  ___ ___ _  ___  _ __   __ _ _ __ "
            "_  __ _ \n\033[1;32m  / __/ _ \\| '_ \\ / __/ _ \\/ __/ __| |/ _ \\| '_ \\ / "
            "_` | '__| |/ _` |\n\033[1;33m | (_| (_) | | | | (_|  __/\\__ \\__ \\ | (_) | "
            "| | | (_| | |  | | (_| |\n\033[1;32m  \\___\\___/|_| "
            "|_|\\___\\___||___/___/_|\\___/|_| |_|\\__,_|_|  |_|\\__,_|\n\033[0m";

        cout << setw(75);
        cout << "\033[1;33mBRASIL \033[1;32mRUMO \033[1;33mAO \033[1;32mHEXA" << endl;


    ifstream myFile("DB_Veiculos"); /* O arquivo do Banco de Dados */
    int i = 0; /* Contador genérico */
    tLista * ordenado = inicia_lista(&i); /* A lista encadeada ordenada onde ficara os veículos ordenados pela placa*/
    tLista * pilha = inicia_lista(&i); /* A lista encadeada em formato de pilha onde ficara os veículos */
    tLista * fila = inicia_lista(&i); /* A lista encadeada em formato de fila onde ficara os veículos  */
    tLista * db = inicia_lista(&i); /* A lista encadeada principal onde ficara alocado todos os veículos em ordem de entrada */

    bool estaOrdenado = false; /* Diz sobre o estado de ordenaçao da lista ordenada. Nao ordenadar uma lista ja ordenada. */

    if(myFile.is_open()) {
        while(!myFile.eof()) {
            veiculo * carro = new veiculo;
            myFile >> carro->modelo;
            myFile >> carro->marca;
            myFile >> carro->tipo;
            myFile >> carro->ano;
            myFile >> carro->km;
            myFile >> carro->potencia;
            myFile >> carro->combustivel;
            myFile >> carro->cambio;
            myFile >> carro->direcao;
            myFile >> carro->cor;
            myFile >> carro->portas;
            myFile >> carro->placa;
            myFile >> carro->preco;

            if(carro->direcao == "Hidraulica") 
                pilha_in(pilha, carro);
            
            if(carro->direcao == "Mecânica") 
                pilha_out(pilha);         

            if(carro->cambio == "Automatico") 
                fila_in(fila, carro);         

            if(carro->cambio == "Manual") 
                fila_out(fila);
            

            inserir(db, carro);
        }
        myFile.close();
    } else {
        cout << "\033[31mNao foi possível abrir o arquivo do banco de dados.\033[0m" << endl;
        return EXIT_FAILURE;
    }

    string option = menu_opcoes();

    while(toupper(option[0]) != 'S'){
        
        if(toupper(option[0]) == 'I') {
            string stringInput;
            veiculo * carro = new veiculo;

            cout << "Por favor, forneça as seguintes informações sobre o veículo que deseja inserir: " << endl;
            cout << "\033[1;33mImportante: \033[0mDigite \033[1m\"!sair\"\033[0m a qualquer momento para sair." << endl;
            cout << "\033[1mPlaca (AAA0000): \033[0m";
            cin >> stringInput;

            if(stringInput == "!sair"){
                option = menu_opcoes();
                continue;
            }

            bool existe = busca(db, stringInput);
            bool valido = e_placa(stringInput);

            while((existe || !valido) && stringInput != "!sair"){
                if(existe){
                    cout << "\033[31mEsse veículo ja existe em nosso Banco de Dados. Por favor, tente novamente!\033[0m" << endl;
                } else if (!valido){
                    cout << "\033[31mPlaca não possui o formato certo. Por favor, tente novamente!\033[0m" << endl;
                }

                cout << "\033[1mPlaca (AAA0000): \033[0m";
                cin >> stringInput;
                existe = busca(db, stringInput);
                valido = e_placa(stringInput);
            }

            if(stringInput == "!sair"){
                option = menu_opcoes();
                continue;
            }

            for(int i = 0; i <= 2; i++){
                stringInput[i] = toupper(stringInput[i]);
            }

            carro->placa = stringInput;

            cout << "\033[1mModelo: \033[0m";
            cin >> stringInput;

            if(stringInput == "!sair"){
                option = menu_opcoes();
                continue;
            }

            carro->modelo = all_upper(stringInput);

            cout << "\033[1mMarca: \033[0m";
            cin >> stringInput;

            if(stringInput == "!sair"){
                option = menu_opcoes();
                continue;
            }

            while(!sao_chars(stringInput) && stringInput != "!sair"){
                cout << "\033[31mMarca inválido. Por favor, use apenas letras ou '-'.\033[0m" << endl;
                cout << "\033[1mMarca: \033[0m";
                cin >> stringInput;
            }

            if(stringInput == "!sair"){
                option = menu_opcoes();
                continue;
            }

            carro->marca = all_upper(stringInput);

            cout << "\033[1mTipo: \033[0m";
            cin >> stringInput;

            while(!sao_chars(stringInput) && stringInput != "!sair"){
                cout << "\033[31mTipo inválido. Por favor, utilize apenas letras ou '-'.\033[0m" << endl;
                cout << "\033[1mTipo: \033[0m";
                cin >> stringInput;
            }

            if(stringInput == "!sair"){
                option = menu_opcoes();
                continue;
            }

            carro->tipo = first_upper(stringInput);

            cout << "\033[1mAno: \033[0m";
            cin >> stringInput;

            if(stringInput == "!sair"){
                option = menu_opcoes();
                continue;
            }

            while((!sao_digitos(stringInput) || stoi(stringInput) < 1900 || stoi(stringInput) > ano_atual() + 2) && stringInput != "!sair"){
                cout << "\033[31mAno invalido. Por favor, tente novamente!\033[0m" << endl;
                cout << "\033[1mAno: \033[0m";
                cin >> stringInput;
            }
            
            if(stringInput == "!sair"){
                option = menu_opcoes();
                continue;
            }
            
            carro->ano = stoi(stringInput);

            cout << "\033[1mKm: \033[0m";
            cin >> stringInput;

            if(stringInput == "!sair"){
                option = menu_opcoes();
                continue;
            }

            while((!sao_digitos(stringInput) || stoi(stringInput) < 0) && stringInput != "!sair"){
                cout << "\033[31mKilometragem invalida. Por favor, tente novamente!\033[0m" << endl;
                cout << "\033[1mKm: \033[0m";
                cin >> stringInput;
            }
            
            if(stringInput == "!sair"){
                option = menu_opcoes();
                continue;
            }
            
            carro->km = stoi(stringInput);

            cout << "\033[1mPotência: \033[0m";
            cin >> stringInput;

            while((!sao_digitos(stringInput) || stof(stringInput) < 1.0) && stringInput != "!sair"){
                cout << "\033[31mPotência invalida. Por favor, tente novamente!\033[0m" << endl;
                cout << "\033[1mPotência: \033[0m";
                cin >> stringInput;
            }

            if(stringInput == "!sair"){
                option = menu_opcoes();
                continue;
            }

            carro->potencia = stof(stringInput);


            cout << "\033[1mCombustível:\033[0m (D)iesel, (G)asolina, (F)lex => ";
            cin >> stringInput;

            if(stringInput == "!sair"){
                option = menu_opcoes();
                continue;
            }

            while(toupper(stringInput[0]) != 'F' && toupper(stringInput[0]) != 'D' && toupper(stringInput[0]) != 'G' && stringInput != "!sair"){
                cout << "\033[31mCombustível invalido. Por favor, tente novamente!\033[0m" << endl;
                cout << "\033[1mCombustível:\033[0m (D)iesel, (G)asolina, (F)lex => ";
                cin >> stringInput;
            }

            if(stringInput == "!sair"){
                option = menu_opcoes();
                continue;
            }

            switch (stringInput[0]) {
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

            if(stringInput == "!sair"){
                option = menu_opcoes();
                continue;
            }

            while(toupper(stringInput[0]) != 'A' && toupper(stringInput[0]) != 'M' && stringInput != "!sair"){
                cout << "\033[31mCâmbio invalido. Por favor, tente novamente!\033[0m" << endl;
                cout << "\033[1mCâmbio:\033[0m (A)utomatico, (M)anual => ";
                cin >> stringInput;
            }

            if(stringInput == "!sair"){
                option = menu_opcoes();
                continue;
            }

            switch (stringInput[0]) {
                case 'A':
                    carro->cambio = "Automatico";
                    break;
                
                case 'M':
                    carro->cambio = "Manual";
                    break;    
            }

            cout << "\033[1mDireçao: \033[0m (H)idraulica, (M)ecânica, (E)letrica => ";
            cin >> stringInput;

            if(stringInput == "!sair"){
                option = menu_opcoes();
                continue;
            }

            while(toupper(stringInput[0]) != 'H' && toupper(stringInput[0]) != 'M' && toupper(stringInput[0]) != 'E' && stringInput != "sair"){
                cout << "\033[31mDireçao invalida. Por favor, tente novamente!\033[0m" << endl;
                cout << "\033[1mDireçao: \033[0m (H)idraulica, (M)ecânica, (E)letrica => ";
                cin >> stringInput;
            }

            if(stringInput == "!sair"){
                option = menu_opcoes();
                continue;
            }

            switch (stringInput[0]) {
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

            if(stringInput == "!sair"){
                option = menu_opcoes();
                continue;
            }

            while(!sao_chars(stringInput) && stringInput != "!sair"){
                cout << "\033[31mCor inválida. Por favor, digite apenas letras.\033[0m" << endl;
                cout << "\033[1mCor: \033[0m";
                cin >> stringInput;
            }

            if(stringInput == "!sair"){
                option = menu_opcoes();
                continue;
            }

            carro->cor = first_upper(stringInput);

            cout << "\033[1mPortas: \033[0m";
            cin >> stringInput;

            if(stringInput == "!sair"){
                option = menu_opcoes();
                continue;
            }

            while((!sao_digitos(stringInput) || stoi(stringInput) <= 0) && stringInput != "!sair" ){
                cout << "\033[31mNúmero de portas invalidas. Por favor, tente novamente!\033[0m" << endl;
                cout << "\033[1mPortas: \033[0m";
                cin >> stringInput;
            }

            if(stringInput == "!sair"){
                option = menu_opcoes();
                continue;
            }

            carro->portas = stoi(stringInput);

            cout << "\033[1mPreço: \033[0m";
            cin >> stringInput;

            if(stringInput == "!sair"){
                option = menu_opcoes();
                continue;
            }

            while((!sao_digitos(stringInput) || stoi(stringInput) < 0) && stringInput != "!sair"){
                cout << "\033[31mPreço invalido. Por favor, tente novamente!\033[0m" << endl;
                cout << "\033[1mPreço: \033[0m";
                cin >> stringInput;
            }

            if(stringInput == "!sair"){
                option = menu_opcoes();
                continue;
            }

            carro->preco = stoi(stringInput);
            inserir(db, carro);

            if(carro->direcao == "Hidraulica") 
                pilha_in(pilha, carro);
            
            if(carro->direcao == "Mecanica") 
                pilha_out(pilha);         

            if(carro->cambio == "Automatico") 
                fila_in(fila, carro);         

            if(carro->cambio == "Manual") 
                fila_out(fila);

            estaOrdenado = false;
            cout << "\033[32mCarro adicionado com sucesso!\033[0m" << endl;
        }

        if(toupper(option[0]) == 'C'){
            string placa;

            cout << "\033[1mDigite a placa que você deseja consultar =>\033[0m ";
            cin >> placa; 

            no * carro = busca(db, placa);

            if(carro) {
                cout << "\033[32mVeículo encontrado com sucesso no banco de dados!\033[0m" << endl;
                cout << "\033[1mO que você deseja fazer com o veículo encontrado?\033[0m (I)nformações, (E)Excluir, (V)oltar => ";
                cin >> option;
                
                while(toupper(option[0]) != 'I' && toupper(option[0]) != 'E' && toupper(option[0]) != 'V'){
                    cout << "\033[31mOpçao invalida. Por favor, tente novamente.\033[0m" << endl;
                    cout << "\033[1mO que você deseja fazer com o veículo encontrado?\033[0m (I)nformações, (R)emover, (V)oltar =>";
                    cin >> option;
                }

                if(toupper(option[0]) == 'I'){
                    cout << "\033[1;32m+---------+-------------------+------------+---------+------+--------+-----+----------+------------+------------+----------+----+--------+" << endl;
                    cout << "|  PLACA  |      MODELO       |    MARCA   |   TIPO  | ANO  |   KM   | POT |   COMB   |   CAMBIO   |   DIREÇAO  |    COR   | PT | PREÇO  |" << endl;
                    cout << "+---------+-------------------+------------+---------+------+--------+-----+----------+------------+------------+----------+----+--------+" << endl;
                    cout << "| " << setw(6) << carro->carro->placa;
                    cout << " | " << setw(17) << carro->carro->modelo;
                    cout << " | " << setw(10) << carro->carro->marca;
                    cout << " | " << setw(7) << carro->carro->tipo;
                    cout << " | " << setw(4) << carro->carro->ano;
                    cout << " | " << setw(6) << carro->carro->km;
                    cout << " | " << setw(3) << carro->carro->potencia;
                    cout << " | " << setw(8) << carro->carro->combustivel;
                    cout << " | " << setw(10) << carro->carro->cambio;
                    cout << " | " << setw(10) << carro->carro->direcao;
                    cout << " | " << setw(8) << carro->carro->cor;
                    cout << " | " << setw(2) << carro->carro->portas;
                    cout << " | " << setw(6) << carro->carro->preco << " |" << endl;
                    cout << "+---------+-------------------+------------+---------+------+--------+-----+----------+------------+------------+----------+----+--------+\033[0m" << endl;
                
                }


                if(toupper(option[0]) == 'E'){
                    if(remover(db, placa)){
                        cout << "\033[32mVeículo apagado do Bando de Dados com sucesso!\033[0m" << endl;
                        estaOrdenado = false;
                    } else {
                        cout << "\033[31mAlguma coisa deu errado. Por favor, tente novamente.\033[0m" << endl;
                    }
                }
                
            } else {
                cout << "\033[31mO veículo nao foi encontrado no nosso Banco de Dados.\033[0m" << endl;
            }
        }

        if(toupper(option[0]) == 'R')
            imprimir(db);

        if(toupper(option[0]) == 'O'){
            if(!estaOrdenado) {
                ordenar_lista(db, ordenado);
            }
            imprimir(ordenado);
        }

        if(toupper(option[0]) == 'P') {
            imprimir(pilha);
        } 

        if(toupper(option[0]) == 'F') {           
            imprimir(fila);
        }

        option = menu_opcoes();
    }

    i = 0;

    desalocar(db, &i);
    desalocar(pilha, &i);
    desalocar(fila, &i);
    desalocar(ordenado, &i);

    cout << "\n\033[1;33mFinalizando...\033[0m" << endl;
    return EXIT_SUCCESS;

}