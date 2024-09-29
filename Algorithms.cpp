// 206971962 / kaufmanlinoy@gmail.com

#include "Algorithms.hpp"
#include <list>
#include "Graph.hpp"
#include <queue>
#include <cstdint> // to handle MAX SIZE definitions

using namespace std;
using namespace ariel;

// Function to check if the graph is connected
int Algorithms::isConnected (const Graph &graph) {
    size_t Varticls = graph.size();  // Get the number of vertices in the graph
    vector<vector<int>> mat = graph.getMatrix();  // Get the adjacency matrix
    std::vector<bool> visited (Varticls, false);  // To track visited vertices
    std::list<size_t> queue;  // Queue for BFS traversal

    visited[0] = true;  // We start from node 0
    queue.push_back(0);  // Add node 0 to the queue

    // BFS 
    while (!queue.empty()) {
        size_t current = queue.front();
        queue.pop_front();

        // Traverse all adjacent vertices of the current node
        for (size_t i = 0; i < Varticls; i++) {
            if (mat[current][i] != 0 && !visited[i]) {  // If there is an edge and vertex is not visited
                visited[i] = true;
                queue.push_back(i);
            }
        }
    }

    // Check if all vertices were visited
    for (bool visit : visited) {
        if (!visit) {
            return 0;  // If any vertex is not visited, graph is not connected
        }
    }

    return 1;  // If all vertices were visited, graph is connected
}

// Function to check if the graph contains a cycle
int Algorithms::isContainsCycle(const Graph &graph) {
    vector<vector<int>> mat = graph.getMatrix();  // Get adjacency matrix
    size_t numVertices = mat.size();  // Number of vertices in the graph
    vector<bool> visited(numVertices, false);  // To track visited vertices
    vector<size_t> parent(numVertices, (size_t)-1);  // To store parent of each node in DFS

    stack<size_t> stack;  // Stack for DFS traversal

    // Perform DFS on all unvisited nodes
    for (size_t i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            stack.push(i);

            while (!stack.empty()) {
                size_t current = stack.top();
                stack.pop();

                // If we revisit an already visited node, a cycle exists
                if (visited[current]) {
                    return 1;  // Graph contains a cycle
                }

                visited[current] = true;

                // Traverse all adjacent vertices of the current node
                for (size_t neighbor : graph.getNeighbors(current)) {
                    if (neighbor != parent[current]) {
                        parent[neighbor] = current;  // Update parent of the neighbor
                        stack.push(neighbor);
                    }
                }
            }
        }
    }

    return 0;  // No cycle detected
}

// Function to find the shortest path between two vertices using BFS
string Algorithms::shortestPath (const Graph &graph, size_t start, size_t end) {
    const vector<vector<int>>& mat = graph.getMatrix();  // Get adjacency matrix
    size_t numVertices = mat.size();  // Number of vertices
    vector<vector<int>> adjacencyMatrix = graph.getMatrix();

    // Check if start and end vertices are valid
    if (start >= numVertices || end >= numVertices)
        return "start or end invalid";

    vector<int> dist(numVertices, -1);  // Distance from start vertex
    vector<size_t> prev(numVertices, SIZE_MAX);  // Previous node in the shortest path
    queue<size_t> queue;  // Queue for BFS
    queue.push(start);  // Start BFS from the start vertex
    dist[start] = 0;  // Distance to the start vertex is 0

    // BFS traversal
    while (!queue.empty()) {
        size_t current = queue.front();
        queue.pop();

        // Traverse all adjacent vertices
        for (size_t neighbor = 0; neighbor < numVertices; neighbor++) {
            if (adjacencyMatrix[current][neighbor] != 0) {  // If there is an edge
                if (dist[neighbor] == -1) {  // If the neighbor has not been visited
                    dist[neighbor] = dist[current] + 1;
                    prev[neighbor] = current;
                    queue.push(neighbor);
                }
            }
        }
    }

    if (dist[end] == -1)
        return "-1";  // If there is no path from start to end

    // Reconstruct the shortest path
    string path = to_string(end);
    size_t current = end;
    while (current != start) {
        current = prev[current];
        path = to_string(current) + "-->" + path;
    }

    return path;  // Return the shortest path as a string
}

// Function to check if the graph is bipartite
string Algorithms::isBipartite(const Graph &graph) {
    size_t num = graph.size();  // Number of vertices
    vector<size_t> colored(num, SIZE_MAX);  // To track colors of vertices, -1 means uncolored
    queue<size_t> queue;  // Queue for BFS traversal

    // Perform BFS for all uncolored nodes
    for (size_t i = 0; i < num; i++) {
        if (colored[i] == -1) {
            queue.push(i);
            colored[i] = 0;  // Color the node with color 0
        }

        while (!queue.empty()) {
            size_t current = queue.front();
            queue.pop();

            // Traverse all neighbors of the current node
            for (size_t neighbor : graph.getNeighbors(current)) {
                if (colored[neighbor] == -1) {  // If the neighbor is uncolored
                    colored[neighbor] = 1 - colored[current];  // Color neighbor with opposite color
                    queue.push(neighbor);
                } else if (colored[neighbor] == colored[current]) {
                    return "0";  // If neighbor has the same color, graph is not bipartite
                }
            }
        }
    }

    return "The graph is bipartite";  // Graph is bipartite
}

// Function to check for negative cycles using the Bellman-Ford algorithm
string Algorithms::negativeCycle(const Graph &graph) {
    if (isContainsCycle(graph) == 1)
        return "no negative cycle";  // Return if the graph contains a cycle

    size_t n = graph.size();  // Number of vertices
    const vector<vector<int>>& adjMat = graph.getMatrix();  // Get adjacency matrix
    vector<int> dist(n, 0);  // Distance to each vertex, initialized to 0
    vector<int> prev(n, -1);  // Previous node in the path
    size_t source = 0;  // Start from node 0

    // Bellman-Ford algorithm to detect negative cycles
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            for (size_t k = 0; k < n; k++) {
                if (adjMat[j][k] != 0) {  // If there is an edge
                    if (dist[k] > dist[j] + adjMat[j][k]) {  // If a shorter path is found
                        dist[k] = dist[j] + adjMat[j][k];
                        prev[k] = j;
                    }
                }
            }
        }
    }

    // Check for negative cycles
    for (size_t j = 0; j < n; j++) {
        for (size_t k = 0; k < n; k++) {
            if (adjMat[j][k] != 0) {
                if (dist[k] > dist[j] + adjMat[j][k]) {
                    return "there is a negative cycle";  // Negative cycle detected
                }
            }
        }
    }

    return "no negative cycle";  // No negative cycle found
}
