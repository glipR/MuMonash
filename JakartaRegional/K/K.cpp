#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

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

struct matNode {
    ll x1, x2, y1, y2;

    /*
        [ x1, y1 ]
        [ x2, y2 ]
    */

    matNode operator+(const matNode &n) {
        // Multiply the two.
        return {
            (x1 * n.x1 + y1 * n.x2) % MOD,
            (x2 * n.x1 + y2 * n.x2) % MOD,
            (x1 * n.y1 + y1 * n.y2) % MOD,
            (x2 * n.y1 + y2 * n.y2) % MOD,
        };
    }
};

struct matUpdate {
    bool type; // True => Flip, False => Do nothing.

    matNode operator()(const matNode &n) {
        if (type)
            return { n.y2, n.y1, n.x2, n.x1 };
        return { n.x1, n.x2, n.y1, n.y2 };
    }

    matUpdate operator+(const matUpdate &u) {
        return { (bool)(type ^ u.type) };
    }
};

const matNode zero { 1, 0, 0, 1 };
const matUpdate noop { false };
const matNode nodeA { 1, 1, 0, 1 };
const matNode nodeB { 1, 0, 1, 1 };

int main() {

    int n, q;
    cin >> n >> q >> ws;

    char chars[n];
    for (int i=0; i<n; i++) {
        cin >> chars[i];
    }

    SegmentTree<matNode, matUpdate> st(n, zero, noop);
    vector<matNode> leaves;
    for (int i=0; i<n; i++) {
        if (chars[i] == 'A') leaves.push_back(nodeA);
        else leaves.push_back(nodeB);
    }
    st.set_leaves(leaves);

    for (int i=0; i<q; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            // Flip
            int i, j;
            cin >> i >> j;
            st.upd(i-1, j-1, { true });
        } else {
            int i, j, a, b;
            cin >> i >> j >> a >> b;
            matNode m = st.query(i-1, j-1);
            cout << (a * m.x1 + b * m.x2) % MOD << " " << (a * m.y1 + b * m.y2) % MOD << endl;
        }
    }

    return 0;
}
