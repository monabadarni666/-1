// tests.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Graph.hpp"
#include "Algorithms.hpp"
#include "Utils.hpp"
#include <iostream>

// Helper function to count edges in a graph
int countEdges(const graph::Graph& g) {
    int count = 0;
    int numVertices = g.getNumVertices();
    
    for (int i = 0; i < numVertices; i++) {
        graph::Graph::Edge* edge = g.getAdjList(i);
        while (edge) {
            if (i < edge->destination) { // Count each edge only once
                count++;
            }
            edge = edge->next;
        }
    }
    
    return count;
}

// Helper function to calculate total weight of a graph
int calculateTotalWeight(const graph::Graph& g) {
    int totalWeight = 0;
    int numVertices = g.getNumVertices();
    
    for (int i = 0; i < numVertices; i++) {
        graph::Graph::Edge* edge = g.getAdjList(i);
        while (edge) {
            if (i < edge->destination) { // Count each edge weight only once
                totalWeight += edge->weight;
            }
            edge = edge->next;
        }
    }
    
    return totalWeight;
}

// Helper function to check if an edge exists in a graph
bool edgeExists(const graph::Graph& g, int source, int dest) {
    graph::Graph::Edge* edge = g.getAdjList(source);
    while (edge) {
        if (edge->destination == dest) {
            return true;
        }
        edge = edge->next;
    }
    return false;
}

// Helper function to get the weight of an edge
int getEdgeWeight(const graph::Graph& g, int source, int dest) {
    graph::Graph::Edge* edge = g.getAdjList(source);
    while (edge) {
        if (edge->destination == dest) {
            return edge->weight;
        }
        edge = edge->next;
    }
    return -1; // Edge not found
}

// Helper function to check if at least one of multiple edges exists
bool eitherEdgeExists(const graph::Graph& g, int src1, int dest1, int src2, int dest2) {
    return edgeExists(g, src1, dest1) || edgeExists(g, src2, dest2);
}

// Helper function to check if a graph is connected
bool isGraphConnected(const graph::Graph& g) {
    int numVertices = g.getNumVertices();
    if (numVertices == 0) return true;
    
    // Use BFS to check if all vertices are reachable from vertex 0
    bool* visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
    }
    
    // BFS
    graph::Queue queue;
    queue.enqueue(0);
    visited[0] = true;
    
    while (!queue.isEmpty()) {
        int current = queue.dequeue();
        graph::Graph::Edge* edge = g.getAdjList(current);
        
        while (edge) {
            int dest = edge->destination;
            if (!visited[dest]) {
                visited[dest] = true;
                queue.enqueue(dest);
            }
            edge = edge->next;
        }
    }
    
    // Check if all vertices were visited
    bool allVisited = true;
    for (int i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            allVisited = false;
            break;
        }
    }
    
    delete[] visited;
    return allVisited;
}

TEST_CASE("Graph construction and basic operations") {
    graph::Graph g(5);
    
    SUBCASE("Initial graph should be empty") {
        for (int i = 0; i < 5; i++) {
            CHECK(g.getAdjList(i) == nullptr);
        }
    }
    
    SUBCASE("Adding and checking edges") {
        g.addEdge(0, 1, 2);
        g.addEdge(0, 2, 5);
        g.addEdge(1, 3, 7);
        g.addEdge(2, 3, 1);
        g.addEdge(2, 4, 8);
        g.addEdge(3, 4, 4);
        
        // Check edge existence
        CHECK(edgeExists(g, 0, 1));
        CHECK(edgeExists(g, 1, 0)); // Check the reverse direction
        CHECK(edgeExists(g, 0, 2));
        CHECK(edgeExists(g, 2, 3));
        CHECK_FALSE(edgeExists(g, 0, 3));
        CHECK_FALSE(edgeExists(g, 1, 4));
        
        // Check edge weights
        CHECK(getEdgeWeight(g, 0, 1) == 2);
        CHECK(getEdgeWeight(g, 0, 2) == 5);
        CHECK(getEdgeWeight(g, 2, 3) == 1);
        CHECK(getEdgeWeight(g, 3, 4) == 4);
    }
    
    SUBCASE("Removing edges") {
        g.addEdge(0, 1, 2);
        g.addEdge(0, 2, 5);
        g.addEdge(1, 3, 7);
        
        g.removeEdge(0, 1);
        CHECK_FALSE(edgeExists(g, 0, 1));
        CHECK_FALSE(edgeExists(g, 1, 0)); // Check the reverse direction
        
        CHECK_THROWS_WITH(g.removeEdge(0, 3), "Edge does not exist");
    }
    
    SUBCASE("Copy constructor and assignment operator") {
        g.addEdge(0, 1, 2);
        g.addEdge(0, 2, 5);
        g.addEdge(1, 3, 7);
        
        // Test copy constructor
        graph::Graph g2(g);
        CHECK(edgeExists(g2, 0, 1));
        CHECK(getEdgeWeight(g2, 0, 1) == 2);
        CHECK(edgeExists(g2, 0, 2));
        CHECK(edgeExists(g2, 1, 3));
        
        // Test assignment operator
        graph::Graph g3(3);
        g3 = g;
        CHECK(edgeExists(g3, 0, 1));
        CHECK(getEdgeWeight(g3, 0, 1) == 2);
        CHECK(edgeExists(g3, 0, 2));
        CHECK(edgeExists(g3, 1, 3));
    }
}

TEST_CASE("Data structures - Queue") {
    graph::Queue queue;
    
    SUBCASE("Initial queue should be empty") {
        CHECK(queue.isEmpty());
        CHECK_THROWS_WITH(queue.dequeue(), "Queue is empty");
    }
    
    SUBCASE("Enqueue and dequeue operations") {
        queue.enqueue(1);
        queue.enqueue(2);
        queue.enqueue(3);
        
        CHECK_FALSE(queue.isEmpty());
        CHECK(queue.dequeue() == 1);
        CHECK(queue.dequeue() == 2);
        CHECK(queue.dequeue() == 3);
        CHECK(queue.isEmpty());
    }
    
    SUBCASE("FIFO behavior") {
        for (int i = 0; i < 10; i++) {
            queue.enqueue(i);
        }
        
        for (int i = 0; i < 10; i++) {
            CHECK(queue.dequeue() == i);
        }
        
        CHECK(queue.isEmpty());
    }
}

TEST_CASE("Data structures - Priority Queue") {
    graph::PriorityQueue pq(5);
    
    SUBCASE("Initial priority queue should be empty") {
        CHECK(pq.isEmpty());
        CHECK_THROWS_WITH(pq.extractMin(), "Priority queue is empty");
    }
    
    SUBCASE("Insert and extractMin operations") {
        pq.insert(0, 10);
        pq.insert(1, 5);
        pq.insert(2, 15);
        
        CHECK_FALSE(pq.isEmpty());
        CHECK(pq.extractMin() == 1); // Should extract vertex 1 with priority 5
        CHECK(pq.extractMin() == 0); // Should extract vertex 0 with priority 10
        CHECK(pq.extractMin() == 2); // Should extract vertex 2 with priority 15
        CHECK(pq.isEmpty());
    }
    
    SUBCASE("DecreaseKey operation") {
        pq.insert(0, 10);
        pq.insert(1, 20);
        pq.insert(2, 30);
        
        pq.decreaseKey(2, 5); // Decrease priority of vertex 2 to 5
        
        CHECK(pq.extractMin() == 2); // Should now be the minimum
        CHECK(pq.extractMin() == 0);
        CHECK(pq.extractMin() == 1);
    }
    
    SUBCASE("Invalid operations should throw") {
        pq.insert(0, 10);
        
        CHECK_THROWS_WITH(pq.decreaseKey(1, 5), "Vertex not in priority queue");
        CHECK_THROWS_WITH(pq.decreaseKey(0, 20), "New priority is greater than current priority");
    }
}

TEST_CASE("Data structures - Union-Find") {
    graph::UnionFind uf(5);
    
    SUBCASE("Initial sets should be disjoint") {
        for (int i = 0; i < 5; i++) {
            CHECK(uf.find(i) == i);
        }
        
        for (int i = 0; i < 4; i++) {
            CHECK_FALSE(uf.connected(i, i+1));
        }
    }
    
    SUBCASE("Union and find operations") {
        uf.unite(0, 1);
        CHECK(uf.connected(0, 1));
        
        uf.unite(2, 3);
        CHECK(uf.connected(2, 3));
        CHECK_FALSE(uf.connected(0, 2));
        
        uf.unite(0, 3);
        CHECK(uf.connected(0, 2));
        CHECK(uf.connected(1, 3));
        
        uf.unite(4, 0);
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                CHECK(uf.connected(i, j));
            }
        }
    }
    
    SUBCASE("Path compression") {
        // Create a chain of unions
        for (int i = 0; i < 4; i++) {
            uf.unite(i, i+1);
        }
        
        // After finding, all should point to the same root
        int root = uf.find(0);
        for (int i = 1; i < 5; i++) {
            CHECK(uf.find(i) == root);
        }
    }
}

TEST_CASE("BFS algorithm") {
    graph::Graph g(6);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 6);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 5, 1);
    g.addEdge(4, 5, 8);
    
    std::cout << "\n----- Original graph for BFS test -----\n";
    g.print_graph();
    
    graph::Graph bfsTree = graph::Algorithms::bfs(g, 0);
    
    std::cout << "\n----- BFS tree from vertex 0 -----\n";
    bfsTree.print_graph();
    
    SUBCASE("BFS tree properties") {
        // For an undirected graph, check that the number of undirected edges is correct
        CHECK(countEdges(bfsTree) == 5); // 6 vertices should have 5 edges in a tree
        
        // Check if BFS tree is connected
        CHECK(isGraphConnected(bfsTree));
        
        // BFS from 0 should have direct edges from 0 to 1 and 0 to 2
        CHECK(edgeExists(bfsTree, 0, 1));
        CHECK(edgeExists(bfsTree, 0, 2));
        
        // Level 1 vertices should connect to their children - test one edge at a time
        bool hasEdge1_3 = edgeExists(bfsTree, 1, 3);
        bool hasEdge2_3 = edgeExists(bfsTree, 2, 3);
        CHECK((hasEdge1_3 || hasEdge2_3)); // At least one must exist
        
        CHECK(edgeExists(bfsTree, 2, 4));
        
        // Level 2 vertices should connect to their children - test one edge at a time
        bool hasEdge3_5 = edgeExists(bfsTree, 3, 5);
        bool hasEdge4_5 = edgeExists(bfsTree, 4, 5);
        CHECK((hasEdge3_5 || hasEdge4_5)); // At least one must exist
    }
    
    SUBCASE("BFS from different source") {
        graph::Graph bfsTree2 = graph::Algorithms::bfs(g, 3);
        std::cout << "\n----- BFS tree from vertex 3 -----\n";
        bfsTree2.print_graph();
        
        // Check level 0 connections
        CHECK(edgeExists(bfsTree2, 3, 1));
        CHECK(edgeExists(bfsTree2, 3, 2));
        CHECK(edgeExists(bfsTree2, 3, 5));
    }
}

TEST_CASE("DFS algorithm") {
    graph::Graph g(6);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 6);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 5, 1);
    g.addEdge(4, 5, 8);
    
    std::cout << "\n----- Original graph for DFS test -----\n";
    g.print_graph();
    
    graph::Graph dfsTree = graph::Algorithms::dfs(g, 0);
    
    std::cout << "\n----- DFS tree from vertex 0 -----\n";
    dfsTree.print_graph();
    
    SUBCASE("DFS tree properties for undirected graph") {
        // For an undirected graph representation, a DFS tree should have n-1 edges
        CHECK(countEdges(dfsTree) == 5); // 6 vertices should have 5 edges in a tree
        
        // Check if DFS tree is connected
        CHECK(isGraphConnected(dfsTree));
        
        // Since this is an undirected graph implementation, we cannot check for 
        // directed tree properties like "one incoming edge per vertex"
        
        // Instead, verify that the tree connects all vertices
        bool visited[6] = {false, false, false, false, false, false};
        visited[0] = true; // Mark root as visited
        
        // Simple BFS to check connectivity
        graph::Queue queue;
        queue.enqueue(0);
        
        while (!queue.isEmpty()) {
            int v = queue.dequeue();
            graph::Graph::Edge* edge = dfsTree.getAdjList(v);
            
            while (edge) {
                if (!visited[edge->destination]) {
                    visited[edge->destination] = true;
                    queue.enqueue(edge->destination);
                }
                edge = edge->next;
            }
        }
        
        // All vertices should be reachable
        for (int i = 0; i < 6; i++) {
            CHECK(visited[i]);
        }
    }
    
    SUBCASE("DFS from different source") {
        graph::Graph dfsTree2 = graph::Algorithms::dfs(g, 3);
        std::cout << "\n----- DFS tree from vertex 3 -----\n";
        dfsTree2.print_graph();
        
        // Check that vertex 3 is connected to at least one other vertex
        bool connected_to_1 = edgeExists(dfsTree2, 3, 1);
        bool connected_to_2 = edgeExists(dfsTree2, 3, 2);
        bool connected_to_5 = edgeExists(dfsTree2, 3, 5);
        
        CHECK((connected_to_1 || connected_to_2 || connected_to_5));
        
        // Check if the DFS tree is connected
        CHECK(isGraphConnected(dfsTree2));
    }
}
TEST_CASE("Dijkstra algorithm") {
    graph::Graph g(6);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 8);
    g.addEdge(2, 4, 10);
    g.addEdge(3, 4, 2);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 3);
    
    std::cout << "\n----- Original graph for Dijkstra test -----\n";
    g.print_graph();
    
    graph::Graph shortestPaths = graph::Algorithms::dijkstra(g, 0);
    
    std::cout << "\n----- Shortest paths tree from vertex 0 (Dijkstra) -----\n";
    shortestPaths.print_graph();
    
    SUBCASE("Shortest path tree properties") {
        // A tree with 6 vertices should have 5 edges
        CHECK(countEdges(shortestPaths) == 5);
        
        // Check if the tree is connected
        CHECK(isGraphConnected(shortestPaths));
        
        // Based on the actual implementation output, the shortest path 
        // from 0 to 1 is through 2, not direct
        CHECK(edgeExists(shortestPaths, 0, 2));
        CHECK(edgeExists(shortestPaths, 2, 1));
        
        // Shortest path from 0 to 2 is direct
        CHECK(edgeExists(shortestPaths, 0, 2));
        
        // Shortest path from 0 to 3 is 0->2->1->3
        CHECK(edgeExists(shortestPaths, 1, 3));
        
        // Shortest path from 0 to 4 is 0->2->1->3->4
        CHECK(edgeExists(shortestPaths, 3, 4));
        
        // Shortest path from 0 to 5 is 0->2->1->3->4->5
        CHECK(edgeExists(shortestPaths, 4, 5));
    }
    
    SUBCASE("Dijkstra from different source") {
        graph::Graph shortestPaths2 = graph::Algorithms::dijkstra(g, 3);
        std::cout << "\n----- Shortest paths tree from vertex 3 (Dijkstra) -----\n";
        shortestPaths2.print_graph();
        
        // Check direct connections from source
        CHECK(edgeExists(shortestPaths2, 3, 4));
        
        // Path from 3 to 5 should be direct or through 4
        bool direct_to_5 = edgeExists(shortestPaths2, 3, 5);
        bool through_4 = edgeExists(shortestPaths2, 4, 5);
        CHECK((direct_to_5 || through_4));
    }
}

TEST_CASE("Prim algorithm") {
    graph::Graph g(6);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(2, 4, 5);
    g.addEdge(3, 4, 7);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 8);
    
    std::cout << "\n----- Original graph for Prim's MST test -----\n";
    g.print_graph();
    
    graph::Graph mst = graph::Algorithms::prim(g);
    
    std::cout << "\n----- Minimum Spanning Tree (Prim) -----\n";
    mst.print_graph();
    
    SUBCASE("MST properties") {
        // MST of connected graph with 6 vertices should have 5 edges
        CHECK(countEdges(mst) == 5);
        
        // Check if MST is connected
        CHECK(isGraphConnected(mst));
        
        // Calculate total weight of the MST
        int totalWeight = calculateTotalWeight(mst);
        std::cout << "Total MST weight (Prim): " << totalWeight << std::endl;
        
        // MST should include the edge with weight 1 between vertices 1 and 2
        CHECK(edgeExists(mst, 1, 2));
        CHECK(getEdgeWeight(mst, 1, 2) == 1);
        
        // MST should include the edge with weight 2
        CHECK(edgeExists(mst, 1, 3));
        CHECK(getEdgeWeight(mst, 1, 3) == 2);
        
        // Total weight of MST should be 16 (1+2+3+5+6 = 16)
        CHECK(totalWeight == 17);
        
        // Verify minimality by comparing with a non-minimal spanning tree
        graph::Graph nonMinimalST(6);
        nonMinimalST.addEdge(0, 1, 4);  // Weight 4 instead of 3 between 0-2
        nonMinimalST.addEdge(1, 2, 1);
        nonMinimalST.addEdge(1, 3, 2);
        nonMinimalST.addEdge(3, 4, 7);  // Weight 7 instead of 5 between 2-4
        nonMinimalST.addEdge(4, 5, 8);
        
        // Check that our MST has lower total weight
        int nonMinimalWeight = calculateTotalWeight(nonMinimalST);
        std::cout << "Non-minimal spanning tree weight: " << nonMinimalWeight << std::endl;
        CHECK(totalWeight < nonMinimalWeight);
    }
}

TEST_CASE("Kruskal algorithm") {
    graph::Graph g(6);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(2, 4, 5);
    g.addEdge(3, 4, 7);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 8);
    
    std::cout << "\n----- Original graph for Kruskal's MST test -----\n";
    g.print_graph();
    
    graph::Graph mst = graph::Algorithms::kruskal(g);
    
    std::cout << "\n----- Minimum Spanning Tree (Kruskal) -----\n";
    mst.print_graph();
    
    SUBCASE("MST properties") {
        // MST of connected graph with 6 vertices should have 5 edges
        CHECK(countEdges(mst) == 5);
        
        // Check if MST is connected
        CHECK(isGraphConnected(mst));
        
        // Calculate total weight of the MST
        int totalWeight = calculateTotalWeight(mst);
        std::cout << "Total MST weight (Kruskal): " << totalWeight << std::endl;
        
        // Kruskal should include the minimum weight edges that don't form cycles
        CHECK(edgeExists(mst, 1, 2));
        CHECK(getEdgeWeight(mst, 1, 2) == 1);
        
        CHECK(edgeExists(mst, 1, 3));
        CHECK(getEdgeWeight(mst, 1, 3) == 2);
        
        CHECK(edgeExists(mst, 0, 2));
        CHECK(getEdgeWeight(mst, 0, 2) == 3);
        
        // Total weight of MST should be 17 (1+2+3+5+6 = 17)
        CHECK(totalWeight == 17);
        
        // Create a higher weight spanning tree to verify minimality
        graph::Graph heavierST(6);
        heavierST.addEdge(0, 1, 4);
        heavierST.addEdge(1, 2, 1);
        heavierST.addEdge(1, 3, 2);
        heavierST.addEdge(2, 4, 5);
        heavierST.addEdge(3, 5, 6);  // Use edge 3-5 with weight 6 instead of 4-5 with weight 3
        
        int heavierSTWeight = calculateTotalWeight(heavierST);
        std::cout << "Heavier spanning tree weight: " << heavierSTWeight << std::endl;
        CHECK(totalWeight < heavierSTWeight);
    }
    
    SUBCASE("Compare Prim and Kruskal MSTs") {
        graph::Graph primMST = graph::Algorithms::prim(g);
        graph::Graph kruskalMST = graph::Algorithms::kruskal(g);
        
        int primWeight = calculateTotalWeight(primMST);
        int kruskalWeight = calculateTotalWeight(kruskalMST);
        
        // Both algorithms should yield MSTs with the same total weight
        CHECK(primWeight == kruskalWeight);
        
        // Both MSTs should be connected
        CHECK(isGraphConnected(primMST));
        CHECK(isGraphConnected(kruskalMST));
    }
}

TEST_CASE("Edge cases and error handling") {
    SUBCASE("Creating graph with invalid size") {
        CHECK_THROWS_WITH(graph::Graph(-1), "Number of vertices must be positive");
        CHECK_THROWS_WITH(graph::Graph(0), "Number of vertices must be positive");
    }
    
    SUBCASE("Adding edge with invalid vertex") {
        graph::Graph g(5);
        CHECK_THROWS_WITH(g.addEdge(-1, 2), "Vertex index out of range");
        CHECK_THROWS_WITH(g.addEdge(1, 5), "Vertex index out of range");
    }
    
    SUBCASE("Algorithm with invalid source") {
        graph::Graph g(5);
        CHECK_THROWS_WITH(graph::Algorithms::bfs(g, -1), "Source vertex out of range");
        CHECK_THROWS_WITH(graph::Algorithms::bfs(g, 5), "Source vertex out of range");
        CHECK_THROWS_WITH(graph::Algorithms::dfs(g, -1), "Source vertex out of range");
        CHECK_THROWS_WITH(graph::Algorithms::dijkstra(g, 5), "Source vertex out of range");
    }
    
    SUBCASE("Algorithms on disconnected graph") {
        graph::Graph g(6);
        g.addEdge(0, 1);
        g.addEdge(1, 2);
        // No edges to vertices 3, 4, 5
        
        // BFS from vertex 0 should only reach vertices 0, 1, 2
        graph::Graph bfsTree = graph::Algorithms::bfs(g, 0);
        CHECK(countEdges(bfsTree) == 2); // Only 2 edges in the tree
        CHECK(edgeExists(bfsTree, 0, 1));
        CHECK(edgeExists(bfsTree, 1, 2));
        CHECK_FALSE(edgeExists(bfsTree, 0, 3));
        CHECK_FALSE(edgeExists(bfsTree, 0, 4));
        CHECK_FALSE(edgeExists(bfsTree, 0, 5));
        
        // MST should connect only the connected components
        graph::Graph mst = graph::Algorithms::prim(g);
        CHECK(countEdges(mst) == 2); // Only 2 edges in the MST
    }
}
TEST_CASE("Complex graph scenarios") {
    // Create a more complex graph to test algorithm behavior
    SUBCASE("Graph with multiple equal weight paths") {
        graph::Graph g(7);
        g.addEdge(0, 1, 5);
        g.addEdge(0, 2, 5);
        g.addEdge(1, 3, 3);
        g.addEdge(2, 3, 3);
        g.addEdge(3, 4, 2);
        g.addEdge(3, 5, 2);
        g.addEdge(4, 6, 4);
        g.addEdge(5, 6, 4);
        
        std::cout << "\n----- Complex graph with equal weight paths -----\n";
        g.print_graph();
        
        graph::Graph dijkstraTree = graph::Algorithms::dijkstra(g, 0);
        std::cout << "\n----- Dijkstra shortest paths tree -----\n";
        dijkstraTree.print_graph();
        
        // Verify correct shortest path lengths
        // Path from 0 to 6 should be length 11 (0->1->3->4->6 or 0->2->3->5->6)
        CHECK(countEdges(dijkstraTree) == 6); // 7 vertices - 1 = 6 edges in tree
        CHECK(isGraphConnected(dijkstraTree));
    }
    
    SUBCASE("Graph with cycle") {
        graph::Graph g(4);
        g.addEdge(0, 1, 1);
        g.addEdge(1, 2, 2);
        g.addEdge(2, 3, 3);
        g.addEdge(3, 0, 4);
        
        std::cout << "\n----- Simple cycle graph -----\n";
        g.print_graph();
        
        graph::Graph mstPrim = graph::Algorithms::prim(g);
        graph::Graph mstKruskal = graph::Algorithms::kruskal(g);
        
        std::cout << "\n----- MST using Prim -----\n";
        mstPrim.print_graph();
        
        std::cout << "\n----- MST using Kruskal -----\n";
        mstKruskal.print_graph();
        
        // Verify both MSTs have 3 edges for a connected graph with 4 vertices
        CHECK(countEdges(mstPrim) == 3);
        CHECK(countEdges(mstKruskal) == 3);
        
        // Check if MSTs are connected
        CHECK(isGraphConnected(mstPrim));
        CHECK(isGraphConnected(mstKruskal));
        
        // Verify total weights are equal
        int primWeight = calculateTotalWeight(mstPrim);
        int kruskalWeight = calculateTotalWeight(mstKruskal);
        CHECK(primWeight == kruskalWeight);
        
        // The MST should exclude the highest weight edge (3-0 with weight 4)
        // and include edges 0-1, 1-2, and 2-3 with total weight 1+2+3=6
        CHECK(primWeight == 6);
        CHECK(kruskalWeight == 6);
    }
    
    SUBCASE("Larger complex graph for MST verification") {
        graph::Graph g(9); // Changed from 8 to 9 to include vertex 8
        g.addEdge(0, 1, 4);
        g.addEdge(0, 7, 8);
        g.addEdge(1, 2, 8);
        g.addEdge(1, 7, 11);
        g.addEdge(2, 3, 7);
        g.addEdge(2, 5, 4);
        g.addEdge(2, 8, 2);
        g.addEdge(3, 4, 9);
        g.addEdge(3, 5, 14);
        g.addEdge(4, 5, 10);
        g.addEdge(5, 6, 2);
        g.addEdge(6, 7, 1);
        g.addEdge(6, 8, 6);
        g.addEdge(7, 8, 7);
        
        std::cout << "\n----- Complex graph for MST verification -----\n";
        g.print_graph();
        
        graph::Graph mstPrim = graph::Algorithms::prim(g);
        graph::Graph mstKruskal = graph::Algorithms::kruskal(g);
        
        std::cout << "\n----- MST using Prim (larger graph) -----\n";
        mstPrim.print_graph();
        
        std::cout << "\n----- MST using Kruskal (larger graph) -----\n";
        mstKruskal.print_graph();
        
        // Check if MSTs are connected
        CHECK(isGraphConnected(mstPrim));
        CHECK(isGraphConnected(mstKruskal));
        
        // Verify total weights are equal
        int primWeight = calculateTotalWeight(mstPrim);
        int kruskalWeight = calculateTotalWeight(mstKruskal);
        
        CHECK(primWeight == kruskalWeight);
        
        // Known minimum weight for this standard graph
        CHECK(primWeight == 37);
    }
}