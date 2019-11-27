#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;

ll DP[201][201];
vector<ll> values(201);

ll n, b;

ll solve(int i, int j) {
    if (DP[i][j] != -1) return DP[i][j];
    if (j == 0) return -2;
    ll best = (values[n-1] - values[i]) * (values[n-1] - values[i]);
    for (int x=i+1; x<n; x++) {
        if (solve(x, j-1) == -2) continue;
        best = min(best, (values[x-1] - values[i]) * (values[x-1] - values[i]) + solve(x, j-1));
    }
    DP[i][j] = best;
    return DP[i][j];
}

int main() {
    for (int i=0; i<201; i++) for (int j=0; j<201; j++) DP[i][j] = -1;
    cin >> n >> b;
    for (int i=0; i<n; i++) { cin >> values[i]; }
    sort(values.begin(), values.begin() + n);
    /*for (int i=0; i<n; i++) { cerr << values[i] << " "; }
    cerr << endl;*/
    cout << solve(0, b) << endl;
}
