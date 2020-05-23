// MuMonash
// Insight #1: PQ^-1 is preserved through addition an multiplication.
// Insight #2: A matching has a recursive definition where we pick an edge and recurse.

#include <iostream>
#include <vector>
#include <bitset>

#define X first
#define Y second

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll MOD = 1e9 + 7;

ll expmod(ll a, ll b, ll m) {
    ll res = 1%m; a %= m;
    for(; b; b /= 2) { if (b&1) res = res*a%m; a=a*a%m; }
    return res;
}

ll gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        y = 0;
        x = (a < 0) ? -1 : 1;
        return a > 0 ? a : -a;
    }
    else {
        ll g = gcd(b, a%b, y, x);
        y -= a/b*x;
        return g;
    }
}

ll inv(ll a, ll m) { ll x, y; gcd(m, a, x, y); return ((y % m) + m) % m; }

int n;
ll probs[10][10];

// Bitset DP
ll sol[1 << 15];

ll solve(ll bits) {
    // First check DP
    if (sol[bits] != -1) return sol[bits];
    cerr << bitset<14>(bits) << endl;
    // Next, calculate each sub-matching probability.
    // Find the first non-targeted left hand vertex.
    for (int i=0; i<n; i++) if (bits & (1 << i)) {
        vector<pii> possibles;
        for (int j=n; j<2*n; j++) if (bits & (1 << j)) {
            cerr << "Picking edge (" << i << ", " << j << ")" << endl;
            ll new_sol = bits;
            new_sol -= (1 << i) + (1 << j);
            possibles.push_back({j-n, solve(new_sol)});
        }
        ll res = 0;
        // Try all combinations of submatchings.
        for (int k=1; k<(1 << possibles.size()); k++) {
            ll cur = 1;
            int amount = 0;
            cerr << "Case " << bitset<7>(k) << endl;
            for (int j=0; j<possibles.size(); j++) if (k & (1 << j)) {
                cerr << "Considering matching where edge (" << i << ", " << possibles[j].X << ") is picked" << endl;
                cerr << probs[i][possibles[j].X] << " " << possibles[j].Y << endl;
                amount ++;
                cur = (((cur * probs[i][possibles[j].X]) % MOD) * possibles[j].Y) % MOD;
            }
            if (amount % 2) res += cur;
            else res -= cur;
            res %= MOD;
        }
        sol[bits] = res;
        return sol[bits];
    }
    return 1;
}

int main() {

    for (int i=0; i<1<<15; i++) sol[i] = -1;

    cin >> n;

    ll inv_100 = inv(100, MOD);

    for (int i=0; i<n; i++) for (int j=0; j<n; j++) {
        cin >> probs[i][j];
        probs[i][j] = (probs[i][j] * inv_100) % MOD;
    }

    ll res = solve((1 << 2 * n) - 1);
    if (res < 0) res += MOD;

    cout << res << endl;

    return 0;
}
