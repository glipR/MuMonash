// MuMonash
// https://codeforces.com/problemset/problem/1228/C
// WA, but ACs all samples :thinking:

#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

typedef long long ll;
typedef vector<ll> vll;

ll MOD = 1000000007;

ll expmod(ll a, ll b, ll m) {
    ll res=1%m; a %= m;
    for (; b; b /= 2) {if (b&1) res=res*a%m; a=a*a%m; }
    return res;
}

int main() {

    ll MAXFAC = 1000000;

    vector<bool> isprime;
    isprime.assign(MAXFAC+1, 1); isprime[0] = isprime[1] = 0;
    for (ll i = 2; i <= MAXFAC; ++i) if (isprime[i])
        for (ll j = i*i; j <= MAXFAC; j+= i) isprime[j] = 0;

    cerr << "Generated primes" << endl;

    // We now have all possible prime factors (at least on one side) of x.
    ll x, n;
    cin >> x >> ws >> n >> ws;

    vll primes;

    cerr << "Generating factors." << endl;

    for (int i=1; i<= MAXFAC; i++) {
        if (isprime[i]) {
            if (x % i == 0) {
                cerr << i << " divides " << x << endl;
                primes.push_back(i);
                while (x % i == 0) {
                    x /= i;
                }
            }
        }
    }

    if (x != 1) {
        // x is prime.
        primes.push_back(x);
    }

    ll res = 1;
    for (auto p: primes) {
        double tmp = p;
        while (tmp < n+1) {
            res *= expmod(p, n / tmp, MOD);
            cerr << res << endl;
            res %= MOD;
            tmp *= p;
        }
    }

    cout << res << endl;

    return 0;
}
