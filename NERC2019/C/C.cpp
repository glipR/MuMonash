#include <algorithm>
#include <iostream>
#include <vector>

#define X first
#define Y second

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<pll> vpl;

int main() {

    ll n, k;
    cin >> n >> k;

    vpl starts;
    vpl ends;

    ll costs[n];
    ll start_vals[n];
    ll end_vals[n];

    for (int i=0; i<n; i++) {
        ll l, r, p;
        cin >> l >> r >> p;
        starts.push_back({l, i});
        ends.push_back({r, i});
        start_vals[i] = l;
        end_vals[i] = r;
        costs[i] = p;
    }

    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());

    ll start = starts[0].X;
    ll end = ends[0].X;

    ll current = -k;
    ll best = -k;

    ll prev_time = start;

    for (int i=0; i<n; i++) {
        current += costs[ends[i].Y];
        if (i != n-1 && ends[i+1].X == ends[i].X) continue;
        current -= (ends[i].X - prev_time) * k;
        // cerr << start << " " << ends[i].X << " " << current << endl;
        if (current > best) {
            best = current;
            end = ends[i].X;
        }
        prev_time = ends[i].X;
    }

    ll prev_start = starts[0].Y;
    prev_time = starts[0].X;

    current = best;

    for (int i=1; i<n; i++) {
        current -= costs[prev_start];
        if (i != n-1 && starts[i+1].X == starts[i].X) continue;
        if (starts[i].X > end) break;
        current += (starts[i].X - prev_time) * k;
        // cerr << starts[i].X << " " << end << " " << current << endl;
        if (current > best) {
            best = current;
            start = starts[i].X;
        }
        prev_time = starts[i].X;
        prev_start = starts[i].Y;
    }

    if (best <= 0) {
        cout << 0 << endl;
    } else {
        int projects = 0;
        for (int i=0; i<n; i++) if (start_vals[i] >= start && end_vals[i] <= end) projects++;
        cout << best << " " << start << " " << end << " " << projects << endl;
        bool first = true;
        for (int i=0; i<n; i++) if (start_vals[i] >= start && end_vals[i] <= end) {
            if (!first) { cout << " "; }
            cout << i + 1;
            first = false;
        }
        cout << endl;
    }

    return 0;
}
