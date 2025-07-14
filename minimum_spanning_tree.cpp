#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

void prim_mst(int n, vector<vector<pair<int, int>>> &adj) {
    vector<bool> in_mst(n, false);
    vector<int> key(n, INT_MAX);
    vector<int> parent(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<pair<int, int>> mst_edges;

    key[0] = 0;
    pq.push({0, 0});
    int total_weight = 0;
    int count_edges = 0;

    while (!pq.empty()) {
        auto [weight, u] = pq.top();
        pq.pop();

        if (in_mst[u]) continue;
        in_mst[u] = true;
        total_weight += weight;

        if (parent[u] != -1) {
            int v = parent[u];
            mst_edges.push_back({min(u, v), max(u, v)});
            count_edges++;
        }

        for (auto [v, w] : adj[u]) {
            if (!in_mst[v] && w < key[v]) {
                key[v] = w;
                parent[v] = u;
                pq.push({w, v});
            }
        }
    }

    if (count_edges != n - 1) {
        cout << "Impossible\n";
        return;
    }

    sort(mst_edges.begin(), mst_edges.end());

    cout << total_weight << "\n";
    for (auto [u, v] : mst_edges) {
        cout << u << " " << v << "\n";
    }
}

int main() {
    int n, m;
    while (cin >> n >> m, n || m) {
        vector<vector<pair<int, int>>> adj(n);
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        prim_mst(n, adj);
    }
    return 0;
}
