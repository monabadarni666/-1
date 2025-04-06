// main.cpp
#include "Graph.hpp"
#include "Algorithms.hpp"
#include <iostream>

int main() {
    std::cout << "Testing Graph and Algorithms Implementation" << std::endl;
    std::cout << "=========================================" << std::endl << std::endl;
    
    try {
        // Create a graph with 6 vertices
        std::cout << "Creating a graph with 6 vertices" << std::endl;
        graph::Graph g(6);
        
        // Add edges
        std::cout << "\nAdding edges to the graph:" << std::endl;
        g.addEdge(0, 1, 4);
        g.addEdge(0, 2, 3);
        g.addEdge(1, 2, 5);
        g.addEdge(1, 3, 2);
        g.addEdge(2, 3, 7);
        g.addEdge(2, 4, 8);
        g.addEdge(3, 4, 6);
        g.addEdge(3, 5, 1);
        g.addEdge(4, 5, 9);
        
        // Print the graph
        std::cout << "\nOriginal graph:" << std::endl;
        g.print_graph();
        
        // Test BFS algorithm
        std::cout << "\nBFS traversal starting from vertex 0:" << std::endl;
        graph::Graph bfsTree = graph::Algorithms::bfs(g, 0);
        bfsTree.print_graph();
        
        // Test DFS algorithm
        std::cout << "\nDFS traversal starting from vertex 0:" << std::endl;
        graph::Graph dfsTree = graph::Algorithms::dfs(g, 0);
        dfsTree.print_graph();
        
        // Test Dijkstra's algorithm
        std::cout << "\nShortest paths from vertex 0 (Dijkstra's algorithm):" << std::endl;
        graph::Graph shortestPaths = graph::Algorithms::dijkstra(g, 0);
        shortestPaths.print_graph();
        
        // Test Prim's algorithm
        std::cout << "\nMinimum Spanning Tree (Prim's algorithm):" << std::endl;
        graph::Graph primMST = graph::Algorithms::prim(g);
        primMST.print_graph();
        
        // Test Kruskal's algorithm
        std::cout << "\nMinimum Spanning Tree (Kruskal's algorithm):" << std::endl;
        graph::Graph kruskalMST = graph::Algorithms::kruskal(g);
        kruskalMST.print_graph();
        
        // Demonstrate error handling
        std::cout << "\nTesting error handling - invalid source vertex:" << std::endl;
        try {
            graph::Algorithms::bfs(g, 10);
        } catch (const char* msg) {
            std::cout << "Exception caught: " << msg << std::endl;
        }
        
    } catch (const char* msg) {
        std::cout << "An exception occurred: " << msg << std::endl;
        return 1;
    }
    
    std::cout << "\nAll tests completed successfully!" << std::endl;
    return 0;
}