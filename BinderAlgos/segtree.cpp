// MuMonash

#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef long long ll;

ll gcd(ll a, ll b) {
    if (b==0) { return (a<0) ? -a: a; }
    else { return gcd(b, a%b); }
}

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

// Dynamic RMQ (Segment Tree) with range updates.
// More modular, and allows for Custom SegTree "Parts" to be added in.
// As above, O(N) build, and O(log(n)) query.
// Here, U is that "part" mentioned above.
template<typename T, typename U> struct SegmentTree2 {
    T I, t[4]; int N, h; vector<T> A; // I is the identity value.
    SegmentTree2(const vector<T>& data, T I=T()): I(I), N(data.size()),
    h(sizeof(int)*8-__builtin_clz(N)), A(2*N, I) {
        copy(data.begin(), data.end(), A.begin()+N);
        for (int i=N-1; i;i--) op(i);
    }
    void op(int i) { A[i].op(A[2*i], A[2*i+1]); }
    void prop(int i) { A[2*i].us(A[i].U); A[2*i+1].us(A[i].U); A[i].NU(); }
    void push(int i) {for (int j=h;j;j--) prop(i>>j); }
    void update(int l, int r, U v) { // Acts on [l, r)
        push(l+=N); push((r+=N)-1); bool cl=0,cr=0;
        for (;l<r;l/=2,r/=2) {
            if (cl) op(l-1); if (cr) op(r);
            if (l&1) A[l++].us(v), cl=1;
            if (r&1) A[--r].us(v), cr=1;
        }
        if (l==1 && cr) op(1);
        else for (l--;r>0;l/=2,r/=2) {
            if (cl && l) op(l);
            if (cr && (!cl || (l!=r && r!=1))) op(r);
        }
    }
    T query(int l, int r) { // Acts on [l, r)
        push(l+=N); push((r+=N)-1);
        t[0]=t[2]=I; int i=0, j=2;
        for(;l<r;l/=2,r/=2) {
            if (l&1) t[i^1].op(t[i],A[l++]), i^=1;
            if (r&1) t[j^1].op(A[--r],t[j]), j^=1;
        }
        t[i^1].op(t[i],t[j]);
        return t[i^1];
    }
};

struct RangeGCD {  // Example Input to above, to get GCD over range and update value over range.
    // THIS IS BUGGED OR THE IMPLEMENTATION ABOVE IS BUGGED
    int a = INT_MIN, U = INT_MAX;
    void op(RangeGCD& b, RangeGCD& c) { a=gcd(b.a, c.a); }  // Merge two segments.
    void us(int v) { if (v!=INT_MAX) a=U=v; }  // Apply a lazy update (Possibly worse than actuality?)
    void NU() { U = INT_MAX; }  // Node requires no update?
};

struct RangeSum {
    int a = 0, U = INT_MAX;
    void op(RangeSum& b, RangeSum& c) { a = b.a + c.a; }
    void us(int v) { if (v!=INT_MAX) a=U=v; }
    void NU() { U=INT_MAX; }
};

struct RangeMin {
    int a = INT_MAX, U = INT_MIN;
    void op(RangeMin& b, RangeMin& c) { a=min(b.a, c.a); }
    void us(int v) { if (v!=INT_MIN) a=U=v; }
    void NU() { U=INT_MIN; }
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

    cout << "Static vs Dynamic Min" << endl;

    cout << s.query(3, 7).first << " " << s.query(3, 7).second << endl;
    cout << d.query(3, 7).first << " " << d.query(3, 7).second << endl;
    cout << s.query(0, 2).first << " " << s.query(0, 2).second << endl;
    cout << d.query(0, 2).first << " " << d.query(0, 2).second << endl;
    d.update(3, 1);
    cout << s.query(2, 3).first << " " << s.query(2, 3).second << endl;
    cout << d.query(2, 3).first << " " << d.query(2, 3).second << endl;

    cout << "GCD Range Updates" << endl;

    SegmentTree2<RangeMin, int> st(vector<RangeMin>(10));
    st.update(0, 4, 8);
    st.update(4, 5, 6);
    st.update(5, 10, 16);
    cout << st.query(4, 10).a << endl;
    cout << st.query(0, 6).a << endl;
    cout << st.query(7, 10).a << endl;

    return 0;
}
