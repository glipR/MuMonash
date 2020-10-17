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

    map<pair<int, int>, bool> paired;
    paired.clear();

    ll N, F, Q;
    cin >> N >> F >> Q;

    vector<pair<char, pair<int, int> > > events;
    events.clear();

    for (int i=0; i<F; i++) {
        int X, Y;
        cin >> X >> Y >> ws;
        if (X > Y) swap(X, Y);
        paired[{X, Y}] = true;
    }
    for (int i=0; i<Q; i++) {
        char a;
        int X, Y;
        cin >> a >> X >> Y;
        events.push_back({a, {X, Y}});
        if (a == 'E') {
            if (X > Y) swap(X, Y);
            paired[{X, Y}] = false;
        }
    }
    UnionFind uf = UnionFind(N);
    for (auto key_val: paired) {
        if (key_val.second) {
            uf.merge(key_val.first.first-1, key_val.first.second-1);
        }
    }
    vector<string> results;
    results.clear();
    for (int i=Q-1;i>=0; i--) {
        if (events[i].first == 'E') {
            uf.merge(events[i].second.first-1, events[i].second.second-1);
        } else {
            if (uf.connected(events[i].second.first-1, events[i].second.second-1)) {
                results.push_back("YES");
            } else {
                results.push_back("NO");
            }
        }
    }
    for (int i=results.size()-1; i>=0; i--) {
        cout << results[i] << endl;
    }


    return 0;
}