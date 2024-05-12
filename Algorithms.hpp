//206971962 / kaufmanlinoy@gmail.com


#include <iostream>
#include <vector>
#include <stack> 
#include "Graph.hpp"


using namespace std;
namespace ariel{

    class Algorithms
    {
        public:
        static int isConnected(const Graph &gr);
        static string shortestPath(const Graph &gr,size_t start, size_t end);
        static int isContainsCycle(const Graph &gr);
        static int isBipartite(const Graph &gr);
        static string negativeCycle(const Graph &gr);
    };
}
