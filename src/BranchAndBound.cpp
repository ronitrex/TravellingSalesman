#include <vector>
#include <iostream>
#include "BranchAndBound.h"

void BranchAndBound::displayEdgeMatrix(std::vector<std::vector<int>> edgeMatrix) {
    int matrixOrder = edgeMatrix.size();
    std::cout << "Printing the edge Matrix representing the Node.\n";
    for (int i = 0; i < matrixOrder; i++) {
        for (int j = 0; j < matrixOrder; j++) {
            if (edgeMatrix[i][j] >=
                0)                                                          // If value is non-negative, we print it with a space behind it for formatting
                std::cout << " " << edgeMatrix[i][j] << " ";
            else std::cout << edgeMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> BranchAndBound::updateEdgeMatrix(std::vector<std::vector<int>> edgeMatrix, int v) {
    int matrixOrder = edgeMatrix.size();
    for (int i = v; i < matrixOrder; i++) {
        int edgesConsidered = 0;                                                                        // Tracks the total number of edges that should be incident with
        int remainingEdges = 0;                                                                     // Tracks the remaining edges to be considered
        for (int j = 0; j < matrixOrder; j++) {
            if (i != j && edgeMatrix[i][j] == 1) {
                edgesConsidered++;
            } else if (i != j && edgeMatrix[i][j] == 0) {
                remainingEdges++;
            }
        }

        if (edgesConsidered < 2) {
            if ((remainingEdges == 2 && edgesConsidered == 0) || (remainingEdges == 1 && edgesConsidered == 1)) {
                for (int j = 0; j < matrixOrder; j++) {
                    if (i != j && edgeMatrix[i][j] == 0) {
                        edgeMatrix[i][j] = 1;
                        edgeMatrix[j][i] = 1;
                    }
                }
            }
        } else {
            for (int j = 0; j < matrixOrder; j++) {
                if (i != j && edgeMatrix[i][j] == 0) {
                    edgeMatrix[i][j] = -1;
                    edgeMatrix[j][i] = -1;
                }
            }
        }
    }
    return edgeMatrix;
}

void BranchAndBound::getChildNodes(std::vector<std::vector<int>> edgeMatrix) {
    int matrixOrder = edgeMatrix.size();
    bool edgeMatrixGenerated = false;
    for (int i = 0; i < matrixOrder; i++) {
        for (int j = 0; j < matrixOrder; j++) {
            if (i != j) {
                if (edgeMatrix[i][j] == 0) {
                    edgeMatrixGenerated = true;
                    PLUSedgeMatrix[i][j] = 1;
                    PLUSedgeMatrix[j][i] = 1;
                    PLUSedgeMatrix = updateEdgeMatrix(PLUSedgeMatrix, i);
                    MINUSedgeMatrix[i][j] = -1;
                    MINUSedgeMatrix[j][i] = -1;
                    MINUSedgeMatrix = updateEdgeMatrix(MINUSedgeMatrix, i);
                    break;
                }
            }
        }
        if (edgeMatrixGenerated) {
            break;
        }

    }
    if (!edgeMatrixGenerated) {
        throw 1;
    }
}

std::vector<std::vector<int>> BranchAndBound::getPLUSedgeMatrix() {
    return std::vector<std::vector<int>>(PLUSedgeMatrix);
}

std::vector<std::vector<int>> BranchAndBound::getMINUSedgeMatrix() {
    return std::vector<std::vector<int>>(MINUSedgeMatrix);
}

//BranchAndBound BranchAndBound::rightChild() {
//    return BranchAndBound(MINUSedgeMatrix);
//}
//
//BranchAndBound BranchAndBound::leftChild() {
//    return BranchAndBound(PLUSedgeMatrix);
//}