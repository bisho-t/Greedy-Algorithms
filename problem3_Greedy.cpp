#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

bool dfs(int source, int destination, vector<vector<int>>& adj, unordered_set<int>& visited) {
    if (source == destination) {
        return true;
    }

    visited.insert(source);
    for (int neighbor : adj[source]) {
        if (visited.find(neighbor) == visited.end()) {
            if (dfs(neighbor, destination, adj, visited)) {
                return true;
            }
        }
    }

    return false;
}

bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
    vector<vector<int>> adj(n);

    for (auto& edge : edges) {
        adj[edge[0]].push_back(edge[1]);        // {2, 0}
        adj[edge[1]].push_back(edge[0]);        // {1, 2} , {0, 2} , {1, 0}
    }
    unordered_set<int> visited;

    return dfs(source, destination, adj, visited);
}

int main() {
    // Test case 1
    int n = 3;
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 0}};
    int source = 0, destination = 2;

    cout << (validPath(n, edges, source, destination) ? "true" : "false") << endl;

    // Test case 2
    n = 6;
    edges = {{0, 1}, {0, 2}, {3, 5}, {5, 4}, {4, 3}};
    source = 0, destination = 5;

    cout << (validPath(n, edges, source, destination) ? "true" : "false") << endl;

    return 0;
}
