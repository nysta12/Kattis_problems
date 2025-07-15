#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;

    while (cin >> n && n != 0) {
        vector<double> rate(n);
        for (int i = 0; i < n; ++i) {
            cin >> rate[i];
        }
        vector<double> cad(n + 1, 0.0);
        vector<double> usd(n + 1, 0.0);

        cad[0] = 1000.0;

        for (int i = 0; i < n; ++i) {
            cad[i + 1] = max(cad[i + 1], cad[i]);
            usd[i + 1] = max(usd[i + 1], usd[i]);

            double cad_to_usd = floor((cad[i] * 0.97 / rate[i]) * 100.0) / 100.0;
            usd[i + 1] = max(usd[i + 1], cad_to_usd);

            double usd_to_cad = floor((usd[i] * 0.97 * rate[i]) * 100.0) / 100.0;
            cad[i + 1] = max(cad[i + 1], usd_to_cad);
        }
        cout << fixed << setprecision(2) << cad[n] << endl;
    }
    return 0;
}