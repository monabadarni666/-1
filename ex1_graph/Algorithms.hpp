// algorithms.hpp
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"

namespace graph {

class Algorithms {
public:
    // BFS algorithm - returns a rooted tree graph from BFS traversal
    static Graph bfs(const Graph& g, int source);
    
    // DFS algorithm - returns a graph (tree or forest) from DFS traversal
    static Graph dfs(const Graph& g, int source);
    
    // Dijkstra's algorithm - returns a weighted tree of shortest paths
    static Graph dijkstra(const Graph& g, int source);
    
    // Prim's algorithm - returns a minimum spanning tree
    static Graph prim(const Graph& g);
    
    // Kruskal's algorithm - returns a minimum spanning tree
    static Graph kruskal(const Graph& g);
    
private:
    // Helper method for DFS
    static void dfsVisit(const Graph& g, int vertex, bool* visited, Graph& result);
};

} // namespace graph

#endif // ALGORITHMS_HPP