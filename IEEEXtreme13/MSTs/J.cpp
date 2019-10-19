#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;

#define X first
#define Y second

template<typename T = int> struct LCA {
    const int LOGN = 20;
    int n; vi par, lvl; vvi anc; vector<T> len; vector<vector<pair<int, T> > > adj;
    void dfs(int u, int p, int l, T d) {
        par[u] = p, lvl[u] = l, len[u] = d;
        for (auto v: adj[u]) if (v.X != p) dfs(v.X, u, l+1, d+v.Y);
    }
    LCA(int n) : n(n), par(n), lvl(n), len(n), adj(n) {}
    void add_edge(int u, int v, T w = 1) {
        adj[u].emplace_back(v, w); adj[v].emplace_back(u, w);
    }
    void build(int root = 0) {
        dfs(root, -1, 0, 0), anc.assign(n, vi(LOGN, -1));
        for (int i=0; i<n; i++) anc[i][0] = par[i];
        for (int k=1; k<LOGN; k++) for (int i=0; i<n; i++)
            if (anc[i][k-1] != -1) anc[i][k] = anc[anc[i][k-1]][k-1];
    }
    int query(int u, int v) {
        if (lvl[u] > lvl[v]) swap(u, v);
        for (int k=LOGN-1; k >=0; k--)
            if (lvl[v] - (1 << k) >= lvl[u]) v = anc[v][k];
        if (u == v) return u;
        for (int k=LOGN-1; k>=0; k--) {
            if (anc[u][k] == anc[v][k]) continue;
            u = anc[u][k]; v = anc[v][k];
        }
        return par[u];
    }
    int add_node(int parent, T w) {
        par.push_back(parent);
        lvl.push_back(lvl[parent]+1);
        anc.push_back(vi(LOGN, -1));
        len.push_back(len[parent] + w);
        adj.push_back(vector<pair<T, int> >());
        add_edge(n, parent, w);
        anc[n][0] = par[n];
        for (int k=1; k<LOGN; k++)
            if (anc[n][k-1] != -1) anc[n][k] = anc[anc[n][k-1]][k-1];
        return n++;
    }
};

int main() {

    int n, m;
    cin >> n >> m;

    typedef pair<int, pair<int, int>> edge;
    typedef pair<int, int> pq_edge;
    priority_queue<pq_edge> edge_pq;
    int MAX = 10001;
    edge edges[m];
    bool used[m];
    bool unique[m];
    bool pushed[m];
    vector<int> edge_from_weight[MAX];

    vector<int> adj[n];

    for (int i=0; i<m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edges[i] = edge(c, pair<int, int>(a-1, b-1));
        used[i] = false;
        unique[i] = true;
        pushed[i] = false;
        adj[a-1].push_back(i);
        adj[b-1].push_back(i);
        edge_from_weight[c].push_back(i);
    }

    vector<edge> possible[MAX];
    int mapping[n];
    mapping[0] = 0;
    for (int i=1; i<n; i++) mapping[i] = -1;

    LCA<int> current(1);
    current.build();

    for (int i: adj[0]) {
        edge_pq.push(pq_edge(MAX - edges[i].first, i));
        pushed[i] = true;
    }

    while (edge_pq.size()) {
        pq_edge out = edge_pq.top(); edge_pq.pop();
        edge e = edges[out.second];
        //cerr << "Popped " << e.second.first << " " << e.second.second << endl;
        used[out.second] = true;
        if (mapping[e.second.first] == -1 || mapping[e.second.second] == -1) {
            // New edge, we can add it!
            if (mapping[e.second.first] == -1) {
                mapping[e.second.first] = current.add_node(mapping[e.second.second], e.first);
                for (auto i: adj[e.second.first]) {
                    if (!pushed[i]) {
                        edge_pq.push(pq_edge(MAX - edges[i].first, i));
                        pushed[i] = true;
                    }
                }
            } else {
                mapping[e.second.second] = current.add_node(mapping[e.second.first], e.first);
                for (auto i: adj[e.second.second]) {
                    if (!pushed[i]) {
                        edge_pq.push(pq_edge(MAX - edges[i].first, i));
                        pushed[i] = true;
                    }
                }
            }
        } else {
            unique[out.second] = false;
            // Connects both, there must be some other overlap!
            int top = current.query(mapping[e.second.first], mapping[e.second.second]);
            int depth = current.lvl[top];
            for (auto i: edge_from_weight[e.first]) {
                if (used[i] && unique[i]) {
                    //cerr << edges[i].second.first << " " << edges[i].second.second << endl;
                    // This edge is in the tree.
                    int lhs1 = current.query(mapping[edges[i].second.first], mapping[e.second.first]);
                    int lhs2 = current.query(mapping[edges[i].second.second], mapping[e.second.first]);
                    int rhs1 = current.query(mapping[edges[i].second.first], mapping[e.second.second]);
                    int rhs2 = current.query(mapping[edges[i].second.second], mapping[e.second.second]);
                    //cerr << depth << " " << lhs1 << " " << lhs2 << " " << rhs1 << " " << rhs2 << " " << mapping[edges[i].second.first] << " " << mapping[edges[i].second.second] << endl;
                    //cerr << current.lvl[rhs1] << " " << current.lvl[rhs2] << endl;
                    if (lhs1 == mapping[edges[i].second.first] && lhs2 == mapping[edges[i].second.second]) {
                        if (current.lvl[lhs1] >= depth && current.lvl[lhs2] >= depth) {
                            // Cycle found. Invalidate this edge.
                            unique[i] = false;
                        }
                    } else if (rhs1 == mapping[edges[i].second.first] && rhs2 == mapping[edges[i].second.second]) {
                        if (current.lvl[rhs1] >= depth && current.lvl[rhs2] >= depth) {
                            // Cycle found. Invalidate this edge.
                            unique[i] = false;
                        }
                    }
                }
            }
        }
    }

    int sols = 0;
    for (int i=0; i<m; i++) {
        if (used[i] && unique[i]) sols++;
    }

    cout << sols << endl;

    return 0;
}
