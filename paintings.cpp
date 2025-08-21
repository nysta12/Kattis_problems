#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

int n;
vector<string> colors;
unordered_map<string, int> colorIndex;
vector<vector<bool>> forbidden;
vector<bool> used;

unsigned long long countSequences(int last, int count) {
    if (count == n) return 1;

    unsigned long long total = 0;
    for (int i = 0; i < n; i++) {
        if (!used[i] && (last == -1 || !forbidden[last][i])) {
            used[i] = true;
            total += countSequences(i, count + 1);
            used[i] = false;
        }
    }
    return total;
}

void buildSequence(int last, int count, vector<string>& favorite) {
    if (count == n) return;

    for (int i = 0; i < n; i++) {
        if (!used[i] && (last == -1 || !forbidden[last][i])) {
            used[i] = true;
            unsigned long long ways = countSequences(i, count + 1);
            if (ways > 0) {
                favorite.push_back(colors[i]);
                buildSequence(i, count + 1, favorite);
                return;
            }
            used[i] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        colors.resize(n);
        colorIndex.clear();
        for (int i = 0; i < n; i++) {
            cin >> colors[i];
            colorIndex[colors[i]] = i;
        }

        int m;
        cin >> m;
        forbidden.assign(n, vector<bool>(n, false));
        while (m--) {
            string a, b;
            cin >> a >> b;
            int x = colorIndex[a];
            int y = colorIndex[b];
            forbidden[x][y] = true;
            forbidden[y][x] = true;
        }

        used.assign(n, false);
        unsigned long long total = countSequences(-1, 0);
        cout << total << "\n";
        used.assign(n, false);
        vector<string> favorite;
        buildSequence(-1, 0, favorite);

        for (int i = 0; i < n; i++) {
            if (i > 0) cout << " ";
            cout << favorite[i];
        }
        cout << "\n";
    }
    return 0;
}