// Max Segtree - reverse order of push vs pops
// The push that occurs the first time we see positive push vs pops is the top of the stack
// Binary search the max segtree [a..m] to find the rightmost occurence of > 0.

// MuMonash

#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef long long ll;

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

/* Example structures for sum with increment and global update. */
struct maxNode {
    ll value;

    // How are sums combined?
    maxNode operator+(const maxNode &n) {
        return { max(value, n.value) };
    }
};

struct maxUpdate {
    ll value;

    // How do we apply an operation?
    maxNode operator()(const maxNode &n) {
        return { n.value + value };
    }

    maxUpdate operator+(const maxUpdate &u) {
        return { u.value + value};
    }
};

const maxNode maxZero { 0 }; // Width 1.
const maxUpdate maxNoUp { 0 }; // Increment by 0 by default.

int main() {

    int m;
    cin >> m;

    SegmentTree<maxNode, maxUpdate> st(m, maxZero, maxNoUp);
    int pushes[m];
    for (int i=0; i<m; i++) pushes[i] = -1;

    for (int i=0; i<m; i++) {
        int time, type;
        cin >> time >> type;
        time --;
        if (type) {
            int push;
            cin >> push;
            pushes[time] = push;
            st.upd(0, time, {1});
        } else {
            st.upd(0, time, {-1});
        }
        // Binary search to find first top stack element.
        if (st.query(0, m-1).value <= 0) {
            cout << -1 << endl;
            continue;
        }
        int bot = 0;
        int top = m;
        while (top - bot > 1) {
            int med = (top + bot) / 2;
            // cerr << top << " " << med << " " << bot << " " << st.query(med, m-1).value << endl;
            if (st.query(med, m-1).value <= 0) top = med;
            else bot = med;
        }
        // Time = bot should be the first occurence.
        cout << pushes[bot] << endl;
    }

    return 0;
}
