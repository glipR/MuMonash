// MuMonash

#include <iostream>

#define MAXN 100001

using namespace std;

typedef long long ll;

ll orig_melody[MAXN];
pair<ll, ll> ranges[MAXN];
ll solutions[MAXN];

int main() {

    ll n, l, r, k;
    cin >> n >> l >> r >> k;

    for (int i=0; i<n; i++) {
        cin >> orig_melody[i];
    }

    bool changed = true;
    bool bad = false;
    int iterations = 0;

    for (int i=0; i<n; i++)
        ranges[i] = pair<ll, ll>(l, r);
    while (changed && (!bad)) {
        iterations ++;
        changed = false;
        for (int i=0; i<n-1; i++) {
            pair<ll, ll> old_range = ranges[i+1];
            ranges[i+1].first = max(ranges[i].first - k, ranges[i+1].first);
            ranges[i+1].second = min(ranges[i].second + k, ranges[i+1].second);
            // Adjust the range for the next note.
            if (orig_melody[i] < orig_melody[i+1]) {
                // B[i] < B[i+1]
                ranges[i+1].first = max(ranges[i].first + 1, ranges[i+1].first);
            } else
            if (orig_melody[i] == orig_melody[i+1]) {
                ranges[i+1].first = max(ranges[i].first, ranges[i+1].first);
                ranges[i+1].second = min(ranges[i].second, ranges[i+1].second);
            } else {
                // B[i] > B[i+1]
                ranges[i+1].second = min(ranges[i].second - 1, ranges[i+1].second);
            }
            if (old_range != ranges[i+1]) changed = true;
        }

        // Go back to limit the original options.
        for (int i=n-1; i>0; i--) {
            pair<ll, ll> old_range = ranges[i-1];
            // Limit by range K.
            ranges[i].first = max(ranges[i-1].first - k, ranges[i].first);
            ranges[i].second = min(ranges[i-1].second + k, ranges[i].second);
            if (orig_melody[i-1] < orig_melody[i]) {
                // B[i-1] < B[i]
                ranges[i-1].second = min(ranges[i].second - 1, ranges[i-1].second);
            } else
            if (orig_melody[i-1] == orig_melody[i]) {
                // B[i-1] == B[i]
                ranges[i-1].first = max(ranges[i].first, ranges[i-1].first);
                ranges[i-1].second = min(ranges[i].second, ranges[i-1].second);
            } else {
                // B[i-1] > B[i]
                ranges[i-1].first = max(ranges[i].first + 1, ranges[i-1].first);
            }
            if (old_range != ranges[i-1]) changed = true;
        }
        for (int i=0; i<n; i++) {
            if (ranges[i].first > ranges[i].second) {
                bad = true;
            }
        }
    }

    // cerr << iterations << " Iterations" << endl;

    // Now pick the lexicographically smallest.
    for (int i=0; i<n; i++) {
        if (i == 0) {
            solutions[i] = ranges[i].first;
            continue;
        }
        if (orig_melody[i-1] < orig_melody[i]) {
            solutions[i] = solutions[i-1] + 1;
            if (solutions[i-1] + 1 > r) bad = true;
        } else
        if (orig_melody[i-1] == orig_melody[i]) {
            solutions[i] = solutions[i-1];
        } else {
            solutions[i] = max(max(ranges[i].first, solutions[i-1] - k), l);
        }
    }

    if (bad) {
        cout << -1 << endl;
    } else {
        for (int i=0; i<n; i++) {
            if (i != 0) { cout << " "; }
            cout << solutions[i];
        }
        cout << endl;
    }

    return 0;
}
