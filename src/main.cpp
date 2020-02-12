#include <iostream>
#include "Matrix.h"
#include <omp.h>
#include <queue>
#include "Tour.h"
#include "BranchAndBound.h"
#include "Threads.h"
#include <chrono>

struct Compare {
    bool operator()(Tour &tour1, Tour &tour2) {
        return tour1.getTourLowerBound() > tour2.getTourLowerBound();
    }
};

void singleThreadBAndBTSP(int matrixOrder) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    Matrix problemMatrix(matrixOrder);
    std::cout << "User Input: ";
    std::cout << problemMatrix.getOrder() << "\n" << std::endl;
    problemMatrix.displayMatrix();

    std::vector<std::vector<int>> edgeMatrix(matrixOrder, std::vector<int>(matrixOrder, 0));
    std::priority_queue<Tour, std::vector<Tour>, Compare> TSP;
    Tour bestTour(problemMatrix, edgeMatrix);
    TSP.push(bestTour);

    int i = 0;
    start = std::chrono::system_clock::now();
    while (!TSP.empty()) {
        Tour tour = TSP.top();
        TSP.pop();
        if (tour.getIsRoute()) {
            if (tour.getRouteCost() <= bestTour.getRouteCost()) {
                bestTour = tour;
            }
        }

        if (!tour.getIsTourComplete()) {
            Threads thread = Threads(tour);
            Tour leftChildTour(problemMatrix, thread.getLeftChild());
            Tour rightChildTour(problemMatrix, thread.getRightChild());
            if (leftChildTour.getTourLowerBound() <= bestTour.getRouteCost()) {
                TSP.push(leftChildTour);
            }
            if (rightChildTour.getTourLowerBound() <= bestTour.getRouteCost()) {
                TSP.push(rightChildTour);
            }
            i++;
        }
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    bestTour.printRoute();
    std::cout << "Total Tours considered :\t" << i << std::endl;
    std::cout << "Time Taken (in seconds) :\t" << elapsed_seconds.count() << std::endl;

    std::cout << std::endl;
}

int main() {
    int matrixOrder;
    std::cout << "Please enter the order of problem matrix. Enter 5 to generate the problem matrix explained in readme."
              << std::endl;
    std::cin >> matrixOrder;

    singleThreadBAndBTSP(matrixOrder);

    return 0;

    // Begin of parallel region
    int nthreads, tid;

    /* Fork a team of threads with each thread having a private tid variable */
#pragma omp parallel private(nthreads, tid) default(none)
    {
        /* Obtain and print thread id */
        tid = omp_get_thread_num();
        printf("Hello World from thread = %d\n", tid);

        /* Only master thread does this */
        if (tid == 0) {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
    }  /* All threads join master thread and terminate */

}