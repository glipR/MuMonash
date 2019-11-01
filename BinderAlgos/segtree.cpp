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

// Dynamic RQ, with lazy propogation (Ranged updates.)
// Updates and querys are INCLUSIVE ON BOTH SIDES [L, R].
template<typename T, typename U> struct SegmentTree {
    int S, H;

    T z;
    vector<T> v; // Actual values (May not be up to date)

    U noop; // No Operation constant
    vector<bool> d; // Dirty array (What needs updating)
    vector<U> p; // Lazy propogated updates.

    SegmentTree<T, U>(int _S, T _z = T(), U _noop = U()) {
        z = _z, noop = _noop;
        for (S = 1, H = 1; S < _S; ) S *= 2, H++;
        v.resize(2*S, z);
        d.resize(2*S, false);
        p.resize(2*S, noop);
    }

    void set_leaves(vector<T> &l) {
        copy(l.begin(), l.end(), v.begin() + S);
        for (int i = S - 1; i > 0; i--)
            v[i] = v[2 * i] + v[2 * i + 1];
    }

    void apply(int i, U &up) {
        v[i] = up(v[i]);
        if(i < S) {
            p[i] = p[i] + up;
            d[i] = true;
        }
    }

    void rebuild(int i) {
        for (int l = i/2; l; l /= 2) {
            T c = v[2*l] + v[2*l+1];
            v[l] = p[l](c);
        }
    }

    void prop(int i) {
        for (int h = H; h > 0; h--) {
            int l = i >> h;

            if (d[l]) {
                apply(2*l, p[l]);
                apply(2*l+1, p[l]);

                p[l] = noop;
                d[l] = false;
            }
        }
    }

    void upd(int i, int j, U update) {
        i += S, j += S;
        prop(i), prop(j);

        for (int l = i, r = j; l <= r; l /= 2, r /= 2) {
            if((l&1) == 1) apply(l++, update);
            if((r&1) == 0) apply(r--, update);
        }

        rebuild(i), rebuild(j);
    }

    T query(int i, int j){
        i += S, j += S;
        prop(i), prop(j);

        T res_left = z, res_right = z;
        for(; i <= j; i /= 2, j /= 2){
            if((i&1) == 1) res_left = res_left + v[i++];
            if((j&1) == 0) res_right = v[j--] + res_right;
        }
        return res_left + res_right;
    }
};

/* Example structures for minimum with increment and global update. */
struct minNode {
    ll minim;

    // How are minimums combined?
    minNode operator+(const minNode &n) {
        return { min(n.minim, minim) };
    }
};

struct minUpdate {
    bool type; // true => increment; false => set.
    ll value;

    // How do we apply an operation?
    minNode operator()(const minNode &n) {
        return { type ? n.minim + value : value };
    }

    minUpdate operator+(const minUpdate &u) {
        if (type) {
            // Increment
            return { u.type, u.value + value};
        }
        // Set
        return { type, value };
    }
};

const minNode minZero { INT_MAX };
const minUpdate minNoUp { true, 0 }; // Increment by 0 by default.

/* Example structures for sum with increment and global update. */
struct sumNode {
    ll value;
    ll width; // How many leaves does this node span?

    // How are sums combined?
    sumNode operator+(const sumNode &n) {
        return { value + n.value, width + n.width };
    }
};

struct sumUpdate {
    bool type; // true => increment; false => set.
    ll value;

    // How do we apply an operation?
    sumNode operator()(const sumNode &n) {
        return { type ? n.value + value * n.width : value * n.width, n.width };
    }

    sumUpdate operator+(const sumUpdate &u) {
        if (type) {
            // Increment
            return { u.type, u.value + value};
        }
        // Set
        return { type, value };
    }
};

const sumNode sumZero { 0, 1 }; // Width 1.
const sumUpdate sumNoUp { true, 0 }; // Increment by 0 by default.

/* Example structures for gcd with multiply and global update. */
struct gcdNode {
    ll value;

    // How are gcds combined?
    gcdNode operator+(const gcdNode &n) {
        if (n.value == -1) return { value };
        if (value == -1) return { n.value };
        return { gcd(n.value, value) };
    }
};

struct gcdUpdate {
    bool type; // true => multiply; false => set.
    ll value;

    // How do we apply an operation?
    gcdNode operator()(const gcdNode &n) {
        return { type ? n.value * value : value };
    }

    gcdUpdate operator+(const gcdUpdate &u) {
        if (type) {
            // Multiply
            return { u.type, u.value * value};
        }
        // Set the gcd
        return { type, value };
    }
};

const gcdNode gcdZero { -1 }; // Width 1.
const gcdUpdate gcdNoUp { true, 1 }; // Multiply by 1 by default.

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
    SegmentTree<minNode, minUpdate> st(list.size(), minZero, minNoUp);
    vector<minNode> nodeList;
    for (int i=0; i<list.size(); i++) {
        nodeList.push_back({ list[i] });
    }
    st.set_leaves(nodeList);

    cout << "Static vs Dynamic Min" << endl;
    // 0, 1, 2, 3, 4, 5, 6, 7
    // 3, 5, 2, 4, 1, 5, 3, 2
    cout << s.query(3, 7).first << " " << s.query(3, 7).second << endl;
    cout << st.query(3, 7).minim << endl;
    // 1 4, 1
    cout << s.query(0, 2).first << " " << s.query(0, 2).second << endl;
    cout << st.query(0, 2).minim << endl;
    // 2 2, 2
    st.upd(2, 4, { true, 1 }); // Increment [2, 4] by 2.
    cout << s.query(2, 6).first << " " << s.query(2, 6).second << endl;
    cout << st.query(2, 6).minim << endl;
    // 1 4, 2
    st.upd(4, 4, { false, 10 }); // Set [4, 4] to 10
    cout << st.query(4, 4).minim << endl;
    // 10

    cout << "Sum Updates" << endl;
    SegmentTree<sumNode, sumUpdate> st2(list.size(), sumZero, sumNoUp);
    vector<sumNode> sumList;
    for (int i=0; i<list.size(); i++) {
        sumList.push_back({ list[i], 1 });
    }
    st2.set_leaves(sumList);

    // 0, 1, 2, 3, 4, 5, 6, 7
    // 3, 5, 2, 4, 1, 5, 3, 2
    for (int i=0; i<8; i++) {
        cout << st2.query(i, i).value << " ";
    }
    cout << endl;
    cout << st2.query(0, 7).value << " " << st2.query(2, 5).value << endl;
    // 25 12
    st2.upd(1, 5, { false, 1 }); // Set all of [1, 5] to 1.
    cout << st2.query(1, 5).value << " " << st2.query(0, 7).value << endl;
    // 5 13
    st2.upd(4, 7, { true, 2 }); // Increment [4, 7] by 2.
    cout << st2.query(2, 5).value << " " << st2.query(0, 7).value << endl;
    // 8 21

    cout << "GCD Range Updates" << endl;
    SegmentTree<gcdNode, gcdUpdate> st3(list.size(), gcdZero, gcdNoUp);
    vector<gcdNode> gcdList;
    for (int i=0; i<list.size(); i++) {
        gcdList.push_back({ list[i] });
    }
    st3.set_leaves(gcdList);

    // 0, 1, 2, 3, 4, 5, 6, 7
    // 3, 5, 2, 4, 1, 5, 3, 2
    cout << st3.query(2, 2).value << " " << st3.query(4, 4).value << endl;
    // 2 1
    st3.upd(4, 6, { true, 2 }); // Multiply [4, 6] by 2.
    st3.upd(2, 3, { true, 10 }); // Multiply [2, 3] by 10.
    cout << st3.query(3, 7).value << " " << st3.query(2, 3).value << endl;
    // 2 20
    st3.upd(0, 0, { false, 6 });
    st3.upd(7, 7, { false, 15 });
    st3.upd(1, 6, { true, 4 });
    st3.upd(1, 6, { true, 3 });
    cout << st3.query(0, 7).value << " " << st3.query(0, 6).value << endl;
    // 3 6
    return 0;
}
