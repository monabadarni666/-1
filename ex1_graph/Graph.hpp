// graph.hpp
#ifndef GRAPH_HPP
#define GRAPH_HPP

namespace graph {

class Graph {
public:
    // This struct represents an edge in the adjacency list
    struct Edge {
        int destination;
        int weight;
        Edge* next;
        
        Edge(int dest, int w);
        ~Edge();
    };

    // Constructor and destructor
    Graph(int vertices);
    ~Graph();
    
    // Copy constructor and assignment operator
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);
    
    // Main graph operations
    void addEdge(int source, int dest, int weight = 1);
    void removeEdge(int source, int dest);
    void print_graph() const; 
    
    // Accessor methods
    int getNumVertices() const;
    Edge* getAdjList(int vertex) const;
    
private:
    Edge** adjacencyList; // Array of linked lists
    int numVertices;
};

} // namespace graph

#endif // GRAPH_HPP