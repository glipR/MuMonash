#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

struct Key {
    int value;
    vector<int> ciphers;
};

int main() {

    int n, w;
    cin >> n >> w;

    ll A, B;
    cin >> A >> B;

    vector<ll> ciphers(n);
    for (int i=0; i<n; i++) { cin >> ciphers[i]; }

    ll total_keys = 0;
    vector<Key> possible_keys;
    possible_keys.push_back({ 0, {} });
    for (int i=0; i<n; i++) possible_keys[0].ciphers.push_back(i);

    for (int i=w; i>=0; i--) {
        // cerr << "Iteration " << i << endl;
        vector<Key> new_keys;
        for (auto key: possible_keys) {
            // Check a key against it's remaining ciphers.
            // cerr << "Trying key " << key.value << endl;
            vector<int> c1; // Completely contained in [A, B]
            bool c2 = false; // Completely outside [A, B]
            vector<int> c3; // On the boundary
            for (auto c: key.ciphers) {
                // Find the portion of the original text that is already described by the key.
                ll val = ((key.value >> i) ^ (ciphers[c] >> i)) << i;
                ll val2 = val + (1 << i) - 1;
                // cerr << "Cipher " << c << " has current values " << val << " to " << val2 << endl;
                // Original text can range from [val, val2].
                if (val > B || val2 < A) {
                    c2 = true;
                    break;
                }
                if (val < A || val2 > B) {
                    c3.push_back(c);
                }
                else {
                    c1.push_back(c);
                }
            }
            if (c2) continue; // Key invalid no matter what.
            if (c3.size() == 0) { // Key valid no matter what.
                total_keys += (1 << i);
                continue;
            }
            // Boundary ciphers cause problems.
            Key k1;
            Key k2;
            k1.value = key.value;
            k2.value = key.value + (1 << (i-1));
            k1.ciphers = c3;
            k2.ciphers = c3;
            new_keys.push_back(k1);
            new_keys.push_back(k2);
        }
        possible_keys = new_keys;
    }

    cout << total_keys << endl;

    return 0;
}
