#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

typedef vector<int> vi;
typedef int64_t ll;
typedef pair<ll, ll> pii;

struct UnionFind {
    int n; vi A, s, rank;
    UnionFind(int n) : n(n), A(n), s(n, 1), rank(n) { iota(A.begin(), A.end(), 0); }
    int find(int x) { return A[x] == x ? x : A[x]=find(A[x]); }
    bool merge(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) swap(x, y);
        A[y] = x; s[x] += s[y]; n--;
        if (rank[x] == rank[y]) rank[x]++;
        return true;
    }
    bool connected(int x, int y) { return (find(x) == find(y)); }
    int size(int x) { return s[find(x)]; }
    int num_sets() { return n; }
};

int main() {

    vector<pair<ll, pii>> edges;
    int n;
    cin >> n;
    for (int i=0; i<n-1; i++) {
        ll a, b, e;
        cin >> a >> b >> e;
        edges.push_back(pair<ll, pii>(e, pii((ll)a, (ll)b)));
    }

    UnionFind uf(n);

    int64_t best = 0;
    ll mod = 1000000007;

    sort(edges.begin(), edges.end());
    for (auto edge: edges) {
        ll current = uf.size(edge.second.first-1) % mod;
        current *= uf.size(edge.second.second-1);
        current %= mod;
        current *= edge.first;
        current %= mod;
        best += current;
        best %= mod;
        //cerr << uf.size(edge.second.first-1) << uf.size(edge.second.second-1) << edge.first << endl;
        uf.merge(edge.second.first-1, edge.second.second-1);
    }

    cout << best << endl;

    return 0;
}
