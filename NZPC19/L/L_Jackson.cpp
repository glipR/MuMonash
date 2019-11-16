#include <iostream>

using namespace std;

typedef long long ll;

int main() {

    ll l, d, u, s, K;
    cin >> l >> d >> u >> s >> K;

    // Fill the DP.
    ll DP[l+1][d+1][u+1][s+1];
    for (int i=0; i<=d; i++) for (int j=0; j<=u; j++) for (int k=0; k<=s; k++) DP[0][i][j][k] = 0;
    DP[0][0][0][0] = 1;

    for (int length=1; length<=l; length++) {
        // DP[length] solve.
        for (int i=0; i<=d; i++) for (int j=0; j<=u; j++) for (int k=0; k<=s; k++) {
            ll amount = 0;
            // Try using digit.
            amount += 10 * DP[length-1][max(i-1, 0)][j][k];
            // Try using uppercase.
            amount += 26 * DP[length-1][i][max(j-1, 0)][k];
            // Try using lowercase.
            amount += 26 * DP[length-1][i][j][max(k-1, 0)];
            DP[length][i][j][k] = amount;
        }
    }

    // Now we just need to figure out where to stop.
    char soln[l+1];
    soln[l] = 0;

    int cur_d = d, cur_u = u, cur_s = s;
    for (int length=l; length>0; length--) {
        // Should we use a digit, lowercase, or uppercase?
        // cerr << length << " " << cur_d << " " << cur_u << " " << cur_s << " " << K << endl;
        if (10 * DP[length-1][max(cur_d-1, 0)][cur_u][cur_s] >= K) {
            cur_d = max(cur_d-1, 0);
            // cerr << "Digit. " << DP[length-1][cur_d][cur_u][cur_s] << endl;
            // What digit?
            soln[l - length] = "0123456789"[(K-1) / DP[length-1][cur_d][cur_u][cur_s]];
            K = ((K-1) % DP[length-1][cur_d][cur_u][cur_s]) + 1;
            continue;
        } else { K -= 10 * DP[length-1][max(cur_d-1, 0)][cur_u][cur_s]; }
        if (26 * DP[length-1][cur_d][max(cur_u-1, 0)][cur_s] >= K) {
            cur_u = max(cur_u-1, 0);
            // cerr << "Upper. " << DP[length-1][cur_d][cur_u][cur_s] << endl;
            // What uppercase?
            soln[l - length] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[(K-1) / DP[length-1][cur_d][cur_u][cur_s]];
            K = ((K-1) % DP[length-1][cur_d][cur_u][cur_s]) + 1;
            continue;
        } else { K -= 26 * DP[length-1][cur_d][max(cur_u-1, 0)][cur_s]; }
        if (26 * DP[length-1][cur_d][cur_u][max(cur_s-1, 0)] >= K) {
            cur_s = max(cur_s-1, 0);
            // cerr << "Lower. " << DP[length-1][cur_d][cur_u][cur_s] << endl;
            // What lowercase?
            soln[l - length] = "abcdefghijklmnopqrstuvwxyz"[(K-1) / DP[length-1][cur_d][cur_u][cur_s]];
            K = ((K-1) % DP[length-1][cur_d][cur_u][cur_s]) + 1;
            continue;
        } else { K -= 26 * DP[length-1][cur_d][cur_u][max(cur_s-1, 0)]; /* Should never happen */}
    }

    cout << soln << endl;

    return 0;
}
