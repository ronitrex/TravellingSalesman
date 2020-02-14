#include <iostream>
#include <omp.h>
#include <queue>
#include <chrono>
#include <thread>
#include <mutex>
#include "Tour.h"
#include "BranchAndBound.h"
#include "Threads.h"
#include "Matrix.h"

std::mutex mutexBestTour;

std::mutex mutexTSP;

struct Compare {
    bool operator()(Tour &tour1, Tour &tour2) {
        return tour1.getTourLowerBound() > tour2.getTourLowerBound();
    }
};

void Tourism(std::priority_queue<Tour, std::vector<Tour>, Compare> *TSP, Tour *bestTour, Matrix problemMatrix,
             bool *keepWaiting, int threadNumber, int *v) {
    while (*keepWaiting) {

        mutexTSP.lock();

        if (TSP->empty()) {
            v[threadNumber] = 0;
            int total = 0;
            for (int i = 0; i < sizeof(v); i++) {
//                std::cout << total << std::endl;
                total = total + v[i];
            }
            if (total == 0) {
                *keepWaiting = false;
            }
            mutexTSP.unlock();
            continue;
        }
        v[threadNumber] = 1;
        Tour tour = TSP->top();
        TSP->pop();

        mutexTSP.unlock();

        if (tour.getIsRoute()) {
            if (tour.getRouteCost() <= bestTour->getRouteCost()) {
                mutexBestTour.lock();
                *bestTour = tour;
                mutexBestTour.unlock();
            }
        }
        if (!tour.getIsTourComplete()) {
            Threads thread = Threads(tour);
            Tour leftChildTour(problemMatrix, thread.getLeftChild());
            Tour rightChildTour(problemMatrix, thread.getRightChild());
            double leftChildTourLowerBound = leftChildTour.getTourLowerBound();
            double rightChildTourTourLower = rightChildTour.getTourLowerBound();

            mutexTSP.lock();

            if (leftChildTourLowerBound <= bestTour->getRouteCost()) {
                TSP->push(leftChildTour);
            }
            if (rightChildTourTourLower <= bestTour->getRouteCost()) {
                TSP->push(rightChildTour);
            }

            mutexTSP.unlock();
        }
    }
}

void multiThreadBAndBTSP(Matrix problemMatrix) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int matrixOrder = problemMatrix.getOrder();
    std::vector<std::vector<int>> edgeMatrix(matrixOrder, std::vector<int>(matrixOrder, 0));
    std::priority_queue<Tour, std::vector<Tour>, Compare> toursPQ;
    Tour bestTour(problemMatrix, edgeMatrix);
    toursPQ.push(bestTour);

    int numThreads = std::thread::hardware_concurrency();
    int choice = 1;

    std::cout << "Please select solution mode. \n1. Single-threaded sequential solution. \n2. Multi-threaded parallel solution." << std::endl;
    std::cin >> choice;
    if(choice==1){
        numThreads = 1;
        std::cout << "Running in single-threaded sequential mode" <<std::endl;
    }else{
        std::cout << "\n" << numThreads << " concurrent thread(s) supported by system. Using  " << numThreads
                  << " thread(s) for maximum performance." << std::endl;
    }

    int numThreadsArray[48];
    for (int i = 0; i < 48; i++) {
        if (i < numThreads) {
            numThreadsArray[i] = 1;
        } else {
            numThreadsArray[i] = 0;
        }
    }
    std::thread dynamicThreads[numThreads];
    bool keepWaiting = true;

    start = std::chrono::system_clock::now();
    for (int i = 0; i < numThreads; i++) {
        dynamicThreads[i] = std::thread(Tourism, &toursPQ, &bestTour, problemMatrix, &keepWaiting, i, numThreadsArray);
    }

    for (int i = 0; i < numThreads; i++) {
        dynamicThreads[i].join();
    }
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    bestTour.printRoute();
    std::cout << "Time Taken (in seconds) :\t" << elapsed_seconds.count() << std::endl;
    std::cout << std::endl;
}


int main() {
    int matrixOrder;
    std::cout << "Please enter the order of problem matrix. Enter 5 to generate the problem matrix explained in readme."
              << std::endl;
    std::cin >> matrixOrder;

    std::cout << "User Input: ";
    Matrix problemMatrix(matrixOrder);
    std::cout << problemMatrix.getOrder() << "\n" << std::endl;
    problemMatrix.displayMatrix();
    multiThreadBAndBTSP(problemMatrix);
    return 0;
}