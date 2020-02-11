#include <iostream>
#include "Matrix.h"
#include <omp.h>
#include <queue>
#include "Node.h"
#include "BranchAndBound.h"
#include "Threads.h"

struct Compare {
    bool operator()(Node &node1, Node &node2) {
        return node1.getNodeLowerBound() > node2.getNodeLowerBound();
    }
};

int main() {
    int matrixOrder;
    std::cout << "Please enter the order of distanceMatrix" << std::endl;
    std::cin >> matrixOrder;
    Matrix problemMatrix(matrixOrder);
    std::cout << "User Input: ";
    std::cout << problemMatrix.getOrder() << std::endl;
    problemMatrix.displayMatrix();

    std::vector<std::vector<int>> edgeMatrix(matrixOrder, std::vector<int>(matrixOrder, 0));
    std::priority_queue<Node, std::vector<Node>, Compare> TSP;

    Node bestNode(problemMatrix, edgeMatrix);
    TSP.push(bestNode);

    int i = 0;
    while (!TSP.empty()) {
        Node node = TSP.top();
        if (node.getIsRoute()) {
            if (node.getRouteCost() < bestNode.getRouteCost()) {
                bestNode = node;
            }
        }

        TSP.pop();
        if (!node.getIsLeafNode()) {
            Threads thread = Threads(node);
            Node leftNode1(problemMatrix, thread.getLeftChild());
            Node rightNode1(problemMatrix, thread.getRightChild());
            TSP.push(leftNode1);
            TSP.push(rightNode1);
            i++;
        }
    }
    bestNode.printRoute();
    std::cout << "Number of pops = " << i << std::endl;
    std::cout << std::endl;



    // Begin of parallel region
    int nthreads, tid;

    return 0;
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