#include <iostream>
#include <vector>

using namespace std;

int MOD = 1000000007;

int main() {

    int n, k;

    cin >> k >> n >> ws;

    int wait[26];
    for (int i=0; i<26; i++) {
        cin >> wait[i] >> ws;
    }

    int plan[k];
    for (int i=0; i<k; i++) {
        char c;
        cin >> c >> ws;
        plan[i] = ((int)c - (int)'A');
    }

    int value[n];
    for (int i=0; i<n; i++) {
        char c;
        cin >> c >> ws;
        value[i] = ((int)c - (int)'A');
    }

    // With i days remaining, how many ways can I see the remaining k - j bands?
    int DP[n+1][k+1];

    for (int i=0; i<=n; i++) {
        DP[i][k] = 1;
        if (i==0)
        for (int j=k-1; j>=0; j--) {
            DP[i][j] = 0;
        }
        else
        for (int j=k-1; j>=0; j--) {
            if (plan[j] == value[n - i] && i-wait[plan[j]]-1 >= 0) {
                DP[i][j] = DP[i-1][j] + DP[i-wait[plan[j]]-1][j+1];
                DP[i][j] %= MOD;
            } else if (plan[j] == value[n - i] && j+1 == k) {
                DP[i][j] = DP[i-1][j] + 1;
                DP[i][j] %= MOD;
            } else {
                DP[i][j] = DP[i-1][j];
            }
        }
    }

    cout << DP[n][0] << endl;

    return 0;
}
