#include <iostream>
#include <vector>

using namespace std;


// Cut makes p and n - p nodes on each tree.
// There are A blue nodes in the p tree, and K - A blue nodes in the n - p tree
// then flipping the p tree gives p - A in the left tree, and K - A in the n - p tree

#define MAXN 100001

struct Tree {
    int n;
    int parent[MAXN];
    int lvl[MAXN];
    vector<int> adj[MAXN];
    int nodes[MAXN];
    bool marked[MAXN];
    void dfs(int u, int p, int l) {
        nodes[u] = 1;
        for (auto v: adj[u]) {
            if (v != p) {
                dfs(v, u, l+1);
                nodes[u] += nodes[v];
            }
        }
        parent[u] = p, lvl[u] = l;
    }
    Tree(int n) : n(n) {
        for (int i=0; i<n; i++) marked[i] = false;
    }
    void add_edge(int u, int v) {
        adj[u].emplace_back(v); adj[v].emplace_back(u);
    }
    void build(int root = 0) {
        dfs(0, -1, 0);
    }
    // B - parent(B) is the split.
    int find_split(int k, int root = 0) {
        int other = n - k;

        if (nodes[root] == k || nodes[root] == other) {
            return root;
        }
        int best = -1;
        for (auto v: adj[root]) {
            if (v != parent[root]) {
                best = max(find_split(k, v), best);
            }
        }
        return best;
    }

    void dfs_mark(int root, int prev) {
        marked[root] = true;
        for (auto v: adj[root]) if (v != prev) dfs_mark(v, root);
    }
};


int main() {

    int n, k;
    cin >> n >> k;

    Tree t(n);

    for (int i=0; i<n-1; i++) {
        int a, b;
        cin >> a >> b;
        t.add_edge(a-1, b-1);
    }

    t.build();

    int node = t.find_split(k);
    if (node == -1) {
        cout << -1 << endl;
    } else {
        if (t.nodes[node] == k) {
            t.dfs_mark(node, t.parent[node]);
        } else {
            t.dfs_mark(t.parent[node], node);
        }
        for (int i=0; i<n; i++) {
            if (t.marked[i]) {
                cout << "flip " << i+1 << endl;
            }
        }
        cout << "cut " << node+1 << " " << t.parent[node]+1 << endl;
    }

    return 0;
}

