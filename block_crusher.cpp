#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <tuple>

using namespace std;

const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

struct Cell {
    int cost, x, y;
    bool operator>(const Cell& other) const {
        return cost > other.cost;
    }
};

void solveBlock(int h, int w, vector<string>& grid) {
    vector<vector<int>> dist(h, vector<int>(w, INT_MAX));
    vector<vector<pair<int, int>>> parent(h, vector<pair<int, int>>(w, {-1, -1}));
    priority_queue<Cell, vector<Cell>, greater<Cell>> pq;

    for (int j = 0; j < w; ++j) {
        dist[0][j] = grid[0][j] - '0';
        pq.push({dist[0][j], 0, j});
    }

    while (!pq.empty()) {
        auto [cost, x, y] = pq.top(); pq.pop();
        if (cost > dist[x][y]) continue;

        for (int d = 0; d < 8; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx >= 0 && nx < h && ny >= 0 && ny < w) {
                int ncost = cost + (grid[nx][ny] - '0');
                if (ncost < dist[nx][ny]) {
                    dist[nx][ny] = ncost;
                    parent[nx][ny] = {x, y};
                    pq.push({ncost, nx, ny});
                }
            }
        }
    }

    int min_cost = INT_MAX, end_col = -1;
    for (int j = 0; j < w; ++j) {
        if (dist[h-1][j] < min_cost) {
            min_cost = dist[h-1][j];
            end_col = j;
        }
    }

    int x = h-1, y = end_col;
    while (x != -1 && y != -1) {
        grid[x][y] = ' ';
        tie(x, y) = parent[x][y];
    }

    for (const string& row : grid)
        cout << row << '\n';
    cout << '\n';
}


int main() {
    int h, w;
    while (cin >> h >> w, h || w){

        vector<string> grid(h);
        for (int i = 0; i < h; ++i){
            cin >> grid[i];
        }

        solveBlock(h, w, grid);
    }
    return 0;
}