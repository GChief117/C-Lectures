#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <algorithm>
#include "GraphPrinter.h"

using namespace std;

class UndirectedGraph {
public:
    int V; // Number of vertices
    vector<list<int>> adj; // Adjacency list

    // Constructor to initialize the graph with V vertices
    UndirectedGraph(int V) : V(V) {
        adj.resize(V);
    }

    // Add an undirected edge between vertex v and vertex w
    void addEdge(int v, int w) {
        adj[v].push_back(w);
        adj[w].push_back(v);
    }

    // Remove an undirected edge between vertex v and vertex w
    void removeEdge(int v, int w) {
        adj[v].remove(w);
        adj[w].remove(v);
    }

    // Remove a vertex and all its associated edges
    void removeVertex(int v) {
        for (auto& neighbors : adj) {
            neighbors.remove(v);
        }
        adj[v].clear();
    }

    // Perform a depth-first search (DFS) iteratively starting from vertex v
    void DFS_iterative(int v) {
        vector<bool> visited(V, false);
        stack<int> stack;
        stack.push(v);
        while (!stack.empty()) {
            v = stack.top();
            stack.pop();
            if (!visited[v]) {
                cout << v << " ";
                visited[v] = true;
            }
            for (auto i = adj[v].rbegin(); i != adj[v].rend(); ++i) {
                if (!visited[*i]) {
                    stack.push(*i);
                }
            }
        }
        cout << endl;
    }

    // Helper function for recursive DFS
    void DFS_recursive(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";
        for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
            if (!visited[*i]) {
                DFS_recursive(*i, visited);
            }
        }
    }

    // Perform a depth-first search (DFS) recursively starting from vertex v
    void DFS_recursive_start(int v) {
        vector<bool> visited(V, false);
        DFS_recursive(v, visited);
        cout << endl;
    }

    // Perform a breadth-first search (BFS) iteratively starting from vertex v
    void BFS_iterative(int v) {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[v] = true;
        q.push(v);
        while (!q.empty()) {
            v = q.front();
            cout << v << " ";
            q.pop();
            for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
                if (!visited[*i]) {
                    visited[*i] = true;
                    q.push(*i);
                }
            }
        }
        cout << endl;
    }

    // Helper function for recursive BFS
    void BFS_recursive(queue<int>& q, vector<bool>& visited) {
        if (q.empty()) return;
        int v = q.front();
        q.pop();
        cout << v << " ";
        for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
            if (!visited[*i]) {
                visited[*i] = true;
                q.push(*i);
            }
        }
        BFS_recursive(q, visited);
    }

    // Perform a breadth-first search (BFS) recursively starting from vertex v
    void BFS_recursive_start(int v) {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[v] = true;
        q.push(v);
        BFS_recursive(q, visited);
        cout << endl;
    }
};

int main() {
    UndirectedGraph graph(6); // Create a graph with 6 vertices

    // Add edges to the graph
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 5);
    graph.addEdge(5, 0);

    cout << "DFS (iterative) starting from vertex 0: ";
    graph.DFS_iterative(0); // Perform DFS iteratively starting from vertex 0

    cout << "DFS (recursive) starting from vertex 0: ";
    graph.DFS_recursive_start(0); // Perform DFS recursively starting from vertex 0

    cout << "BFS (iterative) starting from vertex 0: ";
    graph.BFS_iterative(0); // Perform BFS iteratively starting from vertex 0

    cout << "BFS (recursive) starting from vertex 0: ";
    graph.BFS_recursive_start(0); // Perform BFS recursively starting from vertex 0

    // Print the graph using GraphPrinter
    GraphPrinter printer;
    printer.printGraph(graph.adj);

    // Remove an edge and print the graph again
    graph.removeEdge(2, 3);
    cout << "Graph after removing edge 2 -> 3:" << endl;
    printer.printGraph(graph.adj);

    // Remove a vertex and print the graph again
    graph.removeVertex(3);
    cout << "Graph after removing vertex 3:" << endl;
    printer.printGraph(graph.adj);

    return 0;
}
