#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int capacity, n;
    while (cin >> capacity >> n) {
        vector<int> values(n), weights(n);
        for (int i = 0; i < n; ++i) {
            cin >> values[i] >> weights[i];
        }

        vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
        for (int i = 1; i <= n; ++i) {
            int val = values[i - 1];
            int wt = weights[i - 1];
            for (int w = 0; w <= capacity; ++w) {
                if (w >= wt) {
                    dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - wt] + val);
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }

        int w = capacity;
        vector<int> chosen_items;
        for (int i = n; i > 0; --i) {
            if (dp[i][w] != dp[i - 1][w]) {
                chosen_items.push_back(i - 1);
                w -= weights[i - 1];
            }
        }

        cout << chosen_items.size() << endl;
        for (int i = 0; i < chosen_items.size(); ++i) {
            cout << chosen_items[i] << " ";
        }
        cout << endl;
    }

    return 0;
}