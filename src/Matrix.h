#include <vector>

#ifndef TRAVELLINGSALESMAN_MATRIX_H
#define TRAVELLINGSALESMAN_MATRIX_H

class Matrix {
private:
    int order;
    int **distanceMatrix;

    int **generateMatrix();

    void populateMatrix();

    void defaultMatrix();

public:
    Matrix(int order) : order(order) {
        distanceMatrix = generateMatrix();
        if (order == 5) {
            defaultMatrix();
        } else {
            populateMatrix();
        }
    }

    int getOrder();

    int **getMatrix();

    void displayMatrix();
};

#endif //TRAVELLINGSALESMAN_MATRIX_H