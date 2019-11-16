// MuMonash

#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef long long ll;

int main() {

    int n, d, K;
    cin >> n >> d >> K;

    vi waves(n);
    for (int i=0; i<n; i++) { cin >> waves[i]; }

    // DP[i][j] = maximum fun given starting at
    int DP[n][d];

    // cerr << "i j DP[i][j]" << endl;
    for (int i=n-1; i>=0; i--) {
        for (int j=d-1; j>=0; j--) {
            int best = 0;
            // Try waiting.
            if (i != n-1) { best = max(best, DP[i+1][j]); }
            // Try leaving now.
            for (int k=1; k<=K; k++) {
                if ((i + 2 * k - 1 < n) && (k + j <= d)) {
                    // cerr << "Swimming " << k << " gives " << k * waves[i + 2 * k - 1] + ((i + 2 * k == n || k + j == d) ? 0 : DP[i + 2 * k][k + j]) << endl;
                    best = max(best, k * waves[i + 2 * k - 1] + ((i + 2 * k == n || k + j == d) ? 0 : DP[i + 2 * k][k + j]));
                }
            }
            DP[i][j] = best;
            // cerr << i << " " << j << " " << best << endl;
        }
    }

    cout << DP[0][0] << endl;

    return 0;
}
