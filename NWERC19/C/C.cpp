#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {

    int n;
    cin >> n;
    vector<ll> left(n);
    vector<ll> right(n);
    for (int i=0; i<n; i++) { cin >> left[i] >> right[i]; }
    int p;
    cin >> p;
    vector<ll> pegs(p);
    vector<ll> new_pegs;
    for (int i=0; i<p; i++) { cin >> pegs[i]; }

    // Greedily apply pegs from left to right, favouring the right corner.
    bool bad = false;
    for (int i=0; i<n; i++) {
        /*err << "Pegs:" << endl;
        for (auto p: pegs) {
            cerr << p << " ";
        }
        cerr << endl;
        cerr << "New Pegs:" << endl;
        for (auto p: new_pegs) {
            cerr << p << " ";
        }
        cerr << endl;*/
        auto lm = lower_bound(pegs.begin(), pegs.end(), left[i]);
        auto rm = upper_bound(pegs.begin(), pegs.end(), right[i]);
        if (rm - lm == 2) continue;
        else if (rm - lm > 2) { bad = true; break; }
        else if (rm - lm == 0) {
            pegs.insert(lower_bound(pegs.begin(), pegs.end(), left[i] + 1), left[i] + 1);
            new_pegs.push_back(left[i]+1);
        }
        // rm - lm = 1 now.
        if (i == n-1) {
            if (binary_search(pegs.begin(), pegs.end(), right[i])) {
                pegs.insert(lower_bound(pegs.begin(), pegs.end(), right[i]-1), right[i]-1);
                new_pegs.push_back(right[i]-1);
            } else {
                pegs.insert(lower_bound(pegs.begin(), pegs.end(), right[i]), right[i]);
                new_pegs.push_back(right[i]);
            }
            continue;
        }
        auto lm2 = lower_bound(pegs.begin(), pegs.end(), left[i+1]);
        auto rm2 = upper_bound(pegs.begin(), pegs.end(), right[i+1]);
        if ((rm2 - lm2 < 2) && (right[i] == left[i+1]) && (!binary_search(pegs.begin(), pegs.end(), right[i]))) {
            pegs.insert(lower_bound(pegs.begin(), pegs.end(), right[i]), right[i]);
            new_pegs.push_back(right[i]);
        } else {
            // Add to the next appropriate position.
            if (binary_search(pegs.begin(), pegs.end(), right[i])) {
                pegs.insert(lower_bound(pegs.begin(), pegs.end(), right[i]-1), right[i]-1);
                new_pegs.push_back(right[i]-1);
            } else {
                if (right[i] != left[i+1]) {
                    pegs.insert(lower_bound(pegs.begin(), pegs.end(), right[i]), right[i]);
                    new_pegs.push_back(right[i]);
                } else {
                    if (binary_search(pegs.begin(), pegs.end(), right[i]-1)) {
                        pegs.insert(lower_bound(pegs.begin(), pegs.end(), right[i]-2), right[i]-2);
                        new_pegs.push_back(right[i]-2);
                    } else {
                        pegs.insert(lower_bound(pegs.begin(), pegs.end(), right[i]-1), right[i]-1);
                        new_pegs.push_back(right[i]-1);
                    }
                }
            }
        }
    }

    if (bad) {
        cout << "impossible" << endl;
    } else {
        cout << new_pegs.size() << endl;
        if (new_pegs.size() != 0) {
            cout << new_pegs[0];
            for (int i=1; i<new_pegs.size(); i++) { cout << " " << new_pegs[i]; }
            cout << endl;
        }
    }

    return 0;
}
