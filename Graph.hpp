// 206971962 / kaufmanlinoy@gmail.com
#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <vector>
#include <utility>
using namespace std;
namespace ariel {
    class Graph {
    private:
        bool directed;
        std::vector<std::vector<int>> Matrix;


    public:
  
    Graph() noexcept; // הגדרת בנאי מוחלט עם noexcept
    ~Graph() noexcept; // כאן אתה יכול להוסיף את noexcept גם להרחבה של ההריסה, אם רק היא לא גרם לך בעיה אחרת
        bool isvalid(const std::vector<std::vector<int>> &mat);
        void loadGraph(const std::vector<std::vector<int>> &matrix);
        void printGraph() const;
        size_t size() const{
            return this->Matrix.size();}
        std::vector<std::pair<size_t , std::pair<size_t , int>>> getEdges() const;
        std::vector<std::size_t> getNeighbors(std::size_t node) const ;
        bool isEdge(size_t from, size_t to) const {
            return Matrix[from][to] != 0;
        }
        std::vector<std::vector<int>> getMatrix() const {
            return Matrix;
        }
    };
    using StartNode = size_t;
}
#endif