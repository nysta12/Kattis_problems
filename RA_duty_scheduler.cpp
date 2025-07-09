#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <climits>

using namespace std;

int m, n, d, i;
string name;
const int NO_PARENT = -1;
int s, t;

int bfs(vector<vector<int>>& capacity, vector<vector<int>>& adj, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = NO_PARENT;
    queue<pair<int,int>> q;
    q.push({s, INT_MAX});
    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();
        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next] > 0) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t) return new_flow;
                q.push({next, new_flow});
            }
        }
    }
    return 0;
}

int maxflow(vector<vector<int>>& capacity, vector<vector<int>>& adj) {
    int flow = 0;
    vector<int> parent(t + 1);
    int new_flow;
    while ((new_flow = bfs(capacity, adj, parent))) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }
    return flow;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;
    vector<string> names(m);
    unordered_map<string,int> name_to_index;
    vector<vector<bool>> availability(m, vector<bool>(n,false));

    for (int x = 0; x < m; ++x) {
        cin >> name >> d;
        names[x] = name;
        name_to_index[name] = x;
        for (int y = 0; y < d; ++y) {
            cin >> i;
            availability[x][i - 1] = true;
        }
    }

    int low = 0, high = n, answer = n;
    while (low <= high) {
        int mid = (low + high) / 2;
        int num_nodes = m + n + 2;
        s = m + n;
        t = m + n + 1;
        vector<vector<int>> capacity(num_nodes, vector<int>(num_nodes, 0));
        vector<vector<int>> adj(num_nodes);

        for (int i = 0; i < m; ++i) {
            capacity[s][i] = mid;
            adj[s].push_back(i);
            adj[i].push_back(s);
        }
        for (int i = 0; i < m; ++i) {
            for (int day = 0; day < n; ++day) {
                if (availability[i][day]) {
                    int day_node = m + day;
                    capacity[i][day_node] = 1;
                    adj[i].push_back(day_node);
                    adj[day_node].push_back(i);
                }
            }
        }
        for (int day = 0; day < n; ++day) {
            int day_node = m + day;
            capacity[day_node][t] = 2;
            adj[day_node].push_back(t);
            adj[t].push_back(day_node);
        }

        int flow = maxflow(capacity, adj);
        if (flow == 2 * n) {
            answer = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    int num_nodes = m + n + 2;
    s = m + n;
    t = m + n + 1;
    vector<vector<int>> capacity(num_nodes, vector<int>(num_nodes, 0));
    vector<vector<int>> adj(num_nodes);

    for (int i = 0; i < m; ++i) {
        capacity[s][i] = answer;
        adj[s].push_back(i);
        adj[i].push_back(s);
    }
    for (int i = 0; i < m; ++i) {
        for (int day = 0; day < n; ++day) {
            if (availability[i][day]) {
                int day_node = m + day;
                capacity[i][day_node] = 1;
                adj[i].push_back(day_node);
                adj[day_node].push_back(i);
            }
        }
    }
    for (int day = 0; day < n; ++day) {
        int day_node = m + day;
        capacity[day_node][t] = 2;
        adj[day_node].push_back(t);
        adj[t].push_back(day_node);
    }

    maxflow(capacity, adj);

    vector<vector<string>> schedule(n);
    for (int i = 0; i < m; ++i) {
        for (int day = 0; day < n; ++day) {
            if (availability[i][day]) {
                int day_node = m + day;
                if (capacity[i][day_node] == 0) {
                    schedule[day].push_back(names[i]);
                }
            }
        }
    }

    cout << answer << '\n';
    for (int day = 0; day < n; ++day) {
        cout << "Day " << day + 1 << ": " << schedule[day][0] << " " << schedule[day][1] << '\n';
    }

    return 0;
}
