#include <iostream>
#include "Matrix.h"
#include <queue>
#include "Node.h"
#include "BranchAndBound.h"
#include "Threads.h"
#include <chrono>
//#include <omp.h>

struct Compare {
    bool operator()(Node &node1, Node &node2) {
        return node1.getNodeLowerBound() > node2.getNodeLowerBound();
    }
};

void singleThreadBAndBTSP(int matrixOrder) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    Matrix problemMatrix(matrixOrder);
    std::cout << "User Input: ";
    std::cout << problemMatrix.getOrder() << std::endl;
    problemMatrix.displayMatrix();

    std::vector<std::vector<int>> edgeMatrix(matrixOrder, std::vector<int>(matrixOrder, 0));
    std::priority_queue<Node, std::vector<Node>, Compare> TSP;
    Node bestNode(problemMatrix, edgeMatrix);
    TSP.push(bestNode);

    int i = 0;
    start = std::chrono::system_clock::now();
    while (!TSP.empty()) {
        Node node = TSP.top();
        if (node.getIsRoute()) {
            if (node.getRouteCost() <= bestNode.getRouteCost()) {
                bestNode = node;
            }
        }

        TSP.pop();

        if (!node.getIsLeafNode()) {
            Threads thread = Threads(node);
            Node leftNode(problemMatrix, thread.getLeftChild());
            Node rightNode(problemMatrix, thread.getRightChild());
            if (leftNode.getNodeLowerBound() <= bestNode.getRouteCost()) {
                TSP.push(leftNode);
            }
            if (rightNode.getNodeLowerBound() <= bestNode.getRouteCost()) {
                TSP.push(rightNode);
            }
            i++;
        }
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    bestNode.printRoute();
    std::cout << "Total nodes popped : \t\t" << i << std::endl;
    std::cout << "Time Taken (in seconds) : \t" << elapsed_seconds.count() << std::endl;

    std::cout << std::endl;
}

int main() {
    int matrixOrder;
    std::cout << "Please enter the order of distanceMatrix. Enter 5 to generate the problem matrix in the readme."
              << std::endl;
    std::cin >> matrixOrder;

    singleThreadBAndBTSP(matrixOrder);

    return 0;

//    // Begin of parallel region
//    int nthreads, tid;
//
//    /* Fork a team of threads with each thread having a private tid variable */
//#pragma omp parallel private(nthreads, tid) default(none)
//    {
//        /* Obtain and print thread id */
//        tid = omp_get_thread_num();
//        printf("Hello World from thread = %d\n", tid);
//
//        /* Only master thread does this */
//        if (tid == 0) {
//            nthreads = omp_get_num_threads();
//            printf("Number of threads = %d\n", nthreads);
//        }
//    }  /* All threads join master thread and terminate */

}