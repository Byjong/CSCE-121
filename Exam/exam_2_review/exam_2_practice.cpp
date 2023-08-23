#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include "exam_2_practice.h"

template<int r, int c>
double** static_to_dynamic(double map[r][c]) {
    double ** t = new double*[r];
    for (int i = 0; i < r; ++i) {
        t[i] = new double[c];
        for (int j = 0; j < c; ++j) {
            t[i][j] = map[i][j];
        }
    }

    return t;
}

double distance[5][5] = {
    {0.0, 30.0, 10.0, 70.0, 10.0},
    {30.0, 0.0, 45.0, 100.0, 50.0},
    {10.0, 45.0, 0.0, 85.0, 20.0},
    {70.0, 100.0, 85.0, 0.0, 100.0},
    {10.0, 50.0, 20.0, 100.0, 0.0}
};

int* path = new int[6] {0, 1, 0, 3, 2, 0};

double pathLength(double** distance, int n, int* path, int m){
    double length = 0;
    for (int i = 0; i < m -1; ++i){
        for (int r = 0; r < n; ++r){
            for (int c = 0; c < n; ++c){
                if(r == path[i] && c == path[i+1]){
                    length += distance[r][c];
                }
            }
        }
    }
    return length;
}

/*      /////AvgMatrix: INCOMPLETE

double matrix[3][4] = {
    {0.5, 2.0, 1.2, 3.0},
    {-1.0, 1.5, 3.0, 2.4},
    {0.0, 1.0, 1.5, 2.0}
};



void avgMatrix(double** inArray, int rows, int columns, double** outArray){
    for(int i = 0; i < rows; ++i){
        outArray[i] = new double[columns];
    }

    for(int rIdx = 0; rIdx < rows; ++rIdx){
        for(int cIdx = 0; cIdx < columns; ++cIdx){
            
            double avg = 0;
            if(rIdx == 0){
                if(cIdx == 0){
                    avg = (inArray[rIdx+1][cIdx] + inArray[rIdx][cIdx+1] + inArray[rIdx+1][cIdx+1]) / 3;
                }
                else if(cIdx == columns - 1){
                    avg = (inArray[rIdx][cIdx-1] + inArray[rIdx+1][cIdx-1] + inArray[rIdx+1][cIdx]) / 3;
                }
                else{
                    avg = (inArray[rIdx][cIdx-1] + inArray[rIdx][cIdx+1] + inArray[rIdx+1][cIdx] + )
                }
            }
            else if(rIdx == rows-1){}

        }
    }
}*/

void minusOddColumn(int** mat, int n){
    int oddCol = 0;
    int maxOdds = 0;

    for(int i = 0; i < n; ++i){
        int numOdds = 0;
        for(int j = 0; j < n; ++j){
            if(mat[j][i] % 2 == 1){
                ++numOdds;
            }
        }
        if(numOdds > maxOdds){
            maxOdds = numOdds;
            oddCol = i;
        }
    }

    for(int r = 0; r < n; ++r){
        mat[r][oddCol] = -1;
    }
}

int mtx[5][5] = {
    {0, 30, 10, 70, 10},
    {30, 0, 45, 100, 50},
    {10, 45, 0, 85, 20},
    {70, 100, 85, 0, 100},
    {10, 50, 20, 100, 0}
};

int mtx2[2][2] = {
    {30, 0},
    {0, 30}
};

template<int r, int c>
int** static_to_dynamic(int map[r][c]) {
    int ** t = new int*[r];
    for (int i = 0; i < r; ++i) {
        t[i] = new int[c];
        for (int j = 0; j < c; ++j) {
            t[i][j] = map[i][j];
        }
    }

    return t;
}

int main(){
    
    int n = 5;
    int m = 6;
    double** map = static_to_dynamic<5, 5>(distance);
    std::cout << pathLength(map, n, path, m) << std::endl;

    std::cout << std::endl;


    /* AvgMatrix: INCOMPLETE
    double** mtx = static_to_dynamic<3, 4>(matirx);
    int r = 3;
    int c = 4;
    double** out = new double*[r];
    std::cout
    */

    int** mat = static_to_dynamic<5, 5>(mtx);
    minusOddColumn(mat, n);

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    mat = static_to_dynamic<2, 2>(mtx2);
    n = 2;
    minusOddColumn(mat, n);
    
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    return 0;
}