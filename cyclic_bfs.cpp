#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const vector<string> names = {"A", "B", "C", "D", "E", "F", "G"};

bool printCyclePath(const vector<int>& parent, int start, int end) {
    vector<int> cycle;
    int v = end;
    cycle.push_back(v);
    while (v != start && v != -1) {
        v = parent[v];
        cycle.push_back(v);
    }
    if (v == -1) return false;
    cycle.push_back(end);
    reverse(cycle.begin(), cycle.end());
    cout << "Cycle found: ";
    for (int x : cycle) cout << names[x] << " ";
    cout << endl;
    return true;
}

bool detectCycleBFS(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> visited(n, false);

    for (int start = 0; start < n; ++start) {
        vector<int> parent(n, -1);
        vector<bool> inQueue(n, false);
        queue<int> q;
        q.push(start);
        inQueue[start] = true;

        while (!q.empty()) {
            int v = q.front(); q.pop();
            visited[v] = true;
            for (int u = 0; u < n; ++u) {
                if (adj[v][u]) {
                    if (!inQueue[u]) {
                        parent[u] = v;
                        q.push(u);
                        inQueue[u] = true;
                    } else if (parent[v] != u) {
                        if (printCyclePath(parent, u, v)) return true;
                    }
                }
            }
        }
    }
    cout << "No cycle found (BFS)." << endl;
    return false;
}

int main() {
    vector<vector<int>> adj = {
        {0, 0, 1, 0, 0, 0, 0}, // A
        {0, 0, 1, 0, 0, 0, 0}, // B
        {0, 0, 0, 0, 1, 1, 1}, // C
        {1, 0, 0, 0, 1, 0, 0}, // D
        {0, 0, 0, 1, 0, 0, 0}, // E
        {0, 0, 0, 0, 0, 0, 0}, // F
        {0, 0, 0, 0, 0, 0, 0}  // G
    };

    cout << "BFS Cycle Path Detection:" << endl;
    detectCycleBFS(adj);

    return 0;
}