#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int w, h;
vector<string> grid;
vector<vector<bool>> visited;

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {-1, 0, 1, 0};

bool is_safe(int x, int y) {
    for (int d = 0; d < 4; ++d) {
        int new_x = x + dx[d];
        int new_y = y + dy[d];
        if (grid[new_y][new_x] == 'T') {
            return false; 
        }
    }
    return true;
}

int bfs(int start_x, int start_y) {
    queue<pair<int, int>> q;
    q.push({start_x, start_y});
    visited[start_y][start_x] = true;

    int gold = 0;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (grid[y][x] == 'G') {
            ++gold;
        }

        if (!is_safe(x, y)) continue;

        for (int d = 0; d < 4; ++d) {
            int new_x = x + dx[d];
            int new_y = y + dy[d];

            if (new_x >= 0 && new_x < w && new_y >= 0 && new_y < h &&
                !visited[new_y][new_x] && grid[new_y][new_x] != '#') {

                visited[new_y][new_x] = true;
                q.push({new_x, new_y});
            }
        }
    }
    return gold;
}

int main() {
    cin >> w >> h;
    grid.resize(h);
    visited.assign(h, vector<bool>(w, false));

    int start_x = 0, start_y = 0;

    for (int i = 0; i < h; ++i) {
        cin >> grid[i];
        for (int j = 0; j < w; ++j) {
            if (grid[i][j] == 'P') {
                start_x = j;
                start_y = i;
            }
        }
    }

    int result = bfs(start_x, start_y);
    cout << result << endl;

    return 0;
}
