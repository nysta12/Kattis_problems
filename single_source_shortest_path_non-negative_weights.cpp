#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;


void dijkstra(int n, int start, const vector<vector<pair<int, int>>> &graph, vector<int> &dist) {
    dist.assign(n, INT_MAX);
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;

        for (auto &[v, w] : graph[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q, s;
    bool first_case = true;

    while (cin >> n >> m >> q >> s, n || m || q || s) {
        
        vector<vector<pair<int, int>>> graph(n);
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            graph[u].emplace_back(v, w);
        }

        vector<int> dist;
        dijkstra(n, s, graph, dist);

        if (!first_case) cout << "\n";
        first_case = false;

        for (int i = 0; i < q; ++i) {
            int t;
            cin >> t;
            if (dist[t] == INT_MAX)
                cout << "Impossible\n";
            else
                cout << dist[t] << "\n";
        }
    }
    return 0;
}