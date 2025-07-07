#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int NO_PARENT = -2;

int n, m, s, t;

int bfs(vector<vector<int>>& flow_capacity, vector<vector<int>>& adjacent, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = NO_PARENT;
    queue<pair<int, int>> q;
    q.push({s, INT_MAX});

    while (!q.empty()){
        int current = q.front().first;
        int flow = q.front().second;
        q.pop();
        for (int next_node : adjacent[current]){
            if (parent[next_node] == -1 && flow_capacity[current][next_node] > 0){
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

int maxflow(vector<vector<int>>& flow_capacity, vector<vector<int>>& adjacent, vector<vector<int>>& flow_result){
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while ((new_flow = bfs(flow_capacity, adjacent, parent))){
        flow += new_flow;
        int current = t;
        while (current != s){
            int previous = parent[current];
            flow_capacity[previous][current] -= new_flow;
            flow_capacity[current][previous] += new_flow;
            flow_result[previous][current] += new_flow;
            flow_result[current][previous] -= new_flow;
            current = previous;
        }
    }
    return flow;
}

int main() {
    cin >> n >> m >> s >> t;
    vector<vector<int>> flow_capacity(n, vector<int>(n, 0));
    vector<vector<int>> flow_result(n, vector<int>(n, 0));
    vector<vector<int>> adjacent(n);
    vector<pair<int,int>> input_edges;

    for (int i = 0; i < m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        adjacent[u].push_back(v);
        adjacent[v].push_back(u);
        flow_capacity[u][v] += c;
        input_edges.push_back({u, v});
    }

    int total_flow = maxflow(flow_capacity, adjacent, flow_result);

    vector<tuple<int,int,int>> result_edges;
    for (auto [u, v] : input_edges) {
        if (flow_result[u][v] > 0) {
            result_edges.emplace_back(u, v, flow_result[u][v]);
        }
    }

    cout << n << " " << total_flow << " " << result_edges.size() << "\n";
    for (auto [u, v, f] : result_edges) {
        cout << u << " " << v << " " << f << "\n";
    }

    return 0;
}

