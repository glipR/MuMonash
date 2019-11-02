#include <iostream>
#include <vector>

#define NOT_CALCULATED -1
#define IMPOSSIBLE -2
#define MAXN 100010

using namespace std;

typedef long long ll;

vector<ll> DP[MAXN];

int main() {

    ll n, k, g1, g2, g3;
    cin >> n >> k >> g1 >> g2 >> g3 >> ws;
    char values[n];
    int num_hash = 1;
    for (int i=0; i<n; i++) {
        cin >> values[i];
        if (values[i] == '#') num_hash++;
    }
    // Maximum possible Type 2 entries up till and including index i with j Type 3 entries.
    for (int i=0; i<n; i++) {
        DP[i].assign(num_hash, NOT_CALCULATED);
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<num_hash; j++) {
            ll best = i == 0 ? ( j == 0 ? 0 : IMPOSSIBLE ) : DP[i-1][j];
            if (i > 0 && ( j == 0 || ( i > 1 && DP[i-2][j] != IMPOSSIBLE))) {
                if (values[i] == '.' && values[i-1] == '.') {
                    if (i == 1 || DP[i-2][j] >= 0) {
                        best = max(best, (i == 1 ? 1 : (1 + DP[i-2][j])));
                    }
                }
            }
            if (i > 1 && j != 0) {
                if (values[i] == '.' && values[i-1] == '#' && values[i-2] == '.') {
                    if ((i == 2 && j == 1) || (i > 2 && DP[i-3][j-1] >= 0)) {
                        best = max(best, (i == 2 ? 0 : DP[i-3][j-1]));
                    }
                }
            }
            DP[i][j] = best;
        }
    }

    /*for (int i=0; i<n; i++) {
        for (int j=0; j<num_hash; j++) {
            cerr << DP[i][j] << " ";
        }
        cerr << endl;
    }*/

    // Try replacing type 2s with type 1s where applicable for each j.
    ll best_score = 0;
    for (int j=0; j<num_hash; j++) {
        if (DP[n-1][j] == IMPOSSIBLE) continue;
        ll tile1_remaining = k;
        ll remaining_blank = n - 3 * j - 2 * DP[n-1][j] - (num_hash - j - 1);
        ll diff = min(tile1_remaining, remaining_blank);
        tile1_remaining -= diff;
        if (2 * g1 > g2) {
            ll diff = min(tile1_remaining / 2, DP[n-1][j]);
            tile1_remaining -= 2*diff;
            DP[n-1][j] -= diff;
        }
        if (g1 > g2) {
            // Only 1 or 0.
            ll diff = min(tile1_remaining, DP[n-1][j]);
            tile1_remaining -= diff;
            DP[n-1][j] -= diff;
        }
        best_score = max(best_score, g1 * (k - tile1_remaining) + g2 * DP[n-1][j] + g3 * j);
    }

    cout << best_score << endl;

    return 0;
}
