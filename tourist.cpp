#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int traverse(const vector<string>& map, int w, int h){
    int max_steps = w + h - 2;
    vector<vector<int>> dp(h, vector<int>(h, INT_MIN));

    if (map[0][0] == '*') {
        dp[0][0] = 1;
    } else {
        dp[0][0] = 0;
    }

    for (int k = 1; k <= max_steps; ++k){
        vector<vector<int>> new_dp(h, vector<int>(h, INT_MIN));

        for (int x1 = max(0, k - (w - 1)); x1 <= min(h - 1, k); ++x1) {
            int y1 = k - x1;
            if (y1 < 0 || y1 >= w || map[x1][y1] == '#') continue;

            for (int x2 = max(0, k - (w - 1)); x2 <= min(h - 1, k); ++x2) {
                int y2 = k - x2;
                if (y2 < 0 || y2 >= w || map[x2][y2] == '#') continue;

                int best_prev = INT_MIN;

                for (int d_x1 = -1; d_x1 <= 0; ++d_x1) {
                    for (int d_x2 = -1; d_x2 <= 0; ++d_x2) {
                        int prev_x1 = x1 + d_x1;
                        int prev_x2 = x2 + d_x2;
                        int prev_y1 = y1 - (1 + d_x1);
                        int prev_y2 = y2 - (1 + d_x2);

                        if (prev_x1 < 0 || prev_x2 < 0 || prev_y1 < 0 || prev_y2 < 0) continue;
                        if (prev_x1 >= h || prev_x2 >= h || prev_y1 >= w || prev_y2 >= w) continue;
                        if (dp[prev_x1][prev_x2] == INT_MIN) continue;

                        best_prev = max(best_prev, dp[prev_x1][prev_x2]);
                    }
                }
                if (best_prev == INT_MIN) continue;

                int add = 0;
                if (map[x1][y1] == '*') add += 1;
                if (x1 != x2 || y1 != y2) {
                    if (map[x2][y2] == '*') add += 1;
                }
                new_dp[x1][x2] = max(new_dp[x1][x2], best_prev + add);
            }
        }
        dp = new_dp;
    }
    return max(0, dp[h - 1][h - 1]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int w, h;
        cin >> w >> h;
        vector<string> map(h);
        for (int i = 0; i < h; ++i) {
            cin >> map[i];
        }

        cout << traverse(map, w, h) << "\n";
    }
    return 0;
}

