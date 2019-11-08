#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<int> vi;

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
    vi flips;
    int pos;

    // How are minimums combined?
    minNode operator+(const minNode &n) {
        if (n.minim < minim) {
            return { n.minim, n.flips, n.pos };
        } return { minim, flips, pos };
    }
};

struct minUpdate {
    ll value;
    vi flips;

    // How do we apply an operation?
    minNode operator()(const minNode &n) {
        if (value == -1) {
            return { n.minim, n.flips, n.pos };
        }
        return { value, flips, n.pos };
    }

    minUpdate operator+(const minUpdate &u) {
        if (value != -1) {
            return { value, flips };
        }
        return { u.value, u.flips };
    }
};

const minNode minZero { INT_MAX, vi(), -1 };
const minUpdate minNoUp { -1, vi() }; // Increment by 0 by default.

int main() {

    int t;
    cin >> t;
    for (int testno=0; testno<t; testno++) {
        ll n, k;
        cin >> n >> k;

        vi human_vals(n);
        vi comp_vals(n);

        for (int i=0; i<n; i++) {
            cin >> human_vals[i];
        }
        for (int i=0; i<n; i++) {
            cin >> comp_vals[i];
        }

        vi human_exceed(n, -1);
        vi comp_exceed(n, -1);

        ll human_sum = 0;
        ll comp_sum = 0;
        ll diff = 0;
        for (int i=0; i<n; i++) {
            human_sum += human_vals[i];
            if (human_sum >= k) {
                human_exceed[0] = i;
                break;
            }
        }
        for (int i=0; i<n; i++) {
            comp_sum += comp_vals[i];
            if (comp_sum >= k) {
                comp_exceed[0] = i;
                break;
            }
        }

        for (int i=1; i<n; i++) {
            diff += human_vals[i-1] - comp_vals[i-1];
            if (human_exceed[i-1] == -1) break;
            human_sum -= human_vals[i-1];
            human_sum -= human_vals[human_exceed[i-1]];
            for (int j=human_exceed[i-1]; j<n; j++) {
                human_sum += human_vals[j];
                if (human_sum + max(diff, (ll)0) >= k) {
                    human_exceed[i] = j;
                    break;
                }
            }
        }

        diff = 0;
        for (int i=1; i<n; i++) {
            diff += comp_vals[i-1] - human_vals[i-1];
            if (comp_exceed[i-1] == -1) break;
            comp_sum -= comp_vals[i-1];
            comp_sum -= comp_vals[comp_exceed[i-1]];
            for (int j=comp_exceed[i-1]; j<n; j++) {
                comp_sum += comp_vals[j];
                if (comp_sum + max(diff, (ll)0) >= k) {
                    comp_exceed[i] = j;
                    break;
                }
            }
        }

        if (comp_exceed[0] == -1) {
            cout << -1 << endl;
        } else if (human_exceed[0] == -1 || (human_exceed[0] > comp_exceed[0])) {
            cout << 0 << endl << endl;
        }
        else {
            // Now we can do the segtree stuff.
            SegmentTree<minNode, minUpdate> st(n, minZero, minNoUp);

            vector<minNode> leaves(n, {n+1, vi(), -1});
            for (int i=0; i<n; i++) leaves[i].pos = i;

            if (comp_exceed[n-1] != -1 && human_exceed[n-1] == -1)
                leaves[n-1] = {0, vi(), (int)n-1};

            st.set_leaves(leaves);

            for (int i=n-2; i>=0; i--) {
                // DP[i].
                if (comp_exceed[i] != -1 && (human_exceed[i] == -1 || (human_exceed[i] > comp_exceed[i]))) {
                    st.upd(i, i, { 0, vi() });
                } else {
                    if (comp_exceed[i] == -1) continue;
                    minNode best = st.query(i+1, human_exceed[i]);
                    if (best.minim == n+1) continue;
                    else {
                        vi flips = best.flips;
                        flips.push_back(best.pos);
                        st.upd(i, i, { best.minim + 1, flips });
                    }
                }
            }

            minNode result = st.query(0, 0);
            if (result.minim >= n+1) {
                cout << -1 << endl;
            } else {
                cout << result.minim << endl;
                for (int i=0; i<result.flips.size(); i++) {
                    if (i) { cout << " "; }
                    cout << result.flips[result.flips.size() - i - 1];
                }
                cout << endl;
            }
        }
    }
    return 0;
}
