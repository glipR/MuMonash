// MuMonash
#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

#define pb(a) push_back(a)
#define X first
#define Y second

typedef long long ll;
typedef long double ld;
typedef vector<ll> vll;
typedef vector<vll> vvll;

ll gcd(ll a, ll b) {
    if (b == 0) return a > 0 ? a : -a;
    return gcd(b, a%b);
}

struct Tree {
    ll n;
    //                Node - Weight Pair.
    vector<vector<pair<ll, ll> > > adj;
    vector<bool> judge;
    vll par, par_len, min, above, below;

    Tree(ll x): n(x), adj(x), par(x, -1), par_len(x, -1), min(x, -2), above(x, -2), below(x, -2), judge(x, false) {}

    void add_edge(ll u, ll v, ll w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void set_judge(ll u) { judge[u] = true; }

    void dfs(ll e, ll p, ll d) {
        par[e] = p;
        par_len[e] = d;
        for (auto v: adj[e]) if (v.X != p) dfs(v.X, e, v.Y);
    }

    void build(ll root = 0) {
        dfs(root, -1, 0);
        gen_minims();
        gen_below(0);
        gen_above(0);
    }

    // NlogN time - Can make faster by using the same strategy as maximum calculation.
    void gen_minims() {
        priority_queue<pair<ll, ll> > pq;
        for (ll i=0; i<n; i++) if (judge[i]) {
            pq.push({0, i});
        }
        while (pq.size()) {
            auto e = pq.top(); pq.pop();
            if (min[e.Y] != -2) continue;
            min[e.Y] = -e.X;
            for (auto v: adj[e.Y]) if (min[v.X] == -2) {
                pq.push({- v.Y + e.X, v.X});
            }
        }
    }

    void gen_below(ll root) {
        ll best = judge[root] ? 0 : -1;
        for (auto v: adj[root]) if (v.X != par[root]) {
            gen_below(v.X);
            if (below[v.X] != -1) best = max(best, below[v.X]+v.Y);
        }
        below[root] = best;
    }

    void gen_above(ll root) {
        ll best = judge[root] ? 0 : -1;
        if (par[root] != -1) {
            if (above[par[root]] != -1) {
                best = max(best, above[par[root]] + par_len[root]);
            }
            for (auto v: adj[par[root]]) if (v.X != root && v.X != par[par[root]]) {
                if (below[v.X] != -1) {
                    best = max(best, below[v.X] + v.Y + par_len[root]);
                }
            }
        }
        above[root] = best;
        for (auto v: adj[root]) if (v.X != par[root]) {
            gen_above(v.X);
        }
    }
};

int main() {

    ll n, k;
    cin >> n >> k;
    Tree t(n);
    for (ll i=0; i<k; i++) {
        ll x;
        cin >> x;
        t.set_judge(x-1);
    }

    for (ll i=0; i<n-1; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        t.add_edge(a-1, b-1, c);
    }

    t.build();

    ld best = -1;
    ll x, y;

    for (int i=0; i<n; i++) {
        ll m1 = t.min[i];
        ll m2 = max(t.below[i], t.above[i]);
        ld ratio = ((ld) m1) / ((ld) m2);
        // cerr << "Results for " << i+1 << "J: " << t.judge[i] << " is min: " << m1 << " max: " << m2 << "(" << t.below[i] << ", " << t.above[i] << ")\n";
        // cerr << "Ratio for " << i+1 << " is " << ratio << endl;
        if (ratio > best) {
            best = ratio;
            x = m1; y = m2;
        }
    }

    ll res = gcd(x, y);
    x /= res;
    y /= res;

    cout << x << "/" << y << endl;

    return 0;
}
