// H Done with sweepline.

#include <algorithm>
#include <iostream>
#include <vector>

#define pb push_back

using namespace std;

typedef long long ll;

struct Rect {
    ll a, b;
    Rect (ll x, ll y) {
        if (x < y) swap(x, y);
        a = x;
        b = y;
    }

    bool operator < (const Rect& other) const {
        return a < other.a;
    }
};

int main() {

    int n;
    cin >> n;
    vector<Rect> x;
    for (int i = 0; i < n; i++)
    {
        int l, w;
        cin >> l >> w;
        x.pb(Rect(l, w));
    }

    // Sort by lvals
    sort(x.begin(), x.end());
    // Keep a list of rvals for each lval, sorted decreasing.
    vector<ll> lvals;
    vector<vector<ll> > rvals;
    ll cur = -1;
    ll cur_index = -1;
    for (int i=0; i<n; i++) {
        if (x[i].a > cur) {
            cur = x[i].a;
            cur_index ++;
            lvals.pb(x[i].a);
            rvals.pb(vector<ll>());
            rvals[cur_index].pb(x[i].b);
        } else {
            // Insert into sorted list.
            rvals[cur_index].insert(lower_bound(rvals[cur_index].begin(), rvals[cur_index].end(), x[i].b), x[i].b);
        }
    }

    double max_area = 0;
    for (int i=0; i<n; i++) {
        max_area = max(max_area, x[i].a * x[i].b /(double) 2);
    }

    // Sweepline begin
    for (int i=0; i<lvals.size(); i++) {
        // If there are two rvals for this lval, then we can have two rects with size equal to the minimum of the top two rvals.
        if (rvals[i].size() > 1) {
            max_area = max(
                max_area,
                (double)(lvals[i] * (min(rvals[i][rvals[i].size() - 1], rvals[i][rvals[i].size() - 2])))
            );
        }
        // We can also move back some steps, until we find an rval greater than ours, and use the minimum of the maximum rval here and the maximum rval there.
        int j=i-1;
        while (j >= 0) {
            max_area = max(
                max_area,
                (double)(lvals[j] * min(rvals[i][rvals[i].size() - 1], rvals[j][rvals[j].size() - 1]))
            );
            if (rvals[i][rvals[i].size() - 1] < rvals[j][rvals[j].size() - 1]) break;
            j--;
        }
    }

    printf("%.1f\n", max_area);

    return 0;
}
