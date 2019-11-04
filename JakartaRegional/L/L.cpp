#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <numeric>

#define X first
#define Y second

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;

struct BipartiteMatchingCap {
    int L, R, p; vi m, used, d, capacity; vvi adj; queue<int> q;
    bool bfs() {
        for (int v=0; v<R; v++) if (used[v] < capacity[v]) d[v] = p, q.push(v);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            if (d[v] != d[R]) for (int u: adj[v]) if (d[m[u]] < p)
                d[m[u]] = d[v] + 1, q.push(m[u]);
        }
        return d[R] >= p;
    }
    int dfs(int v) {
        if (v == R) return 1;
        for (int u : adj[v]) if (d[m[u]] == d[v] + 1 && dfs(m[u])) return m[u] = v, 1;
        d[v] = d[R]; return 0;
    }
    BipartiteMatchingCap(int L, int R): L(L), R(R), d(R+1), adj(R), capacity(R, 1) {}
    void add_edge(int u, int v) {
        adj[v].push_back(u);
    }
    pair<int, vi> match() {
        int res = 0; m.assign(L, R), used.assign(R+1, 0);
        for (p=0; bfs(); p = d[R]+1) for (int v=0; v<R; v++)
            if ((used[v] < capacity[v]) && dfs(v)) used[v]++, res++;
        replace(m.begin(), m.end(), R, -1); return {res, m};
    }
};

template<typename T = int> struct LCA {
    const int LOGN = 20;
    int n; vi par, lvl; vvi anc; vector<T> len; vector<vector<pair<int, T> > > adj;
    void dfs(int u, int p, int l, T d) {
        par[u] = p, lvl[u] = l, len[u] = d;
        for (auto v : adj[u]) if (v.X != p) dfs(v.X, u, l+1, d+v.Y);
    }
    LCA(int n) : n(n), par(n), lvl(n), len(n), adj(n) {}
    void add_edge(int u, int v, T w = 1) {
        adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
    }
    void build(int root = 0) {
        dfs(root, -1, 0, 0), anc.assign(n, vi(LOGN, -1));
        for(int i=0; i<n; i++) anc[i][0] = par[i];
        for (int k=1; k< LOGN; k++) for (int i=0; i<n; i++)
            if (anc[i][k-1] != -1) anc[i][k] = anc[anc[i][k-1]][k-1];
    }
    int query(int u, int v) {
        if (lvl[u] > lvl[v]) swap(u, v);
        for (int k=LOGN-1; k >= 0; k--)
            if (lvl[v] - (1 << k) >= lvl[u]) v = anc[v][k];
        if (u == v) return u;
        for (int k=LOGN-1; k >= 0; k--) {
            if (anc[u][k] == anc[v][k]) continue;
            u = anc[u][k]; v = anc[v][k];
        }
        return par[u];
    }
};

struct UnionFind {
    int n; vi A, s, rank;
    UnionFind(int n) : n(n), A(n), s(n, 1), rank(n) { iota(A.begin(), A.end(), 0); }
    int find(int x) { return A[x] == x ? x : A[x] = find(A[x]); }
    bool merge(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) swap(x, y);
        A[y] = x; s[x] += s[y]; n--;
        if (rank[x] == rank[y]) rank[x]++;
        return true;
    }
};

int main() {

    int n, k;
    cin >> n >> k;
    int pref[n];

    unordered_map<ll, int> mat_workers;
    int p=0;
    vector<ll> mat[n];
    for (int i=0; i<n; i++) {
        cin >> pref[i];
        pref[i]--;
        int mats;
        cin >> mats;
        mat[i].assign(mats, -1);
        for (int j=0; j<mats; j++) {
            cin >> mat[i][j];
            if (mat_workers.count(mat[i][j]) == 0) {
                mat_workers[mat[i][j]] = p++;
            }
        }
    }

    ll workers[k];
    for (int i=0; i<k; i++) {
        cin >> workers[i];
        if (mat_workers.count(workers[i]) == 0) {
            mat_workers[workers[i]] = p++;
        }
    }

    unordered_map<ll, int> mat_index;
    pair<ll, vi> ordered_materials[mat_workers.size()];
    int i=0;
    for (auto key: mat_workers) {
        mat_index[key.first] = i;
        ordered_materials[i++] = {key.first, vi()};
    }

    for (int i=0; i<k; i++) {
        ordered_materials[mat_index[workers[i]]].Y.push_back(i);
    }


    // First: Figure out an edge that causes the cycle.
    UnionFind u(n);
    int cycle_creator = -1;
    for (int i=0; i<n; i++) {
        if (!u.merge(i, pref[i])) {
            cycle_creator = i;
            break;
        }
    }

    // Second: Figure out all edges in the cycle.
    LCA<int> tree(n);
    for (int i=0; i<n; i++) {
        if (i == cycle_creator) continue;
        tree.add_edge(i, pref[i]);
    }
    tree.build();

    int par = tree.query(cycle_creator, pref[cycle_creator]);
    bool cycle_prefs[n];
    for (int i=0; i<n; i++) cycle_prefs[i] = false;
    cycle_prefs[cycle_creator] = true;
    int cur = cycle_creator;
    while (tree.lvl[cur] > tree.lvl[par]) {
        if (pref[cur] == tree.par[cur]) cycle_prefs[cur] = true;
        else cycle_prefs[tree.par[cur]] = true;
        cur = tree.par[cur];
    }
    cur = pref[cycle_creator];
    while (tree.lvl[cur] > tree.lvl[par]) {
        if (pref[cur] == tree.par[cur]) cycle_prefs[cur] = true;
        else cycle_prefs[tree.par[cur]] = true;
        cur = tree.par[cur];
    }

    // Now cycle_prefs[i] is true when i's preference is part of the cycle.

    // Make a matching with all edges (including cycles)
    BipartiteMatchingCap bm(n, mat_index.size());
    for (int i=0; i<mat_index.size(); i++) {
        // cerr << "index " << i << " val " << ordered_materials[i].X << " amount " << ordered_materials[i].Y.size() << endl;
        bm.capacity[i] = ordered_materials[i].Y.size();
    }
    for (int i=0; i<n; i++) {
        for (auto m: mat[i]) {
            bm.add_edge(i, mat_index[m]);
            // cerr << "Adding edge " << i << " " << mat_index[m] << endl;
        }
    }

    auto match = bm.match();
    //cerr << match.X << endl;

    bool bad = false;
    if (match.X < n-1) {
        bad = true;
    } else if (match.X == n-1) {
        int wrong;
        for (int i=0; i<n; i++) if (match.Y[i] == -1) {
            wrong = i;
        }
        /*for (int i=0; i<n; i++) {
            cerr << match.Y[i] << " ";
        }
        cerr << endl;*/
        if (!cycle_prefs[wrong]) {
            // See if there is a cyclic assignment we can remove.
            vector<bool> acceptable(mat_index.size(), false);
            for (ll m: mat[wrong]) { acceptable[mat_index[m]] = true; }
            for (int i=0; i<n; i++) {
                if (cycle_prefs[i]) {
                    if (acceptable[match.Y[i]]) {
                        swap(match.Y[i], match.Y[wrong]);
                        break;
                    }
                }
                bad = true;
            }
        }
    }

    if (bad) {
        cout << -1 << endl;
    } else {
        int worker_application[k];
        for (int i=0; i<k; i++) worker_application[i] = -1;
        int worker_index[mat_index.size()];
        for (int i=0; i<mat_index.size(); i++) worker_index[i] = 0;
        for (int i=0; i<n; i++) {
            if (match.Y[i] == -1) continue;
            worker_application[ordered_materials[match.Y[i]].Y[worker_index[match.Y[i]]]] = i;
            worker_index[match.Y[i]]++;
        }
        for (int i=0; i<k; i++) {
            if (worker_application[i] == -1) {
                cout << "0 0" << endl;
            } else {
                cout << worker_application[i] + 1 << " " << pref[worker_application[i]] + 1 << endl;
            }
        }
    }

    return 0;
}
