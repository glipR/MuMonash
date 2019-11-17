#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

struct Fish {
    ll x, y, v, numpos, numneg;

    void reduce_y() {
        x = x + y * v;
        y = 0;
    }
};

int main() {

    int n;
    cin >> n;

    vector<Fish> fishies(n);

    for (int i=0; i<n; i++) {
        cin >> fishies[i].x >> fishies[i].y >> fishies[i].v;
        fishies[i].reduce_y();
    }

    // Sort by x increasing.
    sort(fishies.begin(), fishies.end(), [](Fish a, Fish b) {
        return a.x < b.x;
    });

    // Group fish by location.
    vector<Fish> grouped;
    ll current_x = -1e10;
    for (auto f: fishies) {
        if (f.x == current_x) {
            if (f.v == 1) grouped[grouped.size()-1].numpos++;
            else grouped[grouped.size()-1].numneg++;
        }
        if (f.x != current_x) {
            current_x = f.x;
            if (f.v == 1) { f.numpos = 1; f.numneg = 0; }
            else { f.numneg = 1; f.numpos = 0; }
            grouped.push_back(f);
        }
    }

    // Can we have two fish groups intercept (or start off intercepting)?
    // This is characterised by a positive followed by a negative, so keep a rolling maximum of positive fish.
    ll best = 0;
    ll largest_pos = 0;
    for (auto g: grouped) {
        largest_pos = max(largest_pos, g.numpos);
        best = max(best, largest_pos + g.numneg);
    }

    cout << best << endl;

    return 0;
}
