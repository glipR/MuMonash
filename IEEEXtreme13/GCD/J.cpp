#include <iostream>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

ll gcd(ll a, ll b) {
    if (b == 0) { return (a < 0) ? -a: a; }
    return gcd(b, a%b);
}

int main() {

    int n, k;
    cin >> n >> k;

    ll top_val = 100001;
    int possible[top_val];

    for (int i=0; i<top_val; i++) possible[i] = 0;
    for (int i=0; i<n; i++) {
        ll a;
        cin >> a;
        possible[a] = 1;
        for (int j=1; j<top_val; j++) {
            if (possible[j]) {
                ll res = gcd(j, a);
                // cerr << "gcd " << j << " " << a << " " << res << endl;
                if (possible[res] && possible[res] < k) {
                    possible[res] = min(possible[j]+1, possible[res]);
                } else possible[res] = possible[j]+1;
            }
        }
    }

    ll sum = 0;
    for (int i=0; i<20; i++) {
        // cerr << i << ": " << possible[i] << endl;
        if (possible[i] && possible[i] <= k) {
            sum++;
        }
    }

    cout << sum << endl;

    return 0;
}
