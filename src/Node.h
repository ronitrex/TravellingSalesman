#include <vector>
#include "Matrix.h"
#include <limits>

#ifndef TRAVELLINGSALESMAN_NODE_H
#define TRAVELLINGSALESMAN_NODE_H

class Node {
private:
    double nodeLowerBound;
    std::vector<std::vector<int>> nodeEdgeMatrix;
    bool isLeafNode;
    bool isRoute;
    int routeCost = std::numeric_limits<int>::max();

    double findLowerBound(Matrix problemMatrix);

    bool checkIsLeafNode();

    bool checkIsRoute();

    int checkRouteCost(Matrix problemMatrix);

public:
    Node(Matrix problemMatrix, std::vector<std::vector<int>> edgeMatrix) {
        nodeEdgeMatrix = edgeMatrix;
        nodeLowerBound = findLowerBound(problemMatrix);
        isLeafNode = checkIsLeafNode();
        isRoute = checkIsRoute();
        if (isRoute) {
            routeCost = checkRouteCost(problemMatrix);
        }
    }

    double getNodeLowerBound();

    std::vector<std::vector<int>> getNodeEdgeMatrix();

    bool getIsLeafNode();

    bool getIsRoute();

    int getRouteCost();

    void printRoute();

};

#endif //TRAVELLINGSALESMAN_NODE_H