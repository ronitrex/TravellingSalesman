#include <limits>
#include <iostream>
#include "Tour.h"
#include "Matrix.h"

int getNextNode(int prev, int current, std::vector<std::vector<int>> edgeMatrix) {
    int matrixOrder = edgeMatrix.size();
    for (int i = 0; i < matrixOrder; i++) {
        if (edgeMatrix[current][i] == 1 && i != prev) {
            return i;
        }
    }
    return 0;
}

double Tour::findLowerBound() {
    int **inputMatrix = problemMatrix->getMatrix();
    int firstLowest = std::numeric_limits<int>::max(); // Max value of int, to give an upper bound
    int secondLowest = std::numeric_limits<int>::max(); // Max value of int, to give an upper bound
    int matrixOrder = problemMatrix->getOrder();
    int totalNumber = 0;  // Set excluded edges to 0
    bool isSet = false; // Value to check whether the value has been set in "firstLowest" variable

    for (int i = 0; i < matrixOrder; i++) {
        int positiveEdges = 0;

        for (int j = 0; j < matrixOrder; j++) {
            if (positiveEdges == 2) {
                break;
            } else if (tourEdgeMatrix[i][j] == 1 && !isSet) {
                firstLowest = inputMatrix[i][j];
                positiveEdges++;
                isSet = true;
            } else if (tourEdgeMatrix[i][j] == 1 && isSet) {
                secondLowest = inputMatrix[i][j];
                positiveEdges++;
            } else if (inputMatrix[i][j] <= firstLowest && inputMatrix[i][j] != 0 && tourEdgeMatrix[i][j] != -1 &&
                       !isSet) {
                if (firstLowest < secondLowest) {
                    secondLowest = firstLowest;
                }
                firstLowest = inputMatrix[i][j];
            } else if (inputMatrix[i][j] < secondLowest && inputMatrix[i][j] != 0 && tourEdgeMatrix[i][j] != -1) {
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

double Tour::getTourLowerBound() {
    return tourLowerBound;
}

std::vector<std::vector<int>> Tour::getTourEdgeMatrix() {
    return tourEdgeMatrix;
}

bool Tour::checkIsTourComplete() {
    int matrixOrder = tourEdgeMatrix.size();
    for (int i = 0; i < matrixOrder; i++) {
        for (int j = 0; j < matrixOrder; j++) {
            if (i != j) {
                if (tourEdgeMatrix[i][j] == 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Tour::getIsTourComplete() {
    return isTourComplete;
}

bool Tour::checkIsRoute() {
    int matrixOrder = tourEdgeMatrix.size();
    std::vector<int> usedEdges(matrixOrder, 0);
    std::vector<bool> vertVisitList(matrixOrder, false);
    int next = 0;
    int prev = -1; // Keep track of previous edge

    for (int i = 0; i < matrixOrder; i++) {
        for (int j = 0; j < matrixOrder; j++) {
            if (tourEdgeMatrix[i][j] == 1) {
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
        next = getNextNode(prev, 0, tourEdgeMatrix);
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

bool Tour::getIsRoute() {
    isRoute = checkIsRoute();
    return isRoute;
}

int Tour::checkRouteCost() {
    int matrixOrder = tourEdgeMatrix.size();
    int cost = 0;
    for (int i = 0; i < matrixOrder; i++) {
        for (int j = i + 1; j < matrixOrder; j++) {
            if (tourEdgeMatrix[i][j] == 1) {
                cost += problemMatrix->getMatrix()[i][j];
            }
        }
    }
    return cost;
}

int Tour::getRouteCost() {
    return routeCost;
}

void Tour::printRoute() {
    std::cout << "\nThe optimal tour will include the following edges : \n";
    int matrixOrder = tourEdgeMatrix.size();
    for (int i = 0; i < matrixOrder; i++) {
        for (int j = i + 1; j < matrixOrder; j++) {
            if (tourEdgeMatrix[i][j] == 1) {
                char c1 = 65 + i;
                char c2 = 65 + j;
                std::cout << "\t" << c1 << " " << c2 << std::endl;
            }

        }
    }
    std::cout << "Optimal tour has cost : \t" << routeCost << std::endl;
}