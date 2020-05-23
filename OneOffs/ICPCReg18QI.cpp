#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

ll factorial[13];
ll fact(ll n) {
    if (factorial[n] != -1) return factorial[n];
    factorial[n] = fact(n-1) * n;
    return factorial[n];
}

ll choose(ll n, ll c) {
    return fact(n) / fact(c) / fact(n-c);
}

int main() {

    for (int i=0; i<13; i++) factorial[i] = -1;
    factorial[0] = 1;

    ll n, m;
    cin >> n >> m;
    if (m > n) m = n;

    ll ans = 0;
    // Go through all possible counting arrays.
    vector<int> bars(n-1, 0);
    vector<int> soln(n);
    bars[n-2] = -1;
    bool done = false;
    while (1) {
        int i=n-2;
        while (1) {
            bars[i] += 1;
            if (bars[i] == n+1) {
                bars[i] = n;
                if (i == 0) { done = true; break; }
                i--;
                continue;
            }
            for (int j=i+1; j<n-1; j++) { bars[j] = bars[i]; }
            break;
        }
        if (done) break;
        soln[0] = bars[0] - 0;
        for (int i=1; i<n-1; i++) { soln[i] = bars[i] - bars[i-1]; }
        soln[n-1] = n - bars[n-2];
        vector<int> count(m, 0);
        vector<pair<int, vector<int> > > non_zero_classes(m);
        for (int i=0; i<m; i++) non_zero_classes[i] = { 0, vector<int>() };
        for (int i=0; i<n; i++) {
            count[soln[i]%m] ++;
            if (soln[i] != 0) {
                non_zero_classes[i%m].first += soln[i];
                non_zero_classes[i%m].second.push_back(soln[i]);
            }
        }
        bool possible = true;
        for (int i=0; i<m; i++) {
            if (count[i] != non_zero_classes[i].first) possible = false;
        }
        if (!possible) continue;
        ll res = 1;
        for (int i=0; i<m; i++) {
            ll choices = non_zero_classes[i].first;
            for (int j=0; j<non_zero_classes[i].second.size()-1; j++) {
                res *= choose(choices, non_zero_classes[i].second[j]);
                choices -= non_zero_classes[i].second[j];
            }
        }
        ans += res;
    }

    cout << ans << endl;

    return 0;
}
