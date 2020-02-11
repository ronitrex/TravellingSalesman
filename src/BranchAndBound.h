#include "Node.h"
#include "Matrix.h"
#include <iostream>

#ifndef TRAVELLINGSALESMAN_BRANCHANDBOUND_H
#define TRAVELLINGSALESMAN_BRANCHANDBOUND_H

class BranchAndBound {
private:
    std::vector<std::vector<int>> PLUSedgeMatrix;           //leftChild
    std::vector<std::vector<int>> MINUSedgeMatrix;          //rightChild
public:
    BranchAndBound(std::vector<std::vector<int>> edgeMatrix) {
        PLUSedgeMatrix = edgeMatrix;
        MINUSedgeMatrix = edgeMatrix;
        getChildNodes(edgeMatrix);
    }

    std::vector<std::vector<int>> updateEdgeMatrix(std::vector<std::vector<int>> edgeMatrix, int v);

    void displayEdgeMatrix(std::vector<std::vector<int>> edgeMatrix);

    void getChildNodes(std::vector<std::vector<int>> edgeMatrix);

    std::vector<std::vector<int>> getPLUSedgeMatrix();

    std::vector<std::vector<int>> getMINUSedgeMatrix();
};

#endif //TRAVELLINGSALESMAN_BRANCHANDBOUND_H