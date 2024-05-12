    // 206971962 / kaufmanlinoy@gmail.com
    #include "Algorithms.hpp"
    #include <list>
    #include "Graph.hpp"
    #include <queue>

    using namespace std;
    using namespace ariel;

    int Algorithms::isConnected (const Graph &graph)
    {
    size_t Varticls =graph.size();
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
                    return 0;
                }
        }
        
        return 1; 
    }

    int Algorithms::isContainsCycle(const Graph &graph){
        vector<vector<int>> mat = graph.getMatrix();
        size_t numVertices = mat.size();
        vector<bool> visited (numVertices, false);
        vector<int> parent (numVertices, -1);

        stack<size_t> stack;
        //
        for(size_t i=0; i<numVertices;i++){
            if(!visited[i]){
                stack.push(i);
                while(!stack.empty())
                {
                    size_t current = stack.top();
                    stack.pop();

                    if (visited[current])
                    {
                    return 1;
                    }
                    visited[current]=true;

                    for (size_t neighbor : graph.getNeighbors(current))
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
        return 0;
    }

    string Algorithms::shortestPath (const Graph &graph, size_t start, size_t end){
        const vector<vector<int>> &mat = graph.getMatrix();
        size_t numVertices = mat.size();
        vector<vector<int>> adjacencyMatrix = graph.getMatrix();

        //chek if start and end is valid
        if(start >= numVertices || end >= numVertices)
            return "start or end invalid";

        
        vector<int> dist (numVertices,-1);
        vector<size_t> prev(numVertices,SIZE_MAX); //keep the prev place in the sortest path
        queue<size_t> queue;
        //start search from first place
        queue.push(start);
        dist[start]=0;

        while (!queue.empty())
        {
            size_t current = queue.front();
            queue.pop();


            for(size_t neighbor = 0; neighbor< numVertices;neighbor++){
                if (adjacencyMatrix[current][neighbor]!=0)
                {
                    if (dist[neighbor]==-1)
                    {
                        dist[neighbor]=dist[current]+1;
                        prev[neighbor]=current;
                        queue.push(neighbor);


                    }
                    
                }
                
            }
        }
        if(dist[end]==-1)
            return "-1";

        string path= to_string(end);
        size_t current=end;
        while (current!=start)
        {
            current=prev[current];
            path= to_string(current)+ "-->" + path;
        }
        return path;
    }

    string Algorithms::isBipartite(const Graph &graph){
        size_t num = graph.size();
        vector<size_t> colored(num,SIZE_MAX);//-1 not colored, 0 - colored 
        queue<size_t> queue;


        for(size_t i =0;i<num;i++){
            if (colored[i]==-1)
            {
                queue.push(i);
                colored[i]=0;
            }
            while (!queue.empty())
            {
                size_t current = queue.front();
                queue.pop();

                for (size_t neighbor : graph.getNeighbors(current))
                {
                    if (colored[neighbor]==-1)
                    {
                        colored[neighbor]=1-colored[current];//color neighbor diffrent color
                        queue.push(neighbor);
                    }
                    else if(colored[neighbor]==colored[current]){
                        return "0";
                    }
                }
                
            }
            
        }
        return "The graph is bipartite";
    }


    string Algorithms::negativeCycle(const Graph &graph){
        if(isContainsCycle(graph)==1)
            return "no negative cycle";
        size_t n = graph.size();
        const vector<vector<int>> &adjMat = graph.getMatrix();
        vector<int> dist (n,0);
        vector<int> prev (n,-1);
        size_t source = 0;
        //balman ford algo
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j< n; j++)
            {
                for (size_t k = 0; k< n; k++)
                {
                    if (adjMat[j][k]!=0)
                    {
                        if (dist[k]>dist[j]+adjMat[j][k])
                        {
                            dist[k]=dist[j]+adjMat[j][k];
                            prev[k]=j;
                        }
                        
                    }
                    
                }
                
            }
            
        }
        for(size_t j=0;j<n;j++){
            for (size_t k= 0; k < n; k++)
            {
                if (adjMat[j][k]!=0)
                {
                    if(dist[k]>dist[j]+adjMat[j][k]){
                        return "there is a negative cycle";
                    }
                }
                
            }
            
        }

    return "no negative cycle";
    }