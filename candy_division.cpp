#include <iostream>
#include <cmath>
#include <set>

using namespace std;

int main() {
    long long n;
    cin >> n;

    set<long long> results;
    results.insert(0);

    for (long long d=1; d*d<=n; ++d) {
        if (n%d == 0) {
            long long a=d;
            long long b=n/d;

            if (a>1) results.insert(a-1);
            if (b>1) results.insert(b-1);
        }
    }

    bool first = true;
    for (long long k : results) {
        if (!first) cout << " ";
        cout << k;
        first = false;
    }
    cout << "\n";

    return 0;
}