// MuMonash

#include <string.h>
#include <vector>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ccomplex>
#include <cstdbool>
#include <algorithm>
#include <iostream>

using namespace std;

#define me (*this)
#define debug(a) cerr << #a << " = " << (a) << endl;
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
typedef long long ll;
typedef pair<int, int> pii;
#define X first
#define Y second

template<typename T = int> struct LCA {
    const int LOGN = 20;
    int n;
    vector<int> par, lvl;
    vector<vector<int>> anc;
    vector<T> len;
    vector<vector<pair<int, T>>> adj;
    void dfs(int u, int p, int l, T d) {
        par[u] = p, lvl[u] = l, len[u] = d;
        for (auto v: adj[u]) if (v.X != p) dfs(v.X, u, l+1, d+v.Y);
    }
    LCA(int n): n(n), par(n), lvl(n), len(n), adj(n) {}
    void add_edge(int u, int v, T w = 1) {
        adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
    }
    void build(int root = 0) {
        dfs(root, -1, 0, 0), anc.assign(n, vector<int>(LOGN, -1));
        for (int i=0; i<n; i++) anc[i][0] = par[i];
        for (int k=1; k<LOGN; k++) for (int i=0; i<n; i++)
            if (anc[i][k-1] != -1) anc[i][k] = anc[anc[i][k-1]][k-1];
    }
    int query(int u, int v) {
        if (lvl[u] > lvl[v]) swap(u, v);
        for (int k=LOGN-1; k>=0; k--) {
            if (lvl[v] - (1 << k) >= lvl[u]) v = anc[v][k];
        }
        if (u == v) return u;
        for (int k=LOGN-1; k >=0; k--) {
            if (anc[u][k] == anc[v][k]) continue;
            u = anc[u][k]; v = anc[v][k];
        }
        return par[u];
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    // Input time.
    int h, w;
    cin >> h >> w >> ws;

    string lines[h+1];
    for (int x=0; x<h+1; x++) {
        getline(cin, lines[x]);
        //cerr << lines[x] << endl;
    }
    int m;
    cin >> m >> ws;
    vector<pii> markers (m);
    vector<vector<bool>> marked(h, vector<bool>(w, false));
    vector<vector<bool>> reached(h, vector<bool>(w, false));
    for (int x=0; x<m; x++) {
        int i, j;
        cin >> i >> j >> ws;
        i--; j--;
        markers[x] = pii(i, j);
        marked[i][j] = true;
    }

    // DFS, and generate the LCA.
    LCA<int> lca(h * w + 5);
    vector<pair<pii, pii>> queue;
    queue.push_back(pair<pii, pii>(markers[0], pii(0, 0)));
    while (queue.size()) {
        pair<pii, pii> popped = queue[0];
        reached[popped.X.X][popped.X.Y] = true;
        queue.erase(queue.begin());
        // What are the neighbours of popped?
        vector<pii> neighbours;
        if ((lines[popped.X.X + 1][2 * popped.X.Y + 1] != '_') && (popped.X.X + 1 != h) && !(reached[popped.X.X+1][popped.X.Y]))
            // Attach bottom
            neighbours.push_back(pii(popped.X.X + 1, popped.X.Y));
        if ((lines[popped.X.X + 1][2 * popped.X.Y] != '|') && (popped.X.Y - 1 != -1) && !(reached[popped.X.X][popped.X.Y-1]))
            // Attach left
            neighbours.push_back(pii(popped.X.X, popped.X.Y-1));
        if ((lines[popped.X.X + 1][2 * popped.X.Y + 2] != '|') && (popped.X.Y + 1 != w) && !(reached[popped.X.X][popped.X.Y+1]))
            // Attach right
            neighbours.push_back(pii(popped.X.X, popped.X.Y+1));
        if ((lines[popped.X.X][2 * popped.X.Y + 1] != '_') && (popped.X.X - 1 != -1) && !(reached[popped.X.X-1][popped.X.Y]))
            // Attach above
            neighbours.push_back(pii(popped.X.X - 1, popped.X.Y));

        if ((neighbours.size() >= 2) || marked[popped.X.X][popped.X.Y]) {
            // Important, new vertex.
            int vertex_num = popped.X.X * w + popped.X.Y + 3; // Add 3 so that the original vertex (0) isn't interferred.
            for (auto neighbour : neighbours) {
                queue.push_back(pair<pii, pii>(neighbour, pii(vertex_num, 1)));
            }
            lca.add_edge(vertex_num, popped.Y.X, popped.Y.Y);
        } else {
            for (auto neighbour : neighbours) {
                queue.push_back(pair<pii, pii>(neighbour, pii(popped.Y.X, popped.Y.Y + 1)));
            }
        }
    }

    lca.build();

    ll covered = 0;
    for (int i=1; i<m; i++) {
        int num1 = markers[i-1].X * w + markers[i-1].Y + 3;
        int num2 = markers[i].X * w + markers[i].Y + 3;
        int node_num = lca.query(num1, num2);
        // cerr << num1 << ' ' << num2 << ' ' << node_num << endl;
        // cerr << lca.len[num1] << ' ' << lca.len[num2] << ' ' << lca.len[node_num] << endl << endl;
        covered += lca.len[num1] + lca.len[num2] - 2 * lca.len[node_num];
    }

    cout << covered << endl;

    return 0;
}
