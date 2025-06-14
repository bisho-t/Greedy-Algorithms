#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// Edge structure representing a road with gold and silver requirements
struct Edge {
    int from, to;
    long long gold, silver;

    // Sort by gold requirement
    bool operator<(const Edge& other) const {
        return gold < other.gold;
    }
};

class RoadOptimizer {
private:
    vector<int> parent;
    vector<Edge> edges;
    vector<Edge> selectedEdges;  // Stores edges being considered for MST
    int vertices, edgeCount;
    long long goldCost, silverCost;

    // Union-Find functions for MST
    void unionSets(int x, int y) {
        parent[findParent(x)] = findParent(y);
    }

    int findParent(int x) {
        if (parent[x] == x) return x;
        return parent[x] = findParent(parent[x]);
    }

public:
    RoadOptimizer(int n, int m, long long G, long long S) :
            vertices(n), edgeCount(m), goldCost(G), silverCost(S),
            parent(n + 1), edges(m + 1), selectedEdges(n + 1) {}

    void addEdge(int idx, int x, int y, long long gold, long long silver) {
        edges[idx] = {x, y, gold, silver};
    }

    long long findMinimumCost() {
        // Sort edges by gold requirement
        sort(edges.begin() + 1, edges.begin() + edgeCount + 1);
        long long minTotalCost = 9e18;

        // Try each edge as the maximum gold requirement
        for (int i = 1, selected = 0; i <= edgeCount; i++) {
            selectedEdges[++selected] = edges[i];

            // Sort selected edges by silver requirement
            for (int j = selected - 1; j && selectedEdges[j + 1].silver < selectedEdges[j].silver; j--) {
                swap(selectedEdges[j], selectedEdges[j + 1]);
            }

            if (selected < vertices - 1 ) { continue;}
            // Reset Union-Find structure
            for (int j = 1; j <= vertices; j++) {
                parent[j] = j;
            }

            // Try to build MST with current edges
            int connectedEdges = 0;
            for (int j = 1; j <= selected && connectedEdges < vertices - 1; j++) {
                int x = findParent(selectedEdges[j].from);
                int y = findParent(selectedEdges[j].to);

                if (x != y) {
                    unionSets(x, y);
                    selectedEdges[++connectedEdges] = selectedEdges[j];
                }
            }

            // If we found a valid MST, update minimum cost
            if (connectedEdges == vertices - 1) {
                minTotalCost = min(minTotalCost,
                                   goldCost * edges[i].gold + silverCost * selectedEdges[connectedEdges].silver);
            }

            selected = connectedEdges;
        }

        return minTotalCost == 9e18 ? -1 : minTotalCost;
    }
};

int main() {
    int n, m;
    long long G, S;
    cin >> n >> m >> G >> S;

    RoadOptimizer optimizer(n, m, G, S);

    for (int i = 1; i <= m; i++) {
        int x, y;
        long long gold, silver;
        cin >> x >> y >> gold >> silver;
        optimizer.addEdge(i, x, y, gold, silver);
    }

    cout << optimizer.findMinimumCost() << endl;
    return 0;
}