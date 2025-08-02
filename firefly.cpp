#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, H;
    cin >> N >> H;
    
    const int HALF = N / 2;
    vector<int> stalagmites(HALF);
    vector<int> stalactites(HALF);
    
    for (int i = 0; i < HALF; ++i) {
        cin >> stalagmites[i];
        cin >> stalactites[i];
    }

    sort(stalagmites.begin(), stalagmites.end());
    sort(stalactites.begin(), stalactites.end());

    int min_obstacles = N + 1;
    int count = 0;

    for (int h = 1; h <= H; ++h){
        int bottom = stalagmites.end() - lower_bound(stalagmites.begin(), stalagmites.end(), h);
        int top = stalactites.end() - lower_bound(stalactites.begin(), stalactites.end(), H - h + 1);

        int total = bottom + top;

        if (total < min_obstacles){
            min_obstacles = total;
            count = 1;
        } else if (total == min_obstacles){
            ++count;
        }
    }
    cout << min_obstacles << " " << count << endl;

    return 0;
}