#include "Tour.h"
#include "BranchAndBound.h"

#ifndef TRAVELLINGSALESMAN_THREADS_H
#define TRAVELLINGSALESMAN_THREADS_H

class Threads {
private:
    std::vector<std::vector<int>> leftChild;         // PLUSedgeMatrix()
    std::vector<std::vector<int>> rightChild;        // MINUSedgeMatrix()
public:
    Threads(Tour tour) {
        BranchAndBound BandB(tour.getTourEdgeMatrix());
        leftChild = BandB.getPLUSedgeMatrix();
        rightChild = BandB.getMINUSedgeMatrix();
    }

    std::vector<std::vector<int>> getLeftChild();

    std::vector<std::vector<int>> getRightChild();
};

#endif //TRAVELLINGSALESMAN_THREADS_H