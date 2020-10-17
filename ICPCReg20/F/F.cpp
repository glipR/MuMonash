#include <numeric>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;

struct UnionFind {
    int n; vi A, s, rank;
    UnionFind(int n): n(n), A(n), s(n, 1), rank(n) { iota(A.begin(),A.end(), 0); }
    int find(int x) {return A[x]==x ? x : A[x]=find(A[x]); }
    bool merge(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) swap(x, y);
        A[y] = x; s[x] += s[y]; n--;
        if (rank[x] == rank[y]) rank[x]++;
        return true;
    }
    bool connected(int x, int y) {return find(x) == find(y); }
};

int main() {

    int p, w;
    cin >> p >> w;
    
    UnionFind uf = UnionFind(p);

    int c, v;
    cin >> c >> v;

    vector<pair<ll, pair<int, int> > > edges;
    edges.clear();

    for (int i=0; i<w; i++) {
        ll ws, we, ww;
        cin >> ws >> we >> ww;
        edges.push_back({ww, {ws, we}});
    }

    sort(edges.begin(), edges.end());
    for (int i=edges.size()-1; i>=0; i--) {
        uf.merge(edges[i].second.first, edges[i].second.second);
        if (uf.connected(c, v)) {
            cout << edges[i].first << endl;
            break;
        }
    }

    return 0;
}