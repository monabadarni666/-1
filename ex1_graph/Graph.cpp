// graph.cpp
#include "Graph.hpp"
#include <iostream>

namespace graph {

// Edge struct implementation
Graph::Edge::Edge(int dest, int w) : destination(dest), weight(w), next(nullptr) {}

Graph::Edge::~Edge() {
    delete next; // Delete the chain of edges
}

// Graph constructors and destructor
Graph::Graph(int vertices) : numVertices(vertices) {
    if (vertices <= 0) {
        throw "Number of vertices must be positive";
    }
    
    adjacencyList = new Edge*[vertices];
    for (int i = 0; i < vertices; i++) {
        adjacencyList[i] = nullptr;
    }
}

Graph::~Graph() {
    for (int i = 0; i < numVertices; i++) {
        delete adjacencyList[i]; // This will trigger the Edge destructor chain
    }
    delete[] adjacencyList;
}

// Copy constructor
Graph::Graph(const Graph& other) : numVertices(other.numVertices) {
    adjacencyList = new Edge*[numVertices];
    
    for (int i = 0; i < numVertices; i++) {
        adjacencyList[i] = nullptr;
        
        // Deep copy the linked list
        Edge* current = other.adjacencyList[i];
        Edge** tail = &adjacencyList[i];
        
        while (current) {
            *tail = new Edge(current->destination, current->weight);
            tail = &((*tail)->next);
            current = current->next;
        }
    }
}

// Assignment operator
Graph& Graph::operator=(const Graph& other) {
    if (this != &other) {
        // Clean up existing data
        for (int i = 0; i < numVertices; i++) {
            delete adjacencyList[i];
        }
        delete[] adjacencyList;
        
        // Copy new data
        numVertices = other.numVertices;
        adjacencyList = new Edge*[numVertices];
        
        for (int i = 0; i < numVertices; i++) {
            adjacencyList[i] = nullptr;
            
            // Deep copy the linked list
            Edge* current = other.adjacencyList[i];
            Edge** tail = &adjacencyList[i];
            
            while (current) {
                *tail = new Edge(current->destination, current->weight);
                tail = &((*tail)->next);
                current = current->next;
            }
        }
    }
    return *this;
}

void Graph::addEdge(int source, int dest, int weight) {
    if (source < 0 || source >= numVertices || dest < 0 || dest >= numVertices) {
        throw "Vertex index out of range";
    }
    
    // Add edge from source to dest
    Edge* newEdge = new Edge(dest, weight);
    newEdge->next = adjacencyList[source];
    adjacencyList[source] = newEdge;
    
    // Since this is an undirected graph, add edge from dest to source as well
    Edge* newEdgeReverse = new Edge(source, weight);
    newEdgeReverse->next = adjacencyList[dest];
    adjacencyList[dest] = newEdgeReverse;
}

void Graph::removeEdge(int source, int dest) {
    if (source < 0 || source >= numVertices || dest < 0 || dest >= numVertices) {
        throw "Vertex index out of range";
    }
    
    bool edgeRemoved = false;
    
    // Remove edge from source to dest
    Edge** curr = &adjacencyList[source];
    while (*curr) {
        if ((*curr)->destination == dest) {
            Edge* temp = *curr;
            *curr = (*curr)->next;
            temp->next = nullptr; // Prevent deleting the entire chain
            delete temp;
            edgeRemoved = true;
            break;
        }
        curr = &((*curr)->next);
    }
    
    // Remove edge from dest to source
    curr = &adjacencyList[dest];
    while (*curr) {
        if ((*curr)->destination == source) {
            Edge* temp = *curr;
            *curr = (*curr)->next;
            temp->next = nullptr; // Prevent deleting the entire chain
            delete temp;
            edgeRemoved = true;
            break;
        }
        curr = &((*curr)->next);
    }
    
    if (!edgeRemoved) {
        throw "Edge does not exist";
    }
}

void Graph::print_graph() const {
    for (int i = 0; i < numVertices; i++) {
        std::cout << "Vertex " << i << " -> ";
        Edge* current = adjacencyList[i];
        while (current) {
            std::cout << "(" << current->destination << ", weight: " << current->weight << ") ";
            current = current->next;
        }
        std::cout << std::endl;
    }
}

int Graph::getNumVertices() const {
    return numVertices;
}

Graph::Edge* Graph::getAdjList(int vertex) const {
    if (vertex < 0 || vertex >= numVertices) {
        throw "Vertex index out of range";
    }
    return adjacencyList[vertex];
}

} // namespace graph