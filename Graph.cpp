// 206971962 / kaufmanlinoy@gmail.com
#include "Graph.hpp"
#include <iostream>

#include "Graph.hpp"
using namespace std;
namespace ariel{



Graph::Graph(vector<vector<int> > matrix1, size_t v1, bool isDirected1)
{
    this->matrix = matrix1;
    this->v = v1;
    this->isDirected = isDirected1;
    this->type_graph = 0;
}
}