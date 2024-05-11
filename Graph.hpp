// 206971962 / kaufmanlinoy@gmail.com

#include <vector>
#include <utility>
using namespace std;
namespace ariel {
    class Graph {
    private:
        bool directed;
        std::vector<std::vector<int>> Matrix;


    public:
        bool isvalid(const std::vector<std::vector<int>> &mat);
        void loadGraph(const std::vector<std::vector<int>> &matrix);
        bool getDirected()const{return this->directed;}
        void printGraph() const;
        bool isDirected() const;
        size_t size() const{
            return this->Matrix.size();}
        std::size_t getNumberOfNodes() const;
        std::vector<std::pair<size_t , std::pair<size_t , int>>> getEdges() const;
        std::vector<std::size_t> getNeighbors(std::size_t node) const ;
        int getEdgeWeight(size_t ver1, size_t ver2) const ;
        bool isEdge(size_t from, size_t to) const {
            return Matrix[from][to] != 0;
        }
        std::vector<std::vector<int>> getMatrix() const {
            return Matrix;
        }
    };
    using StartNode = size_t;
}