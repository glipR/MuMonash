// MuMonash

#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;

// Static RMQ (Sparse Table)
// Can solve Range Queries for:
// Max, Min, Sum, GCD, LCM.
// And anything else where we can combine segments in O(1).
// The pair operations here take use of the fact that pairs can be compared element wise.
// For Sum, GCD, LCM, remove the index entirely (Because it doesn't make sense)
// O(n*log(n)) build, O(1) query
template <typename T> struct SparseTable {
    int n; vector<vector<pair<T, int> > > sptable; vi lg;
    SparseTable(const vector<T> &A) : n(A.size()), lg(n+1, 0) {
        for (int i=2; i <= n; i++) lg[i] = lg[i/2] + 1;
        sptable.assign(lg[n]+1, vector<pair<T, int> >(n));
        for (int i=0; i<n; i++) sptable[0][i] = {A[i], i}; // query [x, x] = x.
        for (int i=1; i<=lg[n]; i++) for (int j=0; j+(1<<i)-1<n; j++)
            sptable[i][j] = min(sptable[i-1][j], sptable[i-1][j+(1<<(i-1))]); // Combine segments (Change here.)
    }
    pair<T, int> query(int L, int R) {
        int k = lg[R-L+1];
        return min(sptable[k][L], sptable[k][R-(1<<k)+1]); // Combine segments (Change here.)
    }
};

// Dynamic RMQ (Segment Tree)
// O(n) build, O(log(n)) query/update.
template <typename T> struct SegmentTree {
    int n; vector<pair<T, int> > st; const pair <T, int> I = {numeric_limits<T>::max(),-1};
    SegmentTree(const vector<T>& A) : n(A.size()), st(2*n, I) {
        for (int i=0; i<n;i++) st[n+i] = {A[i], i};
        for (int i=n-1;i;--i) st[i]=min(st[2*i], st[2*i+1]);
    }
    void update(int i, int val) {
        for (st[i+=n]={val, i}; i>1; i/=2) st[i/2]=min(st[i], st[i^1]);
    }
    pair<T, int> query(int l, int r) {
        pair<T, int> res=I;
        for (l += n, r+= n; l<= r; l/= 2, r/= 2) {
            // cerr << "S: " << l << ' ' << r << endl;
            if (l&1) {
                // cerr << "l" << endl;
                res = min(res, st[l++]);
            }
            if (~r&1) {   // THIS IS A TILDE, NOT A MINUS :^(. You could instead do !(r&1), right?
                // cerr << "r" << endl;
                res = min(res, st[r--]);
            }
        }
        return res;
    }
};

int main() {

    vector<int> list;
    list.push_back(3);
    list.push_back(5);
    list.push_back(2);
    list.push_back(4);
    list.push_back(1);
    list.push_back(5);
    list.push_back(3);
    list.push_back(2);

    SparseTable<int> s(list);
    SegmentTree<int> d(list);

    cout << s.query(3, 7).first << " " << s.query(3, 7).second << endl;
    cout << d.query(3, 7).first << " " << d.query(3, 7).second << endl;
    cout << s.query(0, 2).first << " " << s.query(0, 2).second << endl;
    cout << d.query(0, 2).first << " " << d.query(0, 2).second << endl;
    d.update(3, 1);
    cout << s.query(2, 3).first << " " << s.query(2, 3).second << endl;
    cout << d.query(2, 3).first << " " << d.query(2, 3).second << endl;

    return 0;
}
