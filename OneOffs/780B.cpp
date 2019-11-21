#include <iostream>
#include <cmath>
#include <iomanip>

#define MAXN 60005

using namespace std;

typedef long long ll;
typedef long double ld;

ll points[MAXN];
ll velocities[MAXN];

int main() {

    int n;
    cin >> n;

    ld start = 1e10;
    ld end = 0;

    for (int i=0; i<n; i++) {
        cin >> points[i];
        start = min(start, (ld) points[i]);
        end = max(end, (ld) points[i]);
    }
    for (int i=0; i<n; i++) {
        cin >> velocities[i];
    }

    ld maxt = end - start;
    ld mint = 0;

    while (maxt - mint > 1e-9) {
        ld medt = (maxt + mint) / ((ld) 2);
        ld start_a = 0;
        ld end_a = 1e10;
        for (int i=0; i<n; i++) {
            start_a = max(start_a, points[i] - velocities[i] * medt);
            end_a = min(end_a, points[i] + velocities[i] * medt);
        }
        // cerr << mint << " " << medt << " " << maxt << " " << start_a << " " << end_a << endl;
        if (start_a < end_a) maxt = medt;
        else mint = medt;
    }

    cout << setprecision(12) << fixed << maxt << endl;

    return 0;
}
