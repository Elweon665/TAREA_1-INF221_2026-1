/* Fuentes de informacion:
-Matrix-Multiplication(Naive).cpp https://github.com/Dev-XYS/Algorithms/blob/master/Matrix-Multiplication%28Naive%29.cpp*/

#include <vector>
#include "matrix.h"

using namespace std;
//Matrix-Multiplication(Naive).cpp
//Se adaptó el codigo para poder usar vectores
vector<vector<int>> naive(const vector<vector<int>>& A, const vector<vector<int>>& B){
    int tamaño = A.size();
    vector<vector<int>> C(tamaño,vector<int>(tamaño, 0));
    for (int i = 0; i < tamaño; i++){
        for (int j = 0; j < tamaño; j++){
            for(int k = 0; k < tamaño; k++){
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
    return C;
}
