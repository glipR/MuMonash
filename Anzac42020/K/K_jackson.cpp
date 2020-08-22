// MuMonash

#include <cstdio>
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
typedef vector<ll> vi;
typedef vector<vector<ll> > vvi;

struct BipartiteMatching {
    ll L, R, p; vi m, used, d; vvi adj; queue<ll> q;
    bool bfs() {
        for (ll v=0; v<R; v++) if (!used[v]) d[v] = p, q.push(v);
        while (!q.empty()) {
            ll v = q.front(); q.pop();
            if (d[v] != d[R]) for (ll u: adj[v]) if (d[m[u]] < p)
                d[m[u]] = d[v] + 1, q.push(m[u]);
        }
        return d[R] >= p;
    }
    ll dfs(ll v) {
        if (v == R) return 1;
        for (ll u: adj[v]) if (d[m[u]] == d[v] + 1 && dfs(m[u])) return m[u] = v, 1;
        d[v] = d[R]; return 0;
    }
    BipartiteMatching(ll L, ll R): L(L), R(R), d(R+1), adj(R) {}
    void add_edge(ll u, ll v) { adj[v].push_back(u); }
    pair<ll, vi> match() {
        ll res = 0; m.assign(L, R), used.assign(R+1, 0);
        for (p=0; bfs(); p = d[R] + 1) for (ll v=0; v<R; v++)
            if (!used[v] && dfs(v)) used[v] = 1, res++;
        replace(m.begin(), m.end(), R, (ll)(-1)); return {res, m};
    }
};

int main() {

    map<ll, ll> results = map<ll, ll>();
    map<ll, ll> mapBack = map<ll, ll>();

    vector<pii> ps = vector<pii>();

    ll res_no = 0;

    ll n;
    cin >> n >> ws;
    for (ll i=0; i<n; i++) {
        ll a, b;
        cin >> a >> b >> ws;
        ps.push_back({a, b});
        if (results.count(a*b) == 0) {
            results[a*b] = res_no++;
            mapBack[res_no-1] = a*b;
        }
        if (results.count(a-b) == 0) {
            results[a-b] = res_no++;
            mapBack[res_no-1] = a-b;
        }
        if (results.count(a+b) == 0) {
            results[a+b] = res_no++;
            mapBack[res_no-1] = a+b;
        }
    }

    BipartiteMatching bm = BipartiteMatching(n, res_no);
    ll j=0;
    for (auto r : ps) {
        bm.add_edge(j, results[r.first * r.second]);
        bm.add_edge(j, results[r.first - r.second]);
        bm.add_edge(j, results[r.first + r.second]);
        j++;
    }

    pair<ll, vi> res = bm.match();
    if (res.first < n) {
        cout << "impossible" << endl;
    } else {
        for (ll i=0; i<n; i++) {
            ll r = mapBack[res.second[i]];
            if (ps[i].first * ps[i].second == r) {
                cout << ps[i].first << " * " << ps[i].second << " = " << r << endl;
            } else {
                if (ps[i].first - ps[i].second == r) {
                    cout << ps[i].first << " - " << ps[i].second << " = " << r << endl;
                }
                else {
                    if (ps[i].first + ps[i].second == r) {
                        cout << ps[i].first << " + " << ps[i].second << " = " << r << endl;
                    }
                }
            }
        }
    }


    return 0;
}
