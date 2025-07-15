#include <iostream>
#include <vector>
#include <string>

using namespace std;


bool matches(const string& P, const string& s) {
    int m = (int)P.size();
    int n = (int)s.size();
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;

    for (int i = 1; i <= m; ++i) {
        if (P[i - 1] == '*')
            dp[i][0] = dp[i - 1][0];
        else
            break;
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (P[i - 1] == '*') {
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
            } else if (P[i - 1] == s[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = false;
            }
        }
    }
    return dp[m][n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string P;
    cin >> P;
    int N; 
    cin >> N;

    for (int i = 0; i < N; ++i) {
        string s;
        cin >> s;
        if (matches(P, s)) {
            cout << s << "\n";
        }
    }
    return 0;
}