#include <limits>
#include <iostream>
#include "Node.h"
#include "Matrix.h"

int getNextNode(int prev, int current, std::vector<std::vector<int>> edgeMatrix) {
    int matrixOrder = edgeMatrix.size();
    for (int i = 0; i < matrixOrder; i++) {
        if (edgeMatrix[current][i] == 1 && i != prev) {
            return i;
        }
    }
}

double Node::findLowerBound(Matrix problemMatrix) {
    int **inputMatrix = problemMatrix.getMatrix();
    int firstLowest = std::numeric_limits<int>::max(); // Max value of int, to give an upper bound
    int secondLowest = std::numeric_limits<int>::max(); // Max value of int, to give an upper bound
    int matrixOrder = problemMatrix.getOrder();
    int totalNumber = 0;  // Set excluded edges to 0
    bool isSet = false; // Value to check whether the value has been set in "firstLowest" variable

    for (int i = 0; i < matrixOrder; i++) {
        int positiveEdges = 0;

        for (int j = 0; j < matrixOrder; j++) {
            if (positiveEdges == 2) {
                break;
            } else if (nodeEdgeMatrix[i][j] == 1 && !isSet) {
                firstLowest = inputMatrix[i][j];
                positiveEdges++;
                isSet = true;
            } else if (nodeEdgeMatrix[i][j] == 1 && isSet) {
                secondLowest = inputMatrix[i][j];
                positiveEdges++;
            } else if (inputMatrix[i][j] <= firstLowest && inputMatrix[i][j] != 0 && nodeEdgeMatrix[i][j] != -1 &&
                       !isSet) {
                if (firstLowest < secondLowest) {
                    secondLowest = firstLowest;
                }
                firstLowest = inputMatrix[i][j];
            } else if (inputMatrix[i][j] < secondLowest && inputMatrix[i][j] != 0 && nodeEdgeMatrix[i][j] != -1) {
                secondLowest = inputMatrix[i][j];
            }
        }
        isSet = false;

        if (firstLowest == std::numeric_limits<int>::max() || secondLowest == std::numeric_limits<int>::max()) {
            totalNumber = 0;
            return totalNumber;
        } else {
            totalNumber = totalNumber + firstLowest + secondLowest;
            firstLowest = std::numeric_limits<int>::max(); // Max value of int, to give an upper bound
            secondLowest = std::numeric_limits<int>::max(); // Max value of int, to give an upper bound
        }
    }
    return totalNumber / 2.0;
}

double Node::getNodeLowerBound() {
    return nodeLowerBound;
}

std::vector<std::vector<int>> Node::getNodeEdgeMatrix() {
    return nodeEdgeMatrix;
}

bool Node::checkIsLeafNode() {
    int matrixOrder = nodeEdgeMatrix.size();
    for (int i = 0; i < matrixOrder; i++) {
        for (int j = 0; j < matrixOrder; j++) {
            if (i != j) {
                if (nodeEdgeMatrix[i][j] == 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Node::getIsLeafNode() {
    return isLeafNode;
}

bool Node::checkIsRoute() {
    int matrixOrder = nodeEdgeMatrix.size();
    std::vector<int> usedEdges(matrixOrder, 0);
    std::vector<bool> vertVisitList(matrixOrder, false);
    int next = 0;
    int prev = -1; // Keep track of previous node


    for (int i = 0; i < matrixOrder; i++) {
        for (int j = 0; j < matrixOrder; j++) {
            if (nodeEdgeMatrix[i][j] == 1) {
                usedEdges[i] = usedEdges[i] + 1;
            }
        }
    }

    for (int i = 0; i < matrixOrder; i++) {
        if (usedEdges[i] != 2) {
            return false;
        }
    }
    bool isNotCircle = true;
    int i = 0;
    while (isNotCircle || (i <= matrixOrder)) {
        i++;
        next = getNextNode(prev, 0, nodeEdgeMatrix);
        prev = next;
        // There is a circle!
        if (vertVisitList[next] == true) {
            isNotCircle = false;
        } else {
            vertVisitList[next] = true;
        }
    }
    return true;
}

bool Node::getIsRoute() {
    isRoute = checkIsRoute();
}

int Node::checkRouteCost(Matrix problemMatrix) {
    int matrixOrder = nodeEdgeMatrix.size();
    int cost = 0;
    for (int i = 0; i < matrixOrder; i++) {
        for (int j = i + 1; j < matrixOrder; j++) {
            if (nodeEdgeMatrix[i][j] == 1) {
                cost += problemMatrix.getMatrix()[i][j];
            }
        }
    }
    return cost;
}

int Node::getRouteCost() {
    return routeCost;
}

void Node::printRoute() {
    std::cout << "\nThe optimal path will include the following edges : \n";
    int matrixOrder = nodeEdgeMatrix.size();
    for (int i = 0; i < matrixOrder; i++) {
        for (int j = i + 1; j < matrixOrder; j++) {
            if (nodeEdgeMatrix[i][j] == 1) {
                std::cout << " " << i << " " << j << std::endl;
            }

        }
    }
    std::cout << "Optimal route has cost : \t" << routeCost << std::endl;
}