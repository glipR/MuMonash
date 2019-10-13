#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

#define X first
#define Y second

using namespace std;

struct quad {
    int a, b, c, d;
    quad (int w, int x, int y, int z) : a(w), b(x), c(y), d(z) {}
    bool const operator < (const quad &other) const {
        return d > other.d;
    }
};

typedef vector<int> vi;
typedef vector<vi> vvi;

template<typename T = int> struct LCA {
    const int LOGN = 20;
    int n; vi par, lvl; vvi anc; vector<T> len; vector<vector<pair<int, T> > > adj;
    void dfs (int u, int p, int l, T d) {
        par[u] = p, lvl[u] = l, len[u] = d;
        for (auto v: adj[u]) if (v.X != p) dfs(v.X, u, l+1, d+v.Y);
    }
    LCA (int n): n(n), par(n), lvl(n), len(n), adj(n) {}
    void add_edge(int u, int v, T w = 1) {
        adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
    }
    void build(int root = 0) {
        dfs(root, -1, 0, 0), anc.assign(n, vi(LOGN, -1));
        for (int i=0; i<n; i++) anc[i][0] = par[i];
        for (int k=1; k<LOGN; k++) for (int i=0; i<n; i++)
            if (anc[i][k-1] != -1) anc[i][k] = anc[anc[i][k-1]][k-1];
    }
    int query(int u, int v) {
        if (lvl[u] > lvl[v]) swap(u, v);
        for (int k=LOGN - 1; k >= 0; k--)
            if (lvl[v] - (1 << k) >= lvl[u]) v = anc[v][k];
        if (u == v) return v;
        for (int k=LOGN - 1; k >= 0; k--) {
            if (anc[u][k] == anc[v][k]) continue;
            u = anc[u][k], v = anc[v][k];
        }
        return par[u];
    }
    T dist(int u, int v) {
        return len[u] + len[v] - 2 * len[query(u, v)];
    }
};

int main() {

    int n, m;
    cin >> n >> m >> ws;

    LCA<int> sol(n);

    int colours[n];
    vi used_in[m];
    bool used[m];

    for (int i=0; i<m; i++) {
        used[i] = false;
    }

    for (int i=0; i<n; i++) {
        cin >> colours[i] >> ws;
        used_in[colours[i]-1].push_back(i);
    }
    for (int i=0; i<n-1; i++) {
        int a, b;
        cin >> a >> ws >> b >> ws;
        sol.add_edge(a-1, b-1, 1);
    }

    sol.build();

    vector<quad> actions;
    for (int i=0; i<m; i++) {
        if (used_in[i].size() == 0) {
            actions.push_back(quad(i, 0, 0, n+1));
            continue;
        }
        int dist = -1;
        int num1 = -1;
        for (auto idx: used_in[i]) {
            // cerr << idx << ' ' << used_in[i][0] << endl;
            int ndist = sol.dist(idx, used_in[i][0]);
            if (ndist > dist) {
                dist = ndist;
                num1 = idx;
            }
        }
        dist = -1;
        int num2 = -1;
        for (auto idx: used_in[i]) {
            int ndist = sol.dist(idx, num1);
            if (ndist > dist) {
                dist = ndist;
                num2 = idx;
            }
        }
        actions.push_back(quad(i, num1, num2, dist));
    }

    sort(actions.begin(), actions.end());

    for (quad t: actions) {
        cout << t.a + 1 << ' ' << t.b + 1 << ' ' << t.c + 1 << endl;
    }

    return 0;
}
