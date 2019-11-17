#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

vector<pair<ll, ll> > slow_factors(ll n) {
    vector<pair<ll, ll> > res;
    for (ll i=2; i*i <= n; ++i) if (n % i == 0) {
        res.push_back({i, 0});
        while (n % i == 0) { n /= i; res[res.size() - 1].second++;  };
    }
    if (n > 1) res.push_back({n, 1});
    return res;
}

int main() {

    ll a;
    cin >> a;

    vector<pair<ll, ll> > factors = slow_factors(a);

    ll amount = 1;
    for (auto f: factors) {
        amount *= (f.second + 1);
    }

    cout << amount - 1 << endl;

    return 0;
}
