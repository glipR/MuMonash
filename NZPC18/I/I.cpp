// MuMonash

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

int main() {

    while (true) {

        int n;
        cin >> n >> ws;
        if (n == 0) break;

        double x;
        double bearing=0;
        double velx=0;

        for (int i=0; i<n; i++) {
            double ar, ax, ay;
            cin >> ar >> ax >> ay;
            x = x + velx * 0.01;
            velx += (ax * cos(bearing) + ay * sin(bearing)) * 0.01;
            bearing = bearing - (M_PI * ar * 0.01 / (double)180);
        }

        cout << fixed << setprecision(1) << x << endl;
    }

    return 0;
}
