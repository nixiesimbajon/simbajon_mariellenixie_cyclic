#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const vector<string> names = {"A", "B", "C", "D", "E", "F", "G"};

void printCycle(const vector<int>& parent, int start, int end) {
    vector<int> cycle;
    int v = end;
    cycle.push_back(v);
    while (v != start) {
        v = parent[v];
        cycle.push_back(v);
    }
    cycle.push_back(end);
    reverse(cycle.begin(), cycle.end());
    cout << "Cycle found: ";
    for (int v : cycle) cout << names[v] << " ";
    cout << endl;
}

bool dfsCycleUtil(const vector<vector<int>>& adj, int v, vector<int>& visited, vector<int>& parent, int& cycleStart, int& cycleEnd) {
    visited[v] = 1;
    for (int u = 0; u < adj.size(); ++u) {
        if (adj[v][u]) {
            if (visited[u] == 0) {
                parent[u] = v;
                if (dfsCycleUtil(adj, u, visited, parent, cycleStart, cycleEnd)) return true;
            } else if (visited[u] == 1) {
                cycleStart = u;
                cycleEnd = v;
                parent[u] = v;
                return true;
            }
        }
    }
    visited[v] = 2;
    return false;
}

bool detectCycleDFS(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> visited(n, 0);
    vector<int> parent(n, -1);
    int cycleStart = -1, cycleEnd = -1;
    for (int v = 0; v < n; ++v) {
        if (visited[v] == 0) {
            if (dfsCycleUtil(adj, v, visited, parent, cycleStart, cycleEnd)) {
                printCycle(parent, cycleStart, cycleEnd);
                return true;
            }
        }
    }
    cout << "No cycle found (DFS)." << endl;
    return false;
}

int main() {
    vector<vector<int>> adj = {
        {0, 0, 1, 1, 0, 0, 0}, // A
        {0, 0, 1, 0, 0, 0, 0}, // B
        {0, 0, 0, 0, 1, 1, 1}, // C
        {1, 0, 0, 0, 0, 0, 0}, // D
        {0, 0, 0, 1, 0, 0, 0}, // E
        {0, 0, 0, 0, 0, 0, 0}, // F
        {0, 0, 0, 0, 0, 0, 0}  // G
    };

    cout << "DFS Cycle Detection:" << endl;
    detectCycleDFS(adj);

    return 0;
}