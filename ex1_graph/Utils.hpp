// utils.hpp
#ifndef UTILS_HPP
#define UTILS_HPP

namespace graph {

// Queue implementation for BFS
class Queue {
private:
    struct Node {
        int data;
        Node* next;
        
        Node(int val) : data(val), next(nullptr) {}
    };
    
    Node* front;
    Node* rear;
    
public:
    Queue() : front(nullptr), rear(nullptr) {}
    
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
    
    void enqueue(int value) {
        Node* newNode = new Node(value);
        
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }
    
    int dequeue() {
        if (isEmpty()) {
            throw "Queue is empty";
        }
        
        int value = front->data;
        Node* temp = front;
        
        if (front == rear) {
            front = rear = nullptr;
        } else {
            front = front->next;
        }
        
        delete temp;
        return value;
    }
    
    bool isEmpty() const {
        return front == nullptr;
    }
};

// Priority Queue implementation for Dijkstra and Prim
class PriorityQueue {
private:
    struct HeapNode {
        int vertex;
        int priority;
        
        HeapNode() : vertex(-1), priority(0) {}
        HeapNode(int v, int p) : vertex(v), priority(p) {}
    };
    
    HeapNode* heap;
    int* position; // To track positions for decreaseKey
    int capacity;
    int heapSize;
    
    void swap(int i, int j) {
        // Update position array
        position[heap[i].vertex] = j;
        position[heap[j].vertex] = i;
        
        // Swap heap nodes
        HeapNode temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }
    
    void heapify(int index) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        
        if (left < heapSize && heap[left].priority < heap[smallest].priority) {
            smallest = left;
        }
        
        if (right < heapSize && heap[right].priority < heap[smallest].priority) {
            smallest = right;
        }
        
        if (smallest != index) {
            swap(index, smallest);
            heapify(smallest);
        }
    }
    
public:
    PriorityQueue(int cap) : capacity(cap), heapSize(0) {
        heap = new HeapNode[capacity];
        position = new int[capacity];
        
        for (int i = 0; i < capacity; i++) {
            position[i] = -1; // Initialize with -1 (not in heap)
        }
    }
    
    ~PriorityQueue() {
        delete[] heap;
        delete[] position;
    }
    
    bool isEmpty() const {
        return heapSize == 0;
    }
    
    bool inQueue(int vertex) const {
        return position[vertex] != -1;
    }
    
    void insert(int vertex, int priority) {
        if (heapSize == capacity) {
            throw "Priority queue is full";
        }
        
        int i = heapSize;
        heap[i] = HeapNode(vertex, priority);
        position[vertex] = i;
        heapSize++;
        
        // Fix min-heap property
        while (i > 0 && heap[(i - 1) / 2].priority > heap[i].priority) {
            swap(i, (i - 1) / 2);
            i = (i - 1) / 2;
        }
    }
    
    int extractMin() {
        if (isEmpty()) {
            throw "Priority queue is empty";
        }
        
        // Store the root (minimum) node
        int minVertex = heap[0].vertex;
        
        // Replace root with last element and heapify
        heap[0] = heap[heapSize - 1];
        position[heap[0].vertex] = 0;
        heapSize--;
        
        // Mark the extracted vertex as not in queue
        position[minVertex] = -1;
        
        if (heapSize > 0) {
            heapify(0);
        }
        
        return minVertex;
    }
    
    void decreaseKey(int vertex, int newPriority) {
        if (!inQueue(vertex)) {
            throw "Vertex not in priority queue";
        }
        
        int i = position[vertex];
        
        // Update the priority
        if (newPriority > heap[i].priority) {
            throw "New priority is greater than current priority";
        }
        
        heap[i].priority = newPriority;
        
        // Fix min-heap property
        while (i > 0 && heap[(i - 1) / 2].priority > heap[i].priority) {
            swap(i, (i - 1) / 2);
            i = (i - 1) / 2;
        }
    }
    
    int getPriority(int vertex) const {
        if (!inQueue(vertex)) {
            throw "Vertex not in priority queue";
        }
        
        return heap[position[vertex]].priority;
    }
};

// Union-Find implementation for Kruskal's algorithm
class UnionFind {
private:
    int* parent;
    int* rank;
    int size;
    
public:
    UnionFind(int n) : size(n) {
        parent = new int[n];
        rank = new int[n];
        
        for (int i = 0; i < n; i++) {
            parent[i] = i; // Each element is its own parent initially
            rank[i] = 0;   // Initial rank is 0
        }
    }
    
    ~UnionFind() {
        delete[] parent;
        delete[] rank;
    }
    
    // Find with path compression
    int find(int x) {
        if (x < 0 || x >= size) {
            throw "Index out of range";
        }
        
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }
    
    // Union by rank
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) return;
        
        // Union by rank
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

} // namespace graph

#endif // UTILS_HPP