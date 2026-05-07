#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;
    vector<bool> visited;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
        visited.resize(V, false);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // DFS helper
    void dfsUtil(int node) {

#pragma omp critical
        cout << node << " "; // print safely

        for (int neighbor : adj[node]) {

            bool go = false;

#pragma omp critical
            {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    go = true;
                }
            }

            if (go) {
#pragma omp task
                dfsUtil(neighbor); // explore deeper
            }
        }
    }

    void parallelDFS(int start) {
#pragma omp parallel
        {
#pragma omp single
            {
                visited[start] = true;
                dfsUtil(start);
            }
        }
    }
};

int main() {
    Graph g(7);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    cout << "Parallel DFS: ";
    g.parallelDFS(0);
    cout << endl;

    return 0;
}