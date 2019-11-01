#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

template<typename T, typename U> struct seg_tree_lazy {
    int S, H;

    T zero;
    vector<T> value;

    U noop;
    vector<bool> dirty;
    vector<U> prop;

    seg_tree_lazy<T, U>(int _S, T _zero = T(), U _noop = U()) {
        zero = _zero, noop = _noop;
        for (S = 1, H = 1; S < _S; ) S *= 2, H++;

        value.resize(2*S, zero);
        dirty.resize(2*S, false);
        prop.resize(2*S, noop);
    }

    void set_leaves(vector<T> &leaves) {
        copy(leaves.begin(), leaves.end(), value.begin() + S);

        for (int i = S - 1; i > 0; i--)
            value[i] = value[2 * i] + value[2 * i + 1];
    }

    void apply(int i, U &update) {
        value[i] = update(value[i]);
        if(i < S) {
            prop[i] = prop[i] + update;
            dirty[i] = true;
        }
    }

    void rebuild(int i) {
        for (int l = i/2; l; l /= 2) {
            T combined = value[2*l] + value[2*l+1];
            value[l] = prop[l](combined);
        }
    }

    void propagate(int i) {
        for (int h = H; h > 0; h--) {
            int l = i >> h;

            if (dirty[l]) {
                apply(2*l, prop[l]);
                apply(2*l+1, prop[l]);

                prop[l] = noop;
                dirty[l] = false;
            }
        }
    }

    void upd(int i, int j, U update) {
        // cerr << "Updating to " << update.value << " over [" << i << ", " << j << "]" << endl;
        i += S, j += S;
        propagate(i), propagate(j);

        for (int l = i, r = j; l <= r; l /= 2, r /= 2) {
            if((l&1) == 1) apply(l++, update);
            if((r&1) == 0) apply(r--, update);
        }

        rebuild(i), rebuild(j);
        // debug();
    }

    T query(int i, int j){
        // cerr << "Querying [" << i << ", " << j << "]" << endl;
        i += S, j += S;
        propagate(i), propagate(j);
        // debug();

        T res_left = zero, res_right = zero;
        for(; i <= j; i /= 2, j /= 2){
            if((i&1) == 1) res_left = res_left + value[i++];
            if((j&1) == 0) res_right = value[j--] + res_right;
        }
        // cerr << "Got " << (res_left + res_right).minim << endl;
        return res_left + res_right;
    }

    void debug() {
        cerr << "Values in tree:" << endl;
        for (int i=0; i<2*S; i++) {
            cerr << value[i].minim << " ";
        }
        cerr << endl;
        cerr << "Updates in tree:" << endl;
        for (int i=0; i<2*S; i++) {
            cerr << prop[i].value << " ";
        }
        cerr << endl;
    }
};

struct node {
    ll minim;

    node operator+(const node &n) {
        return { min(n.minim, minim) };
    }
};

struct update {
    ll value; // Shift everything, don't set the value.

    node operator()(const node &n) {
        return { n.minim + value };
    }

    update operator+(const update &u) {
        return { value + u.value };
    }
};

const ll MAXN = 1e5 + 10;

int main() {
    int n, m, q;

    cin >> n >> m >> q;

    int employees[MAXN];
    for (int i=0; i<n; i++) {
        cin >> employees[i];
    }
    int above_randall = 0;
    for (int i=1; i<n; i++) {
        if (employees[i] > employees[0]) above_randall++;
    }
    // cerr << "Starting with " << above_randall << endl;
    seg_tree_lazy<node, update> st(m, {100000}, {0});
    vector<node> leaves(m, {0});
    st.set_leaves(leaves);

    vector<ll> updates[m];

    for (int i=0; i<m; i++) {
        ll num_changes;
        cin >> num_changes;
        // cerr << st.query(i, i).minim << endl;
        st.upd(i, i, { (n - num_changes) - above_randall - 1 });
        // cerr << i << " should be " << ((n - num_changes) - above_randall - 1) << endl;
        // cerr << st.query(i, i).minim << endl;
        for (int j=0; j<num_changes; j++) {
            ll change;
            cin >> change;
            updates[i].push_back(change);
            if (change > employees[0]) above_randall++;
        }
        // cerr << "Year " << i+1 << " with " << above_randall << " and " << num_changes << " replaced." << endl;
    }

    /*for (int i=0; i<m; i++) {
        cerr << st.query(i, i).minim << endl;
    }*/

    for (int a=0; a<q; a++) {
        int i, j;
        ll change;
        cin >> i >> j >> change;
        if (updates[i-1][j-1] < employees[0]) {
            if (change > employees[0]) {
                st.upd(i, m-1, { -1 });
            }
        } else {
            if (change < employees[0]) {
                st.upd(i, m-1, { 1 });
            }
        }
        updates[i-1][j-1] = change;
        ll sol = st.query(0, m-1).minim;
        if (sol >= 0) {
            cout << 1 << endl;
        } else {
            cout << 0 << endl;
        }
    }

    return 0;
}
