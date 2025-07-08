#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

typedef vector<int> vi;
vi match, visited;
vector<vi> vis_a_vis;

int n, m, a, b;

bool aug(int shooter, vi& visited){
    if (visited[shooter])
        return 0; 

    visited[shooter] = 1;
    for (auto &target : vis_a_vis[shooter]){
        if ((match[target] == -1) || aug(match[target], visited)){
            match[target] = shooter;                              
            return true;                                  
        }
    }
    return false;                                      
}

int max_match(int n){
    int matches = 0;

    for (int i = 1; i <= n; ++i){
        visited.assign(n + 1, 0);
        if (aug(i, visited))
            ++matches;
    }
    return matches;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    vis_a_vis.resize(n + 1);
    match.assign(n + 1, -1);

    for (int i = 0; i < m; ++i){
        cin >> a >> b;
        vis_a_vis[a].push_back(b);
        vis_a_vis[b].push_back(a);
    }

    if (max_match(n) != n){
        cout << "Impossible";
        return 0;
    }

    for (int i = 1; i <= n; ++i){
        cout << match[i] << "\n";
    }
    return 0;
}