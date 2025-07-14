#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};


bool can_move(int f1, int c1, int f2, int c2) {
    int min_ceil = min(c1, c2);
    int max_floor = max(f1, f2);
    return min_ceil - max_floor >= 50;
}

void bfs(int N, int M, int H, vector<vector<int>>& ceiling, vector<vector<int>>& floor, vector<vector<double>>& time, queue<pair<int, int>>& starting_points) {
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    queue<pair<int, int>> q;
    q.push({0, 0});
    visited[0][0] = true;
    time[0][0] = 0;
    starting_points.push({0, 0});

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue;
            if (visited[nx][ny]) continue;
            if (!can_move(floor[x][y], ceiling[x][y], floor[nx][ny], ceiling[nx][ny])) continue;
            if (ceiling[nx][ny] - H >= 50) {
                visited[nx][ny] = true;
                time[nx][ny] = 0;
                q.push({nx, ny});
                starting_points.push({nx, ny});
            }
        }
    }
}

void dijkstra(int N, int M, int H, vector<vector<int>>& ceiling, vector<vector<int>>& floor, vector<vector<double>>& time, queue<pair<int, int>>& starting_points) {
    while (!starting_points.empty()) {
        int x = starting_points.front().first;
        int y = starting_points.front().second;
        starting_points.pop();

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue;
            if (!can_move(floor[x][y], ceiling[x][y], floor[nx][ny], ceiling[nx][ny])) continue;

            double current_time = time[x][y];
            double water_level = H - current_time * 10.0;

            if (ceiling[nx][ny] - water_level < 50)
                current_time += (50 - (ceiling[nx][ny] - water_level)) / 10.0;

            water_level = H - current_time * 10.0;
            double move_time;
            if (water_level - floor[x][y] >= 20) {
                move_time = 1.0;
            } else {
                move_time = 10.0;
            }
            double total_time = current_time + move_time;

            if (total_time + 1e-6 < time[nx][ny]) {
                time[nx][ny] = total_time;
                starting_points.push({nx, ny});
            }
        }
    }
}

int main() {
    int T;
    cin >> T;
    for (int test = 1; test <= T; test++) {
        int H, N, M;
        cin >> H >> N >> M;

        vector<vector<int>> ceiling(N, vector<int>(M));
        vector<vector<int>> floor(N, vector<int>(M));
        vector<vector<double>> time(N, vector<double>(M, INT_MAX));
        queue<pair<int, int>> starting_points;

        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                cin >> ceiling[i][j];

        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                cin >> floor[i][j];

        bfs(N, M, H, ceiling, floor, time, starting_points);
        dijkstra(N, M, H, ceiling, floor, time, starting_points);

        
        cout << fixed << setprecision(1);
        cout << "Case #" << test << ": " << time[N - 1][M - 1] << endl;
    }
    return 0;
}


