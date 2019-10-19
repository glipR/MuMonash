// Ah shit, here we go again
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define X first
#define Y second

typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double, double> mp;
typedef vector<pii> vpi;

int main() {

    ll n, m;
    cin >> n >> m;

    vpi polygon;
    for (ll i=0; i<n; i++) {
        ll a, b;
        cin >> a >> b;
        polygon.push_back(pii(a, b));
    }

    vpi points;
    for (ll i=0; i<n; i++) {
        ll a, b;
        cin >> a >> b;
        points.push_back(pii(a, b));
    }

    mp midpoint(0, 0);
    for (ll i=0; i<n; i++) {
        midpoint.X += polygon[i].X / (double) n;
        midpoint.Y += polygon[i].Y / (double) n;
    }

    // Radially sort the points from the midpoint.
    double angle(mp p1, pii p2) {
        double dot = p1.X * p2.X + p1.Y * p2.Y;
        double det = p1.X * p2.Y - p1.Y * p2.X;
        return atan2(det, dot);
    }


    return 0;
}
