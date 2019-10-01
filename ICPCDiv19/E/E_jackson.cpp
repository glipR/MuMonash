// MuMonash

#include <algorithm>
#include <functional>
#include <queue>
#include <numeric>
#include <map>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef long long ll;

#define INF 1e15
#define X first
#define Y second


struct UnionFind {

    int n; vi A, s, rank;
    UnionFind(int n) : n(n), A(n), s(n, 1), rank(n) {
        iota(A.begin(), A.end(), 0);
    }

    int find(int x) {
        return A[x] == x ? x : A[x] = find(A[x]);
    }

    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) swap(x, y);
        A[y] = x; s[x] += s[y]; n--;
        if (rank[x] == rank[y]) rank[x]++;
        return true;
    }

    bool connected(int x, int y) {
        return (find(x) == find(y));
    }
    int size(int x) {
        return s[find(x)];
    }
    int num_sets() {
        return n;
    }

};

int main() {

    int n;
    cin >> n >> ws;

    // Ajdacency matrix.
    ll adj[n][n];
    UnionFind islands(n);
    for (int i=0; i<n; i++) {
        adj[i][i] = 0;
    }
    for (int i=1; i<n; i++) {
        for (int j=0; j<i; j++) {
            ll dist;
            cin >> dist;
            adj[i][j] = dist;
            adj[j][i] = dist;
            if (dist < 0) {
                islands.merge(i, j);
            }
        }
    }

    // Islands found. Generate MST value for each island.
    ll GROUP_ADJ[islands.num_sets()][islands.num_sets()];
    for (int i=0; i<islands.num_sets(); i++) {
        for (int j=0; j<islands.num_sets(); j++) {
            GROUP_ADJ[i][j] = INF;
        }
    }

    int no = 0;
    map<int, int> group_no;
    for (int x=0; x<n; x++) {
        if (group_no.count(islands.find(x)) == 0) {
            group_no[islands.find(x)] = no;
            no++;
        }
    }

    vector<int> stations[islands.num_sets()];

    for (int i=0; i<n; i++) {
        for (int j=0; j<i; j++) {
            if (adj[i][j] > 0) {
                GROUP_ADJ[group_no[islands.find(i)]][group_no[islands.find(j)]] = min(adj[i][j], GROUP_ADJ[group_no[islands.find(i)]][group_no[islands.find(j)]]);
                GROUP_ADJ[group_no[islands.find(j)]][group_no[islands.find(i)]] = GROUP_ADJ[group_no[islands.find(i)]][group_no[islands.find(j)]];
            }
        }
        stations[group_no[islands.find(i)]].push_back(i);
    }

    // Now do the MSTs algorithms.
    ll MST[islands.num_sets()];
    for (int i=0; i<islands.num_sets(); i++) MST[i] = -1;

    typedef pair<int, int> pii;
    typedef pair<ll, pii> edge;

    bool impossible = false;

    // Internal MSTs
    for (int x=0; x<islands.num_sets(); x++) {
        // Generate the MST for island x.
        priority_queue<edge, vector<edge>, greater<edge> > pq;
        UnionFind internal_island(stations[x].size());
        int i=0;
        for (auto s1: stations[x]) {
            int j=0;
            for (auto s2: stations[x]) {
                if ((s1 < s2) && adj[s1][s2] < 0) {
                    // Use i, j the indexes relative to the island here.
                    pq.push(edge(-adj[s1][s2], pii(i, j)));
                }
                j++;
            }
            i++;
        }
        ll dist = 0;
        while (pq.size() && (internal_island.num_sets() != 1)) {
            edge e = pq.top();
            pq.pop();
            if (internal_island.connected(e.Y.X, e.Y.Y)) continue;
            internal_island.merge(e.Y.X, e.Y.Y);
            dist += e.X;
        }
        if (internal_island.num_sets() > 1) {
            impossible = true;
        }
        MST[x] = dist;
        /*if (dist != 0) {
           cerr << "MST size for " << x << " is " << dist << endl;
        }*/
    }

    // External MST Algorithm.
    ll dist = 0;

    /*if (islands.num_sets() == 1) {
        // No External connections, so just return MST[0].
        dist = MST[0];
    }*/

    // First update edges and add MST to either side.
    priority_queue<edge, vector<edge>, greater<edge> > pq;
    for (int x=0; x<islands.num_sets(); x++) {
        for (int y=x+1; y<islands.num_sets(); y++) {
            GROUP_ADJ[x][y] += MST[x] + MST[y];
            GROUP_ADJ[y][x] += MST[x] + MST[y];
            if (GROUP_ADJ[x][y] < INF) {
                pq.push(edge(GROUP_ADJ[x][y], pii(x, y)));
            }
        }
    }
    UnionFind external_islands(islands.num_sets());
    while (pq.size() && (islands.num_sets() > 1)) {
        edge e = pq.top();
        pq.pop();
        if (external_islands.connected(e.Y.X, e.Y.Y)) continue;
        dist += e.X;
        external_islands.merge(e.Y.X, e.Y.Y);
    }
    if (impossible || (external_islands.num_sets() > 1)) {
        cout << "impossible" << endl;
    } else {
        cout << dist << endl;
    }

    return 0;
}
