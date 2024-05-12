    // 206971962 / kaufmanlinoy@gmail.com
    #include "Graph.hpp"
    #include <iostream>


    using namespace std;
    using namespace ariel;



    Graph::Graph() noexcept {}
    Graph::~Graph() noexcept {}


    //chek if the mat is valid
    bool Graph::isvalid(const std::vector<std::vector<int>>& mat)
    {
        if(mat.empty()){
    
            return false;
        }
        else{
            size_t size = mat.size();
            for (const auto& row : mat) {
                for(int i = 0 ; i<mat.size();i++)
                    if (row.size() != size) {
                        return false;
                    }
                }
        }
        return true;
    }
    //send invalid the matrix and if true, load else, throw invalid gragh
    void Graph::loadGraph(const vector<vector<int> > &mat)
    {
        if(isvalid(mat)){
            this->Matrix = mat;
        }
        else{
            throw std::invalid_argument("invalid Matrix");
        }
    }
    //print num of vertices and edges
    void Graph::printGraph() const
    {
        int numVertices = Matrix.size();
        int numEdges = 0;
        for (const auto& row : Matrix)
        {
            for (int edge : row)
            {
                if (edge != 0)
                {
                    numEdges++;
                }
            }
        }
        cout << "Graph with " << numVertices << " vertices and " << numEdges << " edges." << endl;
    }
