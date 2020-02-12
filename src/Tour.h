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

    double findLowerBound(Matrix problemMatrix);

    bool checkIsTourComplete();

    bool checkIsRoute();

    int checkRouteCost(Matrix problemMatrix);

public:
    Tour(Matrix problemMatrix, std::vector<std::vector<int>> edgeMatrix) {
        tourEdgeMatrix = edgeMatrix;
        tourLowerBound = findLowerBound(problemMatrix);
        isTourComplete = checkIsTourComplete();
        isRoute = checkIsRoute();
        if (isRoute) {
            routeCost = checkRouteCost(problemMatrix);
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