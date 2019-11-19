#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef long long ll;

unordered_map<ll, ll> DP;
vector<ll> startpoints;
vector<ll> endpoints;

ll s, d, t;

ll linear_interp(ll distance) {
    // Try just swimming
    ll score = distance;
    // Try just jumping
    score = min(score, (distance / d) * t + (distance % d == 0 ? 0 : t));
    // Try jumping and then swimming
    score = min(score, (distance / d) * t + (distance % d));
    return score;
}

ll solve(ll location) {
    if (location == s) return 0;
    if (DP.count(location) != 0) return DP[location];
    // Find the next start point.
    // cerr << "Evaluating at " << location << endl;
    ll island_index = upper_bound(endpoints.begin(), endpoints.end(), location) - endpoints.begin();
    ll up = startpoints[island_index];
    // cerr << "Closest start is " << up << endl;
    ll soln = s * t;
    // If at a starting point, we can just try jumping d units and making sure we land within an island.
    if (binary_search(startpoints.begin(), startpoints.end(), location)) {
        if (
            (lower_bound(startpoints.begin(), startpoints.end(), location + d) - startpoints.begin()) !=
            (upper_bound(endpoints.begin(), endpoints.end(), location + d) - endpoints.begin()) + 1
        ) {
            soln = min(soln, t + solve(min(location + d, s)));
        }
    }
    if (up != location) {
        // cerr << "Jumping to " << up << endl;
        soln = min(soln, linear_interp(up - location) + solve(up));
        // cerr << "Can get from " << location << " in " << soln << endl;
    }
    for (int i=island_index; i<startpoints.size(); i++) {
        // Try jumping to the start or end of this island.
        if (startpoints[i] - d <= up && startpoints[i] != location) {
            // cerr << "Jumping to " << startpoints[i] << endl;
            soln = min(soln, t + linear_interp(max((ll)0, startpoints[i] - d - location)) + solve(startpoints[i]));
            // cerr << "Can get from " << location << " in " << soln << endl;
        }
        if (endpoints[i] - d <= up && endpoints[i] != location) {
            // cerr << "Jumping to " << endpoints[i] << endl;
            soln = min(soln, t + linear_interp(max((ll)0, endpoints[i] - d - location)) + solve(endpoints[i]));
            // cerr << "Can get from " << location << " in " << soln << endl;
        }
    }
    DP[location] = soln;
    return soln;
}

int main() {

    cin >> s >> d >> t;
    startpoints.push_back(0);
    endpoints.push_back(0);
    int n;
    cin >> n;
    for (int i=0; i<n; i++) {
        ll a, b;
        cin >> a >> b;
        startpoints.push_back(a);
        endpoints.push_back(b);
    }
    startpoints.push_back(s);
    endpoints.push_back(s);

    cout << solve(0) << endl;

    return 0;
}
