#include "Tour.h"
#include "Matrix.h"
#include <iostream>

#ifndef TRAVELLINGSALESMAN_BRANCHANDBOUND_H
#define TRAVELLINGSALESMAN_BRANCHANDBOUND_H

class BranchAndBound {
private:
    std::vector<std::vector<int>> PLUSedgeMatrix;           //leftChild
    std::vector<std::vector<int>> MINUSedgeMatrix;          //rightChild
    void getChildTours(std::vector<std::vector<int>> edgeMatrix);

public:
    explicit BranchAndBound(std::vector<std::vector<int>> edgeMatrix) {
        PLUSedgeMatrix = edgeMatrix;
        MINUSedgeMatrix = edgeMatrix;
        getChildTours(edgeMatrix);
    }

    std::vector<std::vector<int>> updateEdgeMatrix(std::vector<std::vector<int>> edgeMatrix, int v);

    std::vector<std::vector<int>> getPLUSedgeMatrix();

    std::vector<std::vector<int>> getMINUSedgeMatrix();
};

#endif //TRAVELLINGSALESMAN_BRANCHANDBOUND_H