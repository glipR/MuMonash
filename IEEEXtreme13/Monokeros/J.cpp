#include <iostream>

using namespace std;

typedef long long ll;

struct BST {

    bool root;
    ll depth;
    ll val;
    BST* left;
    BST* right;

    BST(): root(true), depth(0), left(NULL), right(NULL) {}
    BST(ll v, ll d) {
        val = v;
        depth = d + 1;
        root = false;
        left = NULL;
        right = NULL;
    }

    ll insert(ll value) {
        if (left == NULL && right == NULL && root) {
            left = new BST(value, depth);
            return depth + 1;
        } else if (root) {
            return left->insert(value);
        }
        if (value <= val) {
            if (left == NULL) {
                left = new BST(value, depth);
                return depth + 1;
            }
            return left->insert(value);
        } else {
            if (right == NULL) {
                right = new BST(value, depth);
                return depth + 1;
            }
            return right->insert(value);
        }
    }

};

int main() {

    ll n;
    cin >> n;
    BST t;
    for (ll i=0; i<n; i++) {
        ll val;
        cin >> val;
        if (i != 0) { cout << ' '; }
        cout << t.insert(val);
    }
    cout << endl;

    return 0;
}
