// MuMonash

#include <iostream>
#include <vector>

#define INF 1000000007

using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;

struct SCC {
    int n, comp; vvi g, gt; vi seq, vis;
    void dfs(int u, const vvi &adj) {
        for (int v: adj[u]) {
            if (vis[v] == -1) { vis[v] = comp; dfs(v, adj); }
        }
        seq.push_back(u);
    }
    SCC (int n): n(n), g(n), gt(n) { }
    void add_edge(int u, int v) { g[u].push_back(v); gt[v].push_back(u); }
    pair<int, vi> find_SCC() {
        vis.assign(n, -1); comp=0;
        for (int i=0; i<n; i++) if (vis[i] == -1) { vis[i] = comp; dfs(i, g); }
        vis.assign(n, -1); comp=0;
        for (int i=n-1; i >= 0; i--) {
            int u = seq[i];
            if (vis[u] == -1) { vis[u] = comp; dfs(u, gt); comp++; }
        }
        return {comp, vis};
    }
};

int main() {

    int n, m;
    cin >> n >> ws;

    SCC scc(n);

    int weights[n];
    for (int i=0; i<n; i++) {
        cin >> weights[i] >> ws;
    }

    cin >> m;
    pii edges[m];
    for (int i=0; i<m; i++) {
        cin >> edges[i].first >> edges[i].second >> ws;
        edges[i].first--; edges[i].second--;
        scc.add_edge(edges[i].first, edges[i].second);
    }

    pair<int, vi> info = scc.find_SCC();
    vi component_weights(info.first);
    vi component_ways(info.first);
    component_weights.assign(info.first, INF);
    component_ways.assign(info.first, 1);
    for (int i=0; i<n; i++) {
        // cerr << "Vertex " << i+1 << " is in component " << info.second[i] << endl;
        if (weights[i] < component_weights[info.second[i]]) {
            component_weights[info.second[i]] = weights[i];
            component_ways[info.second[i]] = 1;
        } else if (weights[i] == component_weights[info.second[i]]) {
            component_ways[info.second[i]] += 1;
        }
    }

    ll s=0;
    ll ways=1;
    for (int i=0; i<info.first; i++) {
        s += component_weights[i];
        ways *= component_ways[i];
        ways %= INF;
    }

    cout << s << ' ' << ways << endl;

    return 0;
}
