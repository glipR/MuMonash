// MuMonash

#include <cstdio>
#include <string>
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <limits>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
typedef vector<ll> vi;
typedef vector<vector<ll> > vvi;

const ll MAP_SIZE = 51;
const ll MAXN = 51;
char MAP[MAP_SIZE][MAP_SIZE];

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

ll key (ll i, ll j, ll k) {
    return i + j * MAP_SIZE + k * MAP_SIZE * MAP_SIZE;
}

int main() {

    ll n, m;
    cin >> n >> m >> ws;
    for (ll i=0; i<MAP_SIZE; i++) for (ll j=0; j<MAP_SIZE; j++) MAP[i][j] = '#';
    for (ll i=0; i<n; i++) {
        for (ll j=0; j<n; j++) {
            cin >> MAP[i][j];
        }
        cin >> ws;
    }
    string instruction;
    cin >> instruction >> ws;

    pii start;
    pii end;
    for (ll i=0; i<MAP_SIZE; i++) for (ll j=0; j<MAP_SIZE; j++) if (MAP[i][j] == 'R') start = {i, j};
    for (ll i=0; i<MAP_SIZE; i++) for (ll j=0; j<MAP_SIZE; j++) if (MAP[i][j] == 'E') end = {i, j};

    vector<pii> directions = vector<pii>();
    directions.push_back({0, 1});
    directions.push_back({0, -1});
    directions.push_back({1, 0});
    directions.push_back({-1, 0});

    BellmanFord<ll> bf = BellmanFord<ll>(MAP_SIZE * MAP_SIZE * (instruction.size()+1));

    for (ll i=0; i<MAP_SIZE; i++) for (ll j=0; j<MAP_SIZE; j++) for (ll k=0; k<(instruction.size()+1); k++) {
        if (MAP[i][j] == '#') continue;
        ll vertex = key(i, j, k);
        if (MAP[i][j] == 'E') {
            // We need to make sure you have distance 0. So add a length 0 edge from src to you.
            if (k != 0) {
                ll v2 = key(i, j, k-1);
                bf.add_edge(vertex, v2, (ll)0);
                bf.add_edge(v2, vertex, (ll)0);
            }
        }
        for (pii dir : directions) {
            ll a = i + dir.first;
            ll b = j + dir.second;
            if (0 <= a && a < n && 0 <= b && b < n && MAP[a][b] != '#') {
                ll v2 = key(a, b, k);
                bf.add_edge(vertex, v2, (ll)1);
            }
        }
        // Let the instruction be used.
        if (k < instruction.size()) {
            ll a, b;
            if (instruction[k] == 'U') { a = i - 1; b = j; }
            if (instruction[k] == 'D') { a = i + 1; b = j; }
            if (instruction[k] == 'L') { a = i; b = j - 1; }
            if (instruction[k] == 'R') { a = i; b = j + 1; }
            if (0 <= a && a < n && 0 <= b && b < n && MAP[a][b] != '#') {
                ll v2 = key(a, b, k+1);
                bf.add_edge(vertex, v2, (ll)0);
                bf.add_edge(v2, vertex, (ll)0);
            }
            else {
                ll v2 = key(i, j, k+1);
                bf.add_edge(vertex, v2, (ll)0);
                bf.add_edge(v2, vertex, (ll)0);
            }
        }
    }

    pair<vi, vi> res = bf.shortest_paths(key(end.first, end.second, (ll)0));

    ll s = key(start.first, start.second, (ll)0);

    cout << res.first[s] << endl;

    return 0;
}
