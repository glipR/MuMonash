// MuMonash

// Bit of a weird problem, but the thing to note here is that for n <= 10^9, the maximum distance between primes is <300.
// Therefore, we can search down until we find some prime p, <= n. (300 * log(n))
// Then, we want to decompose the remainder, n-p, into 0-2 more prime numbers.
// We know n-p is <300, and so we just try every prime x, and see if n - p - x is also prime.

#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef ll big;

ll expmod(big a, big b, big m) {
    big res=1%m; a %= m;
    for(; b; b/=2) {if (b&1) res=res*a%m; a=a*a%m; }
    return res;
}

vi val = {2, 13, 23, 1662803};

bool is_prime(ll n) {
    if (n < 2) return false;
    ll s = __builtin_ctzll(n-1), d = (n-1) >> s;
    for (int v: val) {
        if (v >= n) break;
        ll x = expmod(v, d, n);
        if (x == 1 || x == n-1) continue;
        for (ll r=1; r<s; r++) if ((x = ((big(x)*x) % n)) == n-1) goto nextPr;
        return false;
        nextPr:;
    }
    return true;
}

int main() {

    ll n;
    cin >> n;

    // Find the first prime below or at n.
    ll x = n;
    while (!is_prime(x)) x--;
    if (x == n) {
        cout << 1 << endl << n << endl;
    } else {
    // Find the prime decomposition of n - x.
    ll res = n - x;
    for (int a=0; a<res; a++) {
        if (a != 0 && !is_prime(a)) continue;
        if (!is_prime(res - a)) continue;
        if (a == 0) {
            cout << 2 << endl << x << " " << res << endl;
        }
        else {
            cout << 3 << endl << x << " " << res - a << " " << a << endl;
        }
        break;
    }
    }

    return 0;
}
