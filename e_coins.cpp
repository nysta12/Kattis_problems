#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    while (n--) {
        int m, S;
        cin >> m >> S;

        vector<pair<int, int>> coins(m);
        for (int i = 0; i < m; ++i)
            cin >> coins[i].first >> coins[i].second;

        vector<vector<int>> dp(S + 1, vector<int>(S + 1, INT_MAX));
        dp[0][0] = 0;

        for (int i = 0; i <= S; ++i) {
            for (int j = 0; j <= S; ++j) {
                if (dp[i][j] == INT_MAX) continue;
                for (auto [cv, iv] : coins) {
                    int ni = i + cv;
                    int nj = j + iv;
                    if (ni > S || nj > S) continue;
                    if (ni * ni + nj * nj > S * S) continue;
                    dp[ni][nj] = min(dp[ni][nj], dp[i][j] + 1);
                }
            }
        }

        int res = INT_MAX;
        for (int i = 0; i <= S; ++i) {
            for (int j = 0; j <= S; ++j) {
                if (i * i + j * j == S * S) {
                    res = min(res, dp[i][j]);
                }
            }
        }

        if (res == INT_MAX)
            cout << "not possible" << endl;
        else
            cout << res << endl;
    }
    return 0;
}