#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // undirected
    }

    void parallelBFS(int start) {
        vector<bool> visited(V, false);
        vector<int> frontier, next;

        frontier.push_back(start);
        visited[start] = true;

        cout << "Parallel BFS: ";

        while (!frontier.empty()) {
            next.clear();

#pragma omp parallel for
            for (int i = 0; i < frontier.size(); i++) {
                int node = frontier[i];

#pragma omp critical
                cout << node << " ";

                for (int neighbor : adj[node]) {
                    if (!visited[neighbor]) {
#pragma omp critical
                        {
                            if (!visited[neighbor]) {
                                visited[neighbor] = true;
                                next.push_back(neighbor);
                            }
                        }
                    }
                }
            }

            frontier = next;
        }

        cout << endl;
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

    g.parallelBFS(0);

    return 0;
}