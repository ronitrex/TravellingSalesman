#include "Matrix.h"
#include <cstdlib>
#include <iostream>

int Matrix::getOrder() {
    return order;
};

int **Matrix::generateMatrix() {
    int **tempGenerator = new int *[order];
    for (int i = 0; i < order; i++) {
        tempGenerator[i] = new int[order];
    }
    return tempGenerator;
}

void Matrix::populateMatrix() {
    for (int i = 0; i < order; i++) {
        for (int j = 0; j <= i; j++) {
            if (i == j) {
                this->distanceMatrix[i][j] = 0;
            } else {
                int randomInt = rand() % 10;
                if (randomInt == 0){
                    randomInt = 9;
                }
                this->distanceMatrix[i][j] = this->distanceMatrix[j][i] = (randomInt);
            }
        }
    }
}

void Matrix::displayMatrix() {
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
            std::cout << this->distanceMatrix[i][j] << "\t\t";
        }
        std::cout << std::endl;
    }
}

int **Matrix::getMatrix() {
    return distanceMatrix;
}

void Matrix::defaultMatrix() {
    int defaultMatrix[5][5] = {{0, 3, 4, 2, 7},
                               {3, 0, 4, 6, 3},
                               {4, 4, 0, 5, 8},
                               {2, 6, 5, 0, 6},
                               {7, 3, 8, 6, 0}};
    std::cout << "Using the sample matrix explained in readme:" << std::endl;
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
            this->distanceMatrix[i][j] = defaultMatrix[i][j];

        }
    }
}

//Matrix::~Matrix() {
//    for (int i = 0; i < order; i++) {
//        delete[] this->distanceMatrix[i];
//    }
//}

//int Matrix::getValueAt(int i, int j) {
//    return this->distanceMatrix[i][j];
//}