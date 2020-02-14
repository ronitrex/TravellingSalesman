#include <vector>
#include "Matrix.h"
#include <limits>

#ifndef TRAVELLINGSALESMAN_TOUR_H
#define TRAVELLINGSALESMAN_TOUR_H

class Tour {
private:
    double tourLowerBound;
    std::vector<std::vector<int>> tourEdgeMatrix;
    bool isTourComplete;
    bool isRoute;
    int routeCost = std::numeric_limits<int>::max();
    Matrix* problemMatrix;

    double findLowerBound();

    bool checkIsTourComplete();

    bool checkIsRoute();

    int checkRouteCost();

public:
    Tour(Matrix* problemMatrix, std::vector<std::vector<int>> edgeMatrix) : problemMatrix(problemMatrix){
        tourEdgeMatrix = edgeMatrix;
        tourLowerBound = findLowerBound();
        isTourComplete = checkIsTourComplete();
        isRoute = checkIsRoute();
        if (isRoute) {
            routeCost = checkRouteCost();
        }
    }

    double getTourLowerBound();

    std::vector<std::vector<int>> getTourEdgeMatrix();

    bool getIsTourComplete();

    bool getIsRoute();

    int getRouteCost();

    void printRoute();

};

#endif //TRAVELLINGSALESMAN_TOUR_H