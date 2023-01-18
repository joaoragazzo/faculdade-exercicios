/*
*Para compilar no VSCode, utilizando-se de headers, eles precisam estar likados através do mesmo nome. Como por exemplo, sum.cpp e 
*sum.h. Além disso, o segundo arquivo .cpp precisa estar linkado com o main.cpp na hora da compilação. Para isso, utilizamos:
* g++ -o main.exe main.cpp sum.cpp
* e, depois, para executar o arquivo, utilizamos:
* ./main.exe
*/

/**
 * Para compilar automaticamente no VSCode, é necessário mudar as opções do compilador em .vscode/tasks.json e colocar o 
 * nome dos "headers" nos paramentros de compilaçã
 * 
 */


#include <iostream>
#include "sum.h"

using namespace std;

int main(void) {
    cout << sum(10, 20) << endl;
}