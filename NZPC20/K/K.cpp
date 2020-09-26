// MuMonash

#include <cstdio>
#include <string>
#include <iostream>
#include <list>
#include <map>
#include <cmath>
#include <vector>
#include <limits>
#include <algorithm>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
typedef vector<ll> vi;
typedef vector<vector<ll> > vvi;

template <typename T> struct BellmanFord {
    typedef pair<T, ll> pti; vector<vector<pti> > adj;
    ll n, last = -1; const T INF = numeric_limits<T>::max() / 2;
    BellmanFord(ll n) : adj(n), n(n) {}
    void add_edge(ll u, ll v, T weight) { adj[u].emplace_back(weight, v); }
    pair<vector<T>, vi> shortest_paths(ll src) {
        vector<T> dist(n, INF); dist[src] = 0; vi pred(n, -1); last = 0;
        for (ll k = 0; k < n && last != -1; k++) { last = -1;
            for (ll u=0; u<n; u++) if (dist[u] < INF) for (auto &e : adj[u]) {
                ll v = e.second; T len = dist[u] + e.first;
                if (len < dist[v]) dist[v] = len, pred[v] = u, last = v;
            }
        }
        return {dist, pred};
    }
};

template <typename T> struct ContDijkstra {
    vector<vector<T> > adj;
    ll n; const T INF = numeric_limits<T>::max() / 2;
    vector<T> dist;
    vi pred;
    ContDijkstra(ll n) : adj(n), n(n) {
        dist = vector<T>(n, INF);
        dist[0] = 0;
    }
    void add_edge(ll u, ll v) {
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        vector<int> updating(0);
        if (dist[v] > dist[u] + 1) {
            dist[v] = dist[u] + 1;
            updating.push_back(v);
        }
        if (dist[u] > dist[v] + 1) {
            dist[u] = dist[v] + 1;
            updating.push_back(u);
        }
        while (updating.size() > 0) {
            vector<int> new_updating(0);
            for (auto k: updating) {
                for (auto j: adj[k]) {
                    if (dist[j] > dist[k] + 1) {
                        new_updating.push_back(j);
                        dist[j] = dist[k] + 1;
                    }
                }
            }
            updating = new_updating;
        }
    }
};

int main() {
    while (1) {
        int p, d;
        cin >> p >> d;
        double dist_sq = pow(d, 2);
        if (p == 0) break;
        BellmanFord<int> bf(p);
        vector<pair<double, double> > pond(0);
        for (int i=0; i<p; i++) {
            double x, y;
            cin >> x >> y;
            pond.push_back({x, y});
        }
        vector<pair<double, pair<int, int>> > edges(0);
        for (int i=0; i<p; i++) {
            for (int j=i+1; j<p; j++) {
                double dist = pow(pond[i].first - pond[j].first, 2) + pow(pond[i].second - pond[j].second, 2);
                if (dist <= dist_sq) {
                    edges.push_back({dist, {i, j}});
                    bf.add_edge(i, j, 1);
                    bf.add_edge(j, i, 1);
                }
            }
        }
        sort(edges.begin(), edges.end(), [](const pair<double, pair<int, int> > lhs, const pair<double, pair<int, int> > rhs) {
            return lhs.first > rhs.first;
        });

        auto res = bf.shortest_paths(0);
        int dist = res.first[1];
        // Now repeatedly add edges until this distance is possible.

        ContDijkstra<int> cd(p);
        for (int i=0; i<edges.size(); i++) {
            // cerr << edges[i].second.first << " " << edges[i].second.second << endl;
            cd.add_edge(edges[i].second.first, edges[i].second.second);
            if (cd.dist[1] == dist) {
                cout << dist << " " << fixed << setprecision(1) << sqrt(edges[i].first) << endl;
                break;
            }
        }
    }

    return 0;
}
