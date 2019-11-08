#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <queue>

#define X first
#define Y second

using namespace std;

typedef long long ll;
typedef pair<ll, ll> edge;
typedef vector<int> vi;

struct UnionFind {
    int n; vi A, s, rank;
    UnionFind(int n): n(n), A(n), s(n, 1), rank(n) { iota(A.begin(), A.end(), 0); }
    int find(int x) { return A[x] == x ? x : A[x] = find(A[x]); }
    bool merge(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) swap(x, y);
        A[y] = x;
        s[x] += s[y];
        n--;
        if (rank[x] == rank[y]) rank[x]++;
        return true;
    }
    int size(int x) { return s[find(x)]; }
    int num_sets() { return n; }
    vi parents() {
        vi res;
        for (int i=0; i<A.size(); i++) if (A[i] == i) res.push_back(i);
        return res;
    }
};

int main() {

    int t;
    cin >> t;

    for (int testno=0; testno<t; testno++) {
        int n;
        cin >> n;

        int node=0;
        unordered_map<ll, ll> node_names;
        vector<ll> node_values;
        edge edges[n];
        for (int i=0; i<n; i++) {
            cin >> edges[i].X >> edges[i].Y;
            if (node_names.count(edges[i].X) == 0) {
                node_names[edges[i].X] = node++;
                node_values.push_back(edges[i].X);
            }
            if (node_names.count(edges[i].Y) == 0) {
                node_names[edges[i].Y] = node++;
                node_values.push_back(edges[i].Y);
            }
            edges[i].X = node_names[edges[i].X];
            edges[i].Y = node_names[edges[i].Y];
        }

        UnionFind u(node);
        bool loop[n];
        vi adj[node];

        for (int i=0; i<n; i++) {
            loop[i] = (!u.merge(edges[i].X, edges[i].Y));
            adj[edges[i].X].push_back(i);
            adj[edges[i].Y].push_back(i);
        }

        cout << u.num_sets() - 1 << endl;

        queue<int> components;

        for (auto p: u.parents()) {
            components.push(p);
        }

        for (int i=0; i < n; i++) if (loop[i] && u.num_sets() > 1) {
            int p = components.front(); components.pop();
            if (u.find(edges[i].X) == u.find(p)) {
                components.push(p);
                p = components.front(); components.pop();
                p = u.find(p);
            }
            adj[edges[i].X].erase(remove(adj[edges[i].X].begin(), adj[edges[i].X].end(), i), adj[edges[i].X].end());
            adj[p].push_back(i);
            cout << i + 1 << " " << node_values[edges[i].X] << " " << node_values[p] << endl;
            edges[i].X = p;
            u.merge(edges[i].Y, p);
        }

        queue<int> leaves;

        for (int i=0; i<node; i++) if (adj[i].size() == 1) {
            leaves.push(i);
        }

        // Keep removing edges connecting degree 1 vertices
        while (u.num_sets() > 1) {
            int leaf = leaves.front(); leaves.pop();
            if (adj[leaf].size() != 1) continue;
            // Make sure that leaf isn't the parent of it's stack.
            edge e = edges[adj[leaf][0]];
            if (u.find(leaf) == leaf) {
                u.A[leaf] = leaf == e.X ? e.Y : e.X;
                u.A[leaf == e.X ? e.Y : e.X] = leaf == e.X ? e.Y : e.X;
            }
            int p = components.front(); components.pop();
            p = u.find(p);
            if (u.find(e.X) == u.find(p)) {
                components.push(p);
                p = components.front(); components.pop();
                p = u.find(p);
            }
            cout << adj[leaf][0] + 1 << " " << node_values[leaf] << " " << node_values[p] << endl;
            if (leaf == edges[adj[leaf][0]].X) {
                edges[adj[leaf][0]].X = p;
                u.merge(e.Y, p);
            }
            else {
                edges[adj[leaf][0]].Y = p;
                u.merge(e.X, p);
            }
            adj[p].push_back(adj[leaf][0]);
            adj[leaf] = vi();
        }

    }

    return 0;
}
