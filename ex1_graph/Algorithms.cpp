// algorithms.cpp
#include "Algorithms.hpp"
#include "Utils.hpp"

// Maximum possible integer value (to represent infinity)
const int INT_MAX = 2147483647;

namespace graph {

// BFS algorithm implementation
Graph Algorithms::bfs(const Graph& g, int source) {
    int numVertices = g.getNumVertices();
    
    if (source < 0 || source >= numVertices) {
        throw "Source vertex out of range";
    }
    
    // Create a new graph for the BFS tree
    Graph result(numVertices);
    
    // Array to mark visited vertices
    bool* visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
    }
    
    // Create a queue for BFS
    Queue queue;
    
    // Mark source as visited and enqueue it
    visited[source] = true;
    queue.enqueue(source);
    
    while (!queue.isEmpty()) {
        // Dequeue a vertex
        int current = queue.dequeue();
        
        // Get all adjacent vertices
        Graph::Edge* edge = g.getAdjList(current);
        while (edge != nullptr) {
            int adjacent = edge->destination;
            
            // If not visited, mark as visited and enqueue
            if (!visited[adjacent]) {
                visited[adjacent] = true;
                queue.enqueue(adjacent);
                
                // Add edge to BFS tree
                result.addEdge(current, adjacent, edge->weight);
            }
            
            edge = edge->next;
        }
    }
    
    delete[] visited;
    return result;
}

// DFS algorithm implementation
Graph Algorithms::dfs(const Graph& g, int source) {
    int numVertices = g.getNumVertices();
    
    if (source < 0 || source >= numVertices) {
        throw "Source vertex out of range";
    }
    
    // Create a new graph for the DFS tree/forest
    Graph result(numVertices);
    
    // Array to mark visited vertices
    bool* visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
    }
    
    // Call the recursive DFS function
    dfsVisit(g, source, visited, result);
    
    delete[] visited;
    return result;
}

// Helper method for DFS
void Algorithms::dfsVisit(const Graph& g, int vertex, bool* visited, Graph& result) {
    visited[vertex] = true;
    
    // Explore all adjacent vertices
    Graph::Edge* edge = g.getAdjList(vertex);
    while (edge != nullptr) {
        int adjacent = edge->destination;
        
        // If not visited, visit and add edge to DFS tree
        if (!visited[adjacent]) {
            result.addEdge(vertex, adjacent, edge->weight);
            dfsVisit(g, adjacent, visited, result);
        }
        
        edge = edge->next;
    }
}

// Dijkstra's algorithm implementation
Graph Algorithms::dijkstra(const Graph& g, int source) {
    int numVertices = g.getNumVertices();
    
    if (source < 0 || source >= numVertices) {
        throw "Source vertex out of range";
    }
    
    // Create a new graph for the shortest paths tree
    Graph result(numVertices);
    
    // Distance array to store shortest path
    int* distance = new int[numVertices];
    
    // Parent array to store the shortest path tree
    int* parent = new int[numVertices];
    
    // Initialize distance and parent arrays
    for (int i = 0; i < numVertices; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
    }
    
    // Distance to source is 0
    distance[source] = 0;
    
    // Create a priority queue
    PriorityQueue pq(numVertices);
    
    // Insert all vertices with their distances
    for (int i = 0; i < numVertices; i++) {
        pq.insert(i, distance[i]);
    }
    
    // Process all vertices
    while (!pq.isEmpty()) {
        int u = pq.extractMin();
        
        // Process all adjacent vertices of u
        Graph::Edge* edge = g.getAdjList(u);
        while (edge != nullptr) {
            int v = edge->destination;
            int weight = edge->weight;
            
            // If there is a shorter path to v through u
            if (pq.inQueue(v) && distance[u] != INT_MAX && 
                distance[u] + weight < distance[v]) {
                
                // Update distance and parent
                distance[v] = distance[u] + weight;
                parent[v] = u;
                
                // Update priority queue
                pq.decreaseKey(v, distance[v]);
            }
            
            edge = edge->next;
        }
    }
    
    // Build the shortest path tree
    for (int i = 0; i < numVertices; i++) {
        if (i != source && parent[i] != -1) {
            // Find the weight of the edge from parent[i] to i
            int weight = 0;
            Graph::Edge* edge = g.getAdjList(parent[i]);
            while (edge != nullptr) {
                if (edge->destination == i) {
                    weight = edge->weight;
                    break;
                }
                edge = edge->next;
            }
            
            result.addEdge(parent[i], i, weight);
        }
    }
    
    delete[] distance;
    delete[] parent;
    
    return result;
}

// Prim's algorithm implementation
Graph Algorithms::prim(const Graph& g) {
    int numVertices = g.getNumVertices();
    
    // Create a new graph for the MST
    Graph result(numVertices);
    
    // Array to store key values
    int* key = new int[numVertices];
    
    // Array to store MST
    int* parent = new int[numVertices];
    
    // Initialize keys as INFINITE and parent as -1
    for (int i = 0; i < numVertices; i++) {
        key[i] = INT_MAX;
        parent[i] = -1;
    }
    
    // Include first vertex in MST, set its key to 0
    key[0] = 0;
    
    // Create a priority queue
    PriorityQueue pq(numVertices);
    
    // Insert all vertices
    for (int i = 0; i < numVertices; i++) {
        pq.insert(i, key[i]);
    }
    
    // Process all vertices
    while (!pq.isEmpty()) {
        int u = pq.extractMin();
        
        // Process all adjacent vertices
        Graph::Edge* edge = g.getAdjList(u);
        while (edge != nullptr) {
            int v = edge->destination;
            int weight = edge->weight;
            
            // If v is not yet included in MST and weight of u-v is less than key of v
            if (pq.inQueue(v) && weight < key[v]) {
                // Update key and parent
                key[v] = weight;
                parent[v] = u;
                
                // Update priority queue
                pq.decreaseKey(v, key[v]);
            }
            
            edge = edge->next;
        }
    }
    
    // Build the MST
    for (int i = 1; i < numVertices; i++) {
        if (parent[i] != -1) {
            result.addEdge(parent[i], i, key[i]);
        }
    }
    
    delete[] key;
    delete[] parent;
    
    return result;
}

// Kruskal's algorithm implementation
Graph Algorithms::kruskal(const Graph& g) {
    int numVertices = g.getNumVertices();
    
    // Create a new graph for the MST
    Graph result(numVertices);
    
    // Create a structure to represent an edge
    struct Edge {
        int src, dest, weight;
        
        Edge() : src(0), dest(0), weight(0) {}
        Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
    };
    
    // Create an array to store all edges
    int maxEdges = numVertices * (numVertices - 1) / 2; // Maximum possible edges
    Edge* edges = new Edge[maxEdges];
    int edgeCount = 0;
    
    // Collect all edges from the graph
    for (int i = 0; i < numVertices; i++) {
        Graph::Edge* edge = g.getAdjList(i);
        while (edge != nullptr) {
            if (i < edge->destination) { // To avoid duplicates in undirected graph
                edges[edgeCount++] = Edge(i, edge->destination, edge->weight);
            }
            edge = edge->next;
        }
    }
    
    // Sort edges by weight (bubble sort for simplicity)
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
    
    // Create a Union-Find data structure
    UnionFind uf(numVertices);
    
    // Process edges in ascending order of weight
    for (int i = 0; i < edgeCount; i++) {
        int src = edges[i].src;
        int dest = edges[i].dest;
        
        // If including this edge doesn't cause a cycle
        if (!uf.connected(src, dest)) {
            // Add the edge to the MST
            result.addEdge(src, dest, edges[i].weight);
            
            // Union the sets
            uf.unite(src, dest);
        }
    }
    
    delete[] edges;
    
    return result;
}

} // namespace graph