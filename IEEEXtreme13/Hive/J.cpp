#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

typedef long long ll;
typedef vector<int> vi;

struct HexUnionFind {
    int n; vi A, s, perimeter, rank;
    HexUnionFind(int n): n(n), A(n), s(n, 1), perimeter(n, 6), rank(n) {
        iota(A.begin(), A.end(), 0);
    }
    int find(int x) { return A[x] == x ? x : A[x] = find(A[x]); }
    bool merge(int x, int y, int shared_perimeter) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) swap(x, y);
        A[y] = x; s[x] += s[y]; perimeter[x] += perimeter[y] - 2 * shared_perimeter; n--;
        if (rank[x] == rank[y]) rank[x]++;
        return true;
    }
    bool connected(int x, int y) { return find(x) == find(y); }
    int size(int x) { return s[find(x)]; }
    int perim(int x) { return perimeter[find(x)]; }
};

int main() {

    int n, m;
    cin >> n >> m;
    HexUnionFind huf((n+1)*(m+1));
    vector<bool> active((n+1)*(m+1), false);

    for (int i=0; i<n; i++) {
        for (int j=0; j<(i%2 ? m-1 : m); j++) {
            int activet;
            cin >> activet;
            if (!activet) continue;
            // Neighbours of (i, j):
            int me = i + j*n;
            active[me] = true;
            if (i % 2) {
                pair<int, int> neighbours[6] = {
                    {i-1, j},
                    {i-1, j+1},
                    {i, j+1},
                    {i+1, j+1},
                    {i+1, j},
                    {i, j-1},
                };
                for (int k=0; k<6; k++) {
                    if (
                        (0 <= neighbours[k].first && neighbours[k].first < n) &&
                        (0 <= neighbours[k].second && neighbours[k].second < (neighbours[k].first % 2 ? m-1 : m))
                    ) {
                        int neigh = neighbours[k].first + neighbours[k].second * n;
                        if (active[neigh]) {
                            if (huf.connected(me, neigh)) {
                                huf.perimeter[huf.find(me)] -= 2;
                            } else {
                                huf.merge(me, neigh, 1);
                            }
                        }
                    }
                }
            } else {
                pair<int, int> neighbours[6] = {
                    {i-1, j-1},
                    {i-1, j},
                    {i, j+1},
                    {i+1, j},
                    {i+1, j-1},
                    {i, j-1},
                };
                for (int k=0; k<6; k++) {
                    if (
                        (0 <= neighbours[k].first && neighbours[k].first < n) &&
                        (0 <= neighbours[k].second && neighbours[k].second < (neighbours[k].first % 2 ? m-1 : m))
                    ) {
                        int neigh = neighbours[k].first + neighbours[k].second * n;;
                        if (active[neigh]) {
                            if (huf.connected(me, neigh)) {
                                huf.perimeter[huf.find(me)] -= 2;
                            } else {
                                huf.merge(me, neigh, 1);
                            }
                        }
                    }
                }
            }
        }
    }

    int q;
    cin >> q >> ws;

    for (int qe=0; qe<q; qe++) {
        char split;
        int i, j;
        cin >> split >> i >> j >> ws;
        i --;
        j --;
        int me = i + j*n;
        if (split == 'a') {
            if (active[me]) continue;
            active[me] = true;
            if (i % 2) {
                pair<int, int> neighbours[6] = {
                    {i-1, j},
                    {i-1, j+1},
                    {i, j+1},
                    {i+1, j+1},
                    {i+1, j},
                    {i, j-1},
                };
                for (int k=0; k<6; k++) {
                    if (
                        (0 <= neighbours[k].first && neighbours[k].first < n) &&
                        (0 <= neighbours[k].second && neighbours[k].second < (neighbours[k].first % 2 ? m-1 : m))
                    ) {
                        int neigh = neighbours[k].first + neighbours[k].second * n;
                        if (active[neigh]) {
                            if (huf.connected(me, neigh)) {
                                huf.perimeter[huf.find(me)] -= 2;
                            } else {
                                huf.merge(me, neigh, 1);
                            }
                        }
                    }
                }
            } else {
                pair<int, int> neighbours[6] = {
                    {i-1, j-1},
                    {i-1, j},
                    {i, j+1},
                    {i+1, j},
                    {i+1, j-1},
                    {i, j-1},
                };
                for (int k=0; k<6; k++) {
                    if (
                        (0 <= neighbours[k].first && neighbours[k].first < n) &&
                        (0 <= neighbours[k].second && neighbours[k].second < (neighbours[k].first % 2 ? m-1 : m))
                    ) {
                        int neigh = neighbours[k].first + neighbours[k].second * n;
                        if (active[neigh]) {
                            if (huf.connected(me, neigh)) {
                                huf.perimeter[huf.find(me)] -= 2;
                            } else {
                                huf.merge(me, neigh, 1);
                            }
                        }
                    }
                }
            }
        } else if (split == 'k') {
            if (active[me]) {
                cout << huf.perim(me) << endl;
            } else {
                cout << 0 << endl;
            }
        }
    }

    return 0;
}
