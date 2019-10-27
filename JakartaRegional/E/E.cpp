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

    ranges[0] = pair<ll, ll>(l, r);
    for (int i=0; i<n-1; i++) {
        pair<ll, ll> new_range(max(ranges[i].first - k, l), min(ranges[i].second + k, r));
        // Adjust the range for the next note.
        if (orig_melody[i] < orig_melody[i+1]) {
            // B[i] < B[i+1]
            new_range.first = max(ranges[i].first + 1, new_range.first);
        } else
        if (orig_melody[i] == orig_melody[i+1]) {
            new_range.first = max(ranges[i].first, new_range.first);
            new_range.second = min(ranges[i].second, new_range.second);
        } else {
            // B[i] > B[i+1]
            new_range.second = min(ranges[i].second - 1, new_range.second);
        }
        ranges[i+1] = new_range;
    }

    // Go back to limit the original options.
    for (int i=n; i>0; i--) {
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
    }

    bool bad = false;
    // Now pick the lexicographically smallest.
    for (int i=0; i<n; i++) {
        if (ranges[i].first > ranges[i].second) bad = true;
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
            solutions[i] = max(ranges[i].first, solutions[i-1] - k);
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
