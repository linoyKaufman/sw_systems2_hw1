// 206971962 / kaufmanlinoy@gmail.com
#include <Algorithms.hpp>
#include <list>
#include "Graph.hpp"

using namespace std;
using namespace ariel;

int Algorithms::isConnected (const Graph &graph)
{
   int Varticls =graph.size();
   vector<vector<int>> mat = graph.getMatrix();
   std::vector<bool> visited (Varticls,false);
   std::list<size_t> queue;

   visited[0]=true; // we start from node 0
   queue.push_back(0);

   while (!queue.empty()){
    size_t current = queue.front();
    queue.pop_front();
   
        for(size_t i=0; i<Varticls ;i++)
        {
            if(mat[current][i]!=0 && !visited[i]){
                visited[i]=true;
                queue.push_back(i);
                }
        }
            
    }
    for (bool visit : visited){
            if(!visit){
                return false;
            }
    }
    
    return true; 
}

bool Algorithms::isContainsCycle(const Graph &graph){
    vector<vector<int>> mat = graph.getMatrix();
    int numVertices = mat.size();
    vector<bool> visited (numVertices, false);
    vector<int> parent (numVertices, -1);

    stack<int> stack;
    //
    for(int i=0; i<numVertices;i++){
        if(!visited[i]){
            stack.push(i);
            while(!stack.empty())
            {
                int current = stack.top();
                stack.pop();

                 if (visited[current])
                {
                   return true;
                }
                visited[current]=true;

                for (int neighbor : graph.getNeighbors(current))
                {
                   if (neighbor!= parent[current])
                   {
                     parent[neighbor]=current;
                     stack.push(neighbor);
                   }
                   
                }
                
            
            }

           
            
        }

    }
    return false;
}