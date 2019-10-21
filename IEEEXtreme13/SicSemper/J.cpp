#include <iostream>
#include <vector>

// This WAs because I misinterpreted what the sum thing was.
// It's the partial sums, and so is not expmod.

using namespace std;

typedef long long ll;

template<typename T> struct SegmentTree {
    int n; vector<pair<T, int> > st; const pair<T, int> I = {0, -1};
    SegmentTree(const vector<T>& A) : n(A.size()), st(2*n, I) {
        for (int i=0; i<n; i++) st[n+i] = {A[i], i};
        for (int i=n-1; i; i--) st[i] = {st[2*i].first + st[2*i+1].first, -1};
    }
    void update(int i, int val) {
        for (st[i+=n] = {val, i}; i> 1; i/= 2) st[i/2] = {st[i].first + st[i^1].first, -1};
    }
    pair<T, int> query(int l, int r) {
        pair<T, int> res = I;
        for (l += n, r += n; l <= r; l /= 2, r /= 2) {
            if (l&1) res = {res.first + st[l++].first, -1};
            if (~r&1) res = {res.first + st[r--].first, -1};
        }
        return res;
    }
};

typedef __int128 big;

ll expmod(big a, big b, big m) {
    big res = 1%m; a %= m;
    for (; b; b/=2) { if (b&1) res = res * a%m; a=a*a%m; }
    return res;
}

int main() {

    int n, k, q;
    cin >> n >> k >> q;
    ll MOD = 1000000007;

    vector<ll> points;
    for (int i=0; i<n; i++) {
        ll in;
        cin >> in >> ws;
        points.push_back(in);
    }

    SegmentTree<ll> segtree(points);

    for (int qe=0; qe < q; qe++) {
        char r;
        int i, j;
        cin >> r >> i >> j >> ws;
        if (r == 'Q') {
            ll res = segtree.query(i-1, j-1).first % MOD;
            cout << (res * expmod(j-i-1, k, MOD)) % MOD << endl;
        } else {
            segtree.update(i-1, j);
        }
    }

    return 0;
}
