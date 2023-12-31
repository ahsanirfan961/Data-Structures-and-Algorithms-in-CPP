//
// Created by ahsan on 12/3/23.
//
#include <iostream>
#include "Algorithm.h"
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <random>
#include <algorithm>

#define ARR_LENGTH 5


using namespace std;

int main()
{
    srand(time(nullptr));

    /*Distinct 100 numbers from 0-99 Generator*/
//    std::vector<int> numbers;
//
//    numbers.reserve(100);
//    for(int i=0; i<100; i++)       // add 0-99 to the vector
//            numbers.push_back(i);
//
//    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//    std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));

//    UndirectedGraph graph(10);
//    for(int i=0;i<=3;i++)
//        graph.addVertex(i);
//
//    graph.addEdge(0, 1, 5);
//    graph.addEdge(1, 2, 2);
//    graph.addEdge(2, 3, 2);
//    graph.addEdge(3, 0, 3);

    UndirectedGraph graph(4);
    graph.addVertex(5);
    graph.addVertex(6);
    graph.addVertex(2);
    graph.addVertex(0);

    graph.addEdge(5,6,3);
    graph.addEdge(6,2,1);
    graph.addEdge(0,2,4);
    graph.addEdge(5,0,8);

    Print::printGraph(graph);

    MinimumSpanningTree mst(graph);

    Print::printGraph(mst);

    clock_t start = clock();



//    double timeElapsed = double(clock()-start)/CLOCKS_PER_SEC * 1000;
//    cout<<"Time Elapsed: "<<fixed<<timeElapsed<<" ms"<<endl;
}

