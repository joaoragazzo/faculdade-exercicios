//Nome: João Paulo Martyr Ragazzo & Luca Barbosa de Oliveira Vieira
//RA: 2022.1.08.009 & 2022.1.08.022
 
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
 
using namespace std;
 
struct veiculos {
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
 
bool atingiuMaximo(int index){
  if(index == 50){
    cout << "\033[31mMáximo de banco de dados atingido!\033[0m";
    return true;
  }
  return false;
}
//Checa se o máximo do banco de dados já foi antigido, retornando verdadeiro caso positivo.
 
void deletarVeiculo(veiculos *db[], int pos, int *index) {
  while (db[pos + 1]) {
    db[pos] = db[pos + 1];
    pos++;
  }
 
  db[pos] = db[pos + 1];
  delete (db[pos + 1]);
  db[pos + 1] = NULL;
  *index = *index - 1;
  cout << "\033[32;1mCarro removido com sucesso do nosso banco de dados!\033[0m" << endl;
} 
//Para deletar o veículo da posição X, o veículo de posição X+1 é colocado em X, em um loop até o ultimo elemento. Por fim, o ultimo elemento é
//deletado e seu ponteiro é colocado em NULL.
 
void imprimirVeiculos(veiculos *db[], int index) {
  for (int j = 0; j < index; j++) {
    cout << "Carro posição (" << j << "): ";
    cout << db[j]->modelo << " ";
    cout << db[j]->marca << " ";
    cout << db[j]->tipo << " ";
    cout << db[j]->ano << " ";
    cout << db[j]->km << " ";
    cout << db[j]->potencia << " ";
    cout << db[j]->combustivel << " ";
    cout << db[j]->cambio << " ";
    cout << db[j]->direcao << " ";
    cout << db[j]->cor << " ";
    cout << db[j]->portas << " ";
    cout << db[j]->placa << " ";
    cout << db[j]->preco << endl;
  }
} 
//Imprime todos os veículos.
 
int encontrarVeiculo(veiculos *db[], int index, string placa_) {
  for (int pos = 0; pos < index; pos++) {
    if (db[pos]->placa == placa_) {
      return pos;
    }
  }
 
  return -1;
} 
// Procura por todos os veículos de db, se achar, retorna um valor inteiro positivo. Caso contrário, retorna o valor negativo -1.
 
void inserirVeiculo(veiculos *db[], int *index) {
  cout << "Digite as informações dos veículos que deseja inserir." << endl;
  string placa;
 
  cout << "Placa: ";
  cin >> placa;
  int i = encontrarVeiculo(db, *index, placa);
 
  if (i > 0) {
    cout << "\033[31mCarro já existente no nosso banco de dados.\033[0m"
         << endl;
    return;
  }
 
  db[*index] = new veiculos;
  cout << "Modelo: ";
  cin >> db[*index]->modelo;
  cout << "Marca: ";
  cin >> db[*index]->marca;
  cout << "Tipo: ";
  cin >> db[*index]->tipo;
  cout << "Ano: ";
  cin >> db[*index]->ano;
  cout << "Km: ";
  cin >> db[*index]->km;
  cout << "Potencia: ";
  cin >> db[*index]->potencia;
  cout << "Combustível: ";
  cin >> db[*index]->combustivel;
  cout << "Câmbio: ";
  cin >> db[*index]->cambio;
  cout << "Direção: ";
  cin >> db[*index]->direcao;
  cout << "Cor: ";
  cin >> db[*index]->cor;
  cout << "Portas: ";
  cin >> db[*index]->portas;
  cout << "Preço: ";
  cin >> db[*index]->preco;
 
  db[*index]->placa = placa;
 
  *index = *index + 1;
  cout << "\033[32;1mCarro inserido com sucesso do nosso banco de dados!\033[0m" << endl;
}
//Primeiramente, procura se o veículo com placa já está presente no vetor de Struct veículo. Caso já existe, a função mostra uma mensagem de erro
//e é encerada. Caso contrário, os dados são coletados do cliente e o veículo é inserido no banco de dados. No final, a variavél index é 
//acrescentada.
 
void dadosVeiculo(veiculos *db[], int pos) {
  cout << "Dados do veículo na posição " << pos << ":" << endl;
  cout << "Modelo: " << db[pos]->modelo << endl;
  cout << "Marca: " << db[pos]->marca << endl;
  cout << "Tipo: " << db[pos]->tipo << endl;
  cout << "Ano: " << db[pos]->ano << endl;
  cout << "Km: " << db[pos]->km << endl;
  cout << "Potencia: " << db[pos]->potencia << endl;
  cout << "Combustivel: " << db[pos]->combustivel << endl;
  cout << "Cambio: " << db[pos]->cambio << endl;
  cout << "Direcao: " << db[pos]->direcao << endl;
  cout << "Cor: " << db[pos]->cor << endl;
  cout << "Portas: " << db[pos]->portas << endl;
  cout << "Placa: " << db[pos]->placa << endl;
  cout << "Preço: " << db[pos]->preco << endl;
}
//Pega todos os dados de um veiculo de posição X
 
void nearstPrices(veiculos *db[], int price, int lenght) {
  veiculos *prices[lenght];
  prices[0] = db[0];
 
  int k = 0;
 
  for (int i = 1; i < lenght; i++) {
    int j = i;
    while (j > 0 && db[i]->preco < prices[j - 1]->preco) {
      prices[j] = prices[j - 1];
      j--;
    }
    prices[j] = db[i];
  }
  //Insertion sort adaptado para inserir de forma ordenada
 
  for (int i = 0; i < lenght; i++) {
    if (k == 10)
      break;
    if (prices[i]->preco - price >= 0) {
      cout << "Carro (" << i << "): ";
      cout << prices[i]->modelo << " ";
      cout << prices[i]->marca << " ";
      cout << prices[i]->tipo << " ";
      cout << prices[i]->ano << " ";
      cout << prices[i]->km << " ";
      cout << prices[i]->potencia << " ";
      cout << prices[i]->combustivel << " ";
      cout << prices[i]->cambio << " ";
      cout << prices[i]->direcao << " ";
      cout << prices[i]->cor << " ";
      cout << prices[i]->portas << " ";
      cout << prices[i]->placa << " ";
      cout << prices[i]->preco << endl;
      k++;
    }
  }
}
//Pega todos os veículos mais proximos (superior) ao preço dado
 
void ordenaPlacas(veiculos *db[], veiculos *ordenado[], int lenght) {
  ordenado[0] = db[0];
 
  for (int i = 1; i < lenght; i++) {
    int j = i;
 
    while (j > 0 && db[i]->placa < ordenado[j - 1]->placa) {
      ordenado[j] = ordenado[j - 1];
      j--;
    }
    ordenado[j] = db[i];
  }
}
//Ordena todas as placas num segundo vetor
 
int main(void) {
 
  cout << "\033[1;35m                                    _               __       _      "
          " \n                                   (_)             /_/      (_)  "
          "    \n   ___ ___  _ __   ___ ___  ___ ___ _  ___  _ __   __ _ _ __ "
          "_  __ _ \n  / __/ _ \\| '_ \\ / __/ _ \\/ __/ __| |/ _ \\| '_ \\ / "
          "_` | '__| |/ _` |\n | (_| (_) | | | | (_|  __/\\__ \\__ \\ | (_) | "
          "| | | (_| | |  | | (_| |\n  \\___\\___/|_| "
          "|_|\\___\\___||___/___/_|\\___/|_| |_|\\__,_|_|  |_|\\__,_|\n       "
          "                                                              \n\033[0m";
 
  veiculos *db[50], *ordenado[50]; //db[50] trata-se do vetor principal, ordenado[50] se trata do vetor ordenado.
  int index = 0, pos, priceSearch; //index se trata do tamanho atual do vetor. pos se trata da posição (variavel auxiliar). priceSearch o valor a ser procurado
  string option; //option se trata da opção sendo selecionada pelo usuário
  bool ordenadoState = false; //ordenadoState diz se o usuário já ordenou e/ou se fez alguma alteração no banco de dados, para ser necessário uma nova ordenação
 
  ifstream myFile("DB_Veiculos");
 
  string placa_;
  string opts1 = "\033[1mO que você deseja fazer? \033[0m(I)nserir, (C)onsulta, (F)inalizar, (B)anco de Dados, (P)reços, (O)rdenação => ";
  string opts2 = "\033[1mO que você deseja fazer?\033[0m (D)eletar, (I)formações, (C)orrigir, (F)inalizar => ";
  string foundPlaca = "\033[1mDigite o número da placa que você deseja encontrar:\033[0m ";
  string optNotFound = "\033[31mOpção não encontada. Por favor, tente novamente.\033[0m";
 
  if (myFile.is_open()) {
    while (!myFile.eof()) {
      db[index] = new veiculos;
      myFile >> db[index]->modelo;
      myFile >> db[index]->marca;
      myFile >> db[index]->tipo;
      myFile >> db[index]->ano;
      myFile >> db[index]->km;
      myFile >> db[index]->potencia;
      myFile >> db[index]->combustivel;
      myFile >> db[index]->cambio;
      myFile >> db[index]->direcao;
      myFile >> db[index]->cor;
      myFile >> db[index]->portas;
      myFile >> db[index]->placa;
      myFile >> db[index]->preco;
      index++;
    }
 
    for (int j = index; j < 50; j++) {
      db[j] = NULL;
    }
 
    myFile.close();
 
  } else {
    cout << "\033[41mNão foi possível abrir o db\033[0m" << endl;
    return 0;
  } //Abre o arquivo
 
  while (option[0] != 'F') { //While loop do menu para o usuário
 
    cout << opts1;
    cin >> option;
 
    while (option[0] != 'I' && option[0] != 'C' && option[0] != 'F' &&
           option[0] != 'B' && option[0] != 'P' && option[0] != 'O') {
      cout << optNotFound << endl;
      cout << opts1;
      cin >> option;
    } //Força o usuário a colocar um opção existe
 
    if (option[0] == 'C') {
 
      cout << foundPlaca;
      cin >> placa_;
      pos = encontrarVeiculo(db, index, placa_);
 
      while (pos < 0) { 
        cout << "\033[31mCarro inexistente\033[0m" << endl;
        cout << foundPlaca;
        cin >> placa_;
        pos = encontrarVeiculo(db, index, placa_);
      } //Força o usuário a colocar uma placa existente
 
      cout << "O que você deseja fazer com o veículo de placa " << placa_ << "? (D)eletar, (I)nformações, (F)inalizar => ";
      cin >> option;
 
      while (option[0] != 'D' && option[0] != 'I' && option[0] != 'M' &&
             option[0] != 'C' && option[0] != 'F') {
        cout << optNotFound << endl;
        cout << opts2;
        cin >> option;
      }
 
      if (option[0] == 'D') {
        deletarVeiculo(db, pos, &index);
        ordenadoState = false;
        continue;
      }
 
      if (option[0] == 'I') {
        dadosVeiculo(db, pos);
        continue;
      }
    }
 
    if (option[0] == 'I') {
      if(atingiuMaximo(index)) 
        continue;
      inserirVeiculo(db, &index);
      ordenadoState = false;
    }
 
    if (option[0] == 'B') {
      imprimirVeiculos(db, index);
      continue;
    }
 
    if (option[0] == 'P') {
      cout << "Por favor, digite o valor que você deseja receber os 10 valores mais proximos => ";
      cin >> priceSearch;
 
      nearstPrices(db, priceSearch, index);
    }
 
    if (option[0] == 'O') {
      if (!ordenadoState) {
        ordenaPlacas(db, ordenado, index);
        cout << index << endl;
        ordenadoState = true;
      }
      imprimirVeiculos(ordenado, index);
    }
  }
 
  ofstream myFile_("DB_Veiculos");
 
  if (myFile_.is_open()) {
    myFile_   << db[0]->modelo << " " << db[0]->marca << " " << db[0]->tipo << " " 
              << db[0]->ano << " " << db[0]->km << " " << db[0]->potencia << " " 
              << db[0]->combustivel << " " << db[0]->tipo << " "
              << db[0]->direcao << " " << db[0]->cor << " " << db[0]->portas << " " 
              << db[0]->placa << " " << db[0]->preco;
    for (int i = 1; i < index; i++) {
      myFile_ <<"\n" << db[i]->modelo << " " << db[i]->marca << " " << db[i]->tipo
              << " " << db[i]->ano << " " << db[i]->km << " " << db[i]->potencia
              << " " << db[i]->combustivel << " " << db[i]->tipo << " "
              << db[i]->direcao << " " << db[i]->cor << " " << db[i]->portas
              << " " << db[i]->placa << " " << db[i]->preco;
    }
 
    myFile_.close();
 
  } else {
    cout << "\033[41mNão foi possível abrir o db\033[0m" << endl;
    return 0;
  }
 
 
  cout << "Saindo do algoritimo..." << endl;
  return (EXIT_SUCCESS);
}