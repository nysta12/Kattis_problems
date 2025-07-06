#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <climits>
using namespace std;

const int NO_PARENT = -2;

int n, m, s, t;

int bfs(vector<vector<int>>& flow_capacity, vector<vector<int>>& adjacent, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = NO_PARENT;
    queue<pair<int, int>> q;
    q.push({s, INT_MAX});

    while (!q.empty()) {
        int current = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next_node : adjacent[current]) {
            if (parent[next_node] == -1 && flow_capacity[current][next_node] > 0) {
                parent[next_node] = current;
                int new_flow = min(flow, flow_capacity[current][next_node]);
                if (next_node == t)
                    return new_flow;
                q.push({next_node, new_flow});
            }
        }
    }
    return 0;
}

int maxflow(vector<vector<int>>& flow_capacity, vector<vector<int>>& adjacent) {
    int flow = 0;
    vector<int> parent(n, -1);
    int new_flow;

    while ((new_flow = bfs(flow_capacity, adjacent, parent))) {
        flow += new_flow;
        int current = t;
        while (current != s) {
            int previous = parent[current];
            flow_capacity[previous][current] -= new_flow;
            flow_capacity[current][previous] += new_flow;
            current = previous;
        }
    }
    return flow;
}

void minimum_cut(int u, vector<vector<int>>& flow_capacity, vector<vector<int>>& adjacent, vector<bool>& visited) {
    visited[u] = true;
    for (int v : adjacent[u]) {
        if (!visited[v] && flow_capacity[u][v] > 0) {
            minimum_cut(v, flow_capacity, adjacent, visited);
        }
    }
}

int main() {
    cin >> n >> m >> s >> t;
    vector<vector<int>> flow_capacity(n, vector<int>(n, 0));
    vector<vector<int>> adjacent(n);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adjacent[u].push_back(v);
        adjacent[v].push_back(u);
        flow_capacity[u][v] += w;
    }

    maxflow(flow_capacity, adjacent);

    vector<bool> visited(n, false);
    minimum_cut(s, flow_capacity, adjacent, visited);

    vector<int> U;
    for (int i = 0; i < n; ++i)
        if (visited[i])
            U.push_back(i);

    cout << U.size() << endl;
    for (int k : U)
        cout << k << endl;


    return 0;
}

