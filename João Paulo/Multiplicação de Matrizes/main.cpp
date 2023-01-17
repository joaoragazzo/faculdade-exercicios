#include <iostream>

using namespace std;

int main(void){
    int A[3][3] = {
        {4, 5, 2},
        {5, 4, 1},
        {4, 9, 0}
    };

    int B[3][3] = {
        {2, 3, 4},
        {4, 7, 8},
        {3, 8, 9}
    };

    int C[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    int *m = &A[0][0]; // k
    int *n = &B[0][0]; // j
    int *o = &C[0][0];

    
    for(int i = 0; o <= &C[2][2]; o++, i++){
        for(int *k = m + 3*(i/3), *j = n + (i%3), c = 1; c/4 == 0; k++, j += 3, c++){
            *o = *o + ((*k) * (*j));
        }
    }
    
   
    for(int i = 0; i < 3; i++){
        for(int j = 0; j <  3; j++){
            cout << C[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}