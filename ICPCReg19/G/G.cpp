// MuMonash
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>

#define x real()
#define y imag()

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ld> cpx;

ld det(cpx a, cpx b) {return (conj(a) * b).y; }

ld poly_area(const vector<cpx>& p) {
    ld r=0; int n=p.size();
    for (int j=0, i=n-1;j<n;i=j++) r+= det(p[i], p[j]);
    return r/2;
}

const ld EPS = 1e-9;

void sort_points(vector<cpx>& p) {
    cpx p1 = p[0];
    sort(p.begin(), p.end(), [p1](cpx a1, cpx a2){
        ld m1 = norm(a1 - p1), m2 = norm(a2 - p1);
        ld t1 = arg(a1 - p1), t2 = arg(a2 - p1);
        // Ensure p[0] remains first.
        if (m1 < EPS) return true;
        if (m2 < EPS) return false;
        // Sort by angle and then by magnitude (anti-clockwise).
        // Angle is -pi to pi. if +ve, then we want to sort by magnitude decreasing.
        // if -ve then we want to sort by magnitude increasing
        if (t1 < t2 - EPS) { return true; }
        if (t2 < t1 - EPS) { return false; }
        if (t1 > 0) {
            return m1 > m2;
        } else return m2 > m1;
    });
}

ll gcd(ll a, ll b) {
    if (b == 0) return a > 0 ? a : -a;
    return gcd(b, a%b);
}

int main() {

    ll n;
    cin >> n;

    vector<cpx> points;
    for (int i=0; i<n; i++) {
        ll a1, a2;
        cin >> a1 >> a2;
        points.push_back({ (ld)a1, (ld)a2 });
    }

    /*cerr << "Before sorting" << endl;

    for (auto p: points) { cerr << p << " "; }
    cerr << endl;*/

    sort_points(points);

    /*cerr << "After sorting" << endl;
    for (auto p: points) { cerr << p << " "; }
    cerr << endl;*/

    ld double_area = 2 * poly_area(points);

    for (int j=0, i=n-1;j<n;i=j++) {
        // remove squares interesect by p[i] to p[j];
        ll dx = roundl(abs(points[i].x - points[j].x));
        ll dy = roundl(abs(points[i].y - points[j].y));
        if (dx == 0 || dy == 0) continue;
        // Otherwise we have dx + dy - gcd(dx, dy) squares to count.
        double_area -= dx + dy - gcd(dx, dy);
    }

    cout << (ll) roundl(double_area / 2) << endl;

    return 0;
}
