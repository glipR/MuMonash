// Team Name (Monash)
// WA (Overlapping primes)

#include <bits/stdc++.h>
using namespace std;

#define me (*this)
#define debug(a) cerr << #a << " = " << (a) << endl;
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
typedef long long ll;
typedef pair<int, int> pii;

ll gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) { y = 0; x = (a < 0) ? -1 : 1; return (a < 0) ? -a : a; }
    else { ll g = gcd(b, a%b, y, x); y -= a/b*x; return g; }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n = 10000001;
    vector<bool> is_prime;
    is_prime.assign(n+1, 1); is_prime[0] = is_prime[1] = 0;
    for (ll i=2; i * i <= n; ++i) if (is_prime[i])
    for (ll j=i*i; j <= n; j += i) is_prime[j] = 0;
    // For this example, 1 is fine.

    int cases;
    cin >> cases >> ws;

    for (int c=0; c<cases; c++) {
        double x, y;
        cin >> x >> y >> ws;
        ll ax = round(x * 100000);
        ll ay = round(y * 100000);
        ll u, v, g;
        // cout << ax << ' ' << ay << endl;
        g = gcd(ax, ay, u, v);
        // cout << g << endl;
        ax /= g;
        ay /= g;
        //cout << ax << ' ' << ay << endl;
        if (is_prime[ax] && is_prime[ay]) {
            cout << ax << ' ' << ay << endl;
        } else {
            cout << "impossible" << endl;
        }
    }

    return 0;
}
