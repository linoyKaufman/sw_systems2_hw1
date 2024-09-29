// 206971962 / kaufmanlinoy@gmail.com
#include "Graph.hpp"
#include <iostream>
#include <vector>
#include <ostream>
#include <sstream>
#include "Algorithms.hpp"

namespace ariel {

// Default constructor for Graph
Graph::Graph() {}

// Destructor for Graph
Graph::~Graph() {}

// Function to reset the graph by clearing its adjacency matrix
void Graph::cleanGraph() {
    this->getMatrix();
}

// Check if the matrix is valid (i.e., it's a square matrix)
bool Graph::isvalid(const std::vector<std::vector<int>>& mat) {
    if (mat.empty()) {
        return false;
    } else {
        size_t size = mat.size(); // Number of rows
        for (const auto& row : mat) { // Iterate through each row
            if (row.size() != size) { // Ensure each row has the same number of columns
                return false;
            }
        }
    }
    return true;
}

// Load the graph with a given matrix if valid; otherwise, throw an exception
void Graph::loadGraph(const vector<vector<int>>& mat) {
    if (isvalid(mat)) {
        this->Matrix = mat; // If valid, store the matrix
    } else {
        throw std::invalid_argument("invalid Matrix");
    }
}

// Print the number of vertices and edges in the graph
void Graph::printGraph() const {
    int numVertices = Matrix.size();
    int numEdges = 0;
    for (const auto& row : Matrix) {
        for (int edge : row) {
            if (edge != 0) { // Count all non-zero entries as edges
                numEdges++;
            }
        }
    }
    cout << "Graph with " << numVertices << " vertices and " << numEdges << " edges." << endl;
}

// Get the neighbors (connected vertices) of a given node
std::vector<std::size_t> Graph::getNeighbors(std::size_t node) const {
    std::vector<std::size_t> neighbors;
    const std::vector<int>& row = Matrix[node]; // Access the row corresponding to the node

    // Iterate over the row to find the neighbors (non-zero entries)
    for (std::size_t i = 0; i < row.size(); ++i) {
        if (row[i] != 0) {
            neighbors.push_back(i); // Add the index to the neighbors vector
        }
    }

    return neighbors;
}

// Helper function to check if two matrices have the same size
bool isSameSize(const vector<vector<int>>& mat1, const vector<vector<int>>& mat2) {
    if (mat1.size() != mat2.size()) {
        return false;
    }
    for (size_t i = 0; i < mat1.size(); i++) {
        if (mat1[i].size() != mat2[i].size()) {
            return false;
        }
    }
    return true;
}

// Check if graph `g1` is contained in the current graph
bool Graph::isContaine(Graph& g1) {
    if (g1.getMatrix().size() > this->getMatrix().size()) {
        return false;  // g1 is bigger
    }
    for (size_t i = 0; i < this->getMatrix().size(); i++) {
        for (size_t j = 0; i < this->getMatrix().size(); j++) {
            // Check if g1 has more connections than the current graph
            if (g1.getMatrix()[i][j] >= 1 && g1.getMatrix()[i][j] > this->getMatrix()[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Count the number of edges in the graph
int Graph::getEdges() const {
    int numEdges = 0;
    for (const auto& row : Matrix) {
        for (int edge : row) {
            if (edge != 0) {
                numEdges++;
            }
        }
    }
    return numEdges;
}

// Unary plus operator (returns a copy of the graph)
Graph Graph::operator+() const {
    return *this;
}

// Binary addition operator for two graphs (sum their adjacency matrices)
Graph operator+(const Graph& g1, const Graph& g2) {
    if (!isSameSize(g1.getMatrix(), g2.getMatrix())) {
        throw std::invalid_argument("the matrices are not equal in size");
    }

    Graph g3;
    size_t n = g1.size();
    vector<vector<int>> helpGraph(n, vector<int>(n, 0));

    // Sum corresponding elements in the two adjacency matrices
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            helpGraph[i][j] = g1.getMatrix()[i][j] + g2.getMatrix()[i][j];
        }
    }

    g3.loadGraph(helpGraph);
    return g3;
}

// Binary subtraction operator for two graphs (subtract their adjacency matrices)
Graph operator-(const Graph& g1, const Graph& g2) {
    if (!isSameSize(g1.getMatrix(), g2.getMatrix())) {
        throw std::invalid_argument("the matrices are not equal in size");
    }

    Graph g3;
    size_t n = g1.size();
    vector<vector<int>> helpGraph(n, vector<int>(n, 0));

    // Subtract corresponding elements in the adjacency matrices
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            helpGraph[i][j] = g1.getMatrix()[i][j] - g2.getMatrix()[i][j];
        }
    }

    g3.loadGraph(helpGraph);
    return g3;
}

// Compound addition-assignment operator
void Graph::operator+=(const Graph& g1) {
    if (!isSameSize(g1.getMatrix(), this->getMatrix())) {
        throw std::invalid_argument("the matrices are not equal in size");
    }

    size_t n = g1.size();

    // Add corresponding elements
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            this->getMatrix()[i][j] += g1.getMatrix()[i][j];
        }
    }
}

// Compound subtraction-assignment operator
void Graph::operator-=(const Graph& g1) {
    if (!isSameSize(g1.getMatrix(), this->getMatrix())) {
        throw std::invalid_argument("the matrices are not equal in size");
    }

    size_t n = g1.size();

    // Subtract corresponding elements
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            this->getMatrix()[i][j] -= g1.getMatrix()[i][j];
        }
    }
}

// Increment each element of the adjacency matrix by 1
void Graph::operator++() {
    size_t size = this->getMatrix().size();
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            this->getMatrix()[i][j]++;
        }
    }
}

// Decrement each element of the adjacency matrix by 1
void Graph::operator--() {
    size_t size = this->getMatrix().size();
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            this->getMatrix()[i][j]--;
        }
    }
}

// Comparison operators for equality, less than, and greater than
bool Graph::operator==(Graph& g1) {
    if (!isSameSize(g1.getMatrix(), this->getMatrix())) {
        return false;
    }
    size_t n = g1.getMatrix().size();
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (g1.getMatrix()[i][j] != this->getMatrix()[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Graph::operator>(Graph& g1) {
    if (g1.isContaine(*this) && !isSameSize(g1.getMatrix(), this->getMatrix())) {
        return true;
    }
    if (this->isContaine(g1) && !isSameSize(g1.getMatrix(), this->getMatrix())) {
        return false;
    }
    if (this->getEdges() > g1.getEdges()) {
        return true;
    } else if (this->size() > g1.size()) {
        return true;
    }
    return false;
}

bool Graph::operator<(Graph& g1) {
    return !(*this > g1);
}

bool Graph::operator<=(Graph& g1) {
    return (*this < g1) || (g1.operator==(*this));
}

bool Graph::operator>=(Graph& g1) {
    return (*this > g1) || (g1.operator==(*this));
}

bool Graph::operator!=(Graph& g1) {
    return !g1.operator==(*this);
}

// Multiplication operator for scalar multiplication
void Graph::operator*(int num) const {
    size_t size = this->getMatrix().size();
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            this->getMatrix()[i][j] *= num;
        }
    }
}

// Compound multiplication operator
void Graph::operator*=(int num) {
    size_t numROWthis = this->Matrix.size();
    size_t numCOLthis = this->Matrix[0].size();

    for (size_t i = 0; i < numROWthis; i++) {
        for (size_t j = 0; j < numCOLthis; j++) {
            this->getMatrix()[i][j] *= num;
        }
    }
}

// Graph multiplication operator (matrix multiplication)
Graph Graph::operator*(Graph& g1) {
    if (this->getMatrix()[0].size() != g1.getMatrix().size()) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");
    }

    size_t numROWthis = this->Matrix.size();
    size_t numCOLthis = this->Matrix[0].size();
    size_t COLg1 = g1.Matrix[0].size();

    std::vector<std::vector<int>> resultMat(numROWthis, std::vector<int>(COLg1, 0));

    for (size_t i = 0; i < numROWthis; i++) {
        for (size_t j = 0; j < COLg1; j++) {
            for (size_t k = 0; k < numCOLthis; k++) {
                resultMat[i][j] += this->Matrix[i][k] * g1.Matrix[k][j];
            }
        }
    }

    Graph result;
    result.loadGraph(resultMat);
    return result;
}

// Compound division operator for scalar division
void Graph::operator/=(int num) {
    size_t size = this->getMatrix().size();
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            if (num != 0) {
                this->getMatrix()[i][j] /= num;
            }
        }
    }
}

// Overload for outputting a graph's adjacency matrix to an ostream
std::ostream& operator<<(std::ostream& os, const Graph& graph) {
    const auto& mat = graph.getMatrix();
    for (const auto& row : mat) {
        for (int val : row) {
            os << val << " ";
        }
        os << std::endl;
    }
    return os;
}

}
