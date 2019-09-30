// MuMonash

#include <cmath>
#include <iostream>
#include <iomanip>
#define X first
#define Y second

using namespace std;

long double distance(long double x1, long double x2, long double y1, long double y2) {
    return sqrtl(powl(x1 - x2, 2) + powl(y1 - y2, 2));
}

int main() {

    int x1, x2, y1, y2;
    int red_x, red_y, red_r;
    int blue_x, blue_y, blue_r;

    cin >> x1 >> y1 >> ws;
    cin >> x2 >> y2 >> ws;
    cin >> blue_x >> blue_y >> blue_r >> ws;
    cin >> red_x >> red_y >> red_r >> ws;

    // First, find the angle we need to rotate so we are facing the tngent of the circle.
    long double theta_1, theta_2;
    long double dist1, dist2;
    dist1 = distance(x1, red_x, y1, red_y);
    dist2 = distance(x2, red_x, y2, red_y);
    theta_1 = asin((long double)(red_r) / dist1);
    theta_2 = asin((long double)(red_r) / dist2);

    // [x, y] rotate theta = xcos-ysin, xsin + ycos
    long double vecx1, vecy1;
    vecx1 = (long double)(red_x - x1) * cos(theta_1);
    vecy1 = (long double)(red_y - y1) * cos(theta_1);
    long double vecx2, vecy2;
    vecx2 = (long double)(red_x - x2) * cos(theta_2);
    vecy2 = (long double)(red_y - y2) * cos(theta_2);

    pair<long double, long double> p11 {x1 + vecx1 * cos(theta_1) - vecy1 * sin(theta_1), y1 + vecx1 * sin(theta_1) + vecy1 * cos(theta_1)};
    pair<long double, long double> p12 {x1 + vecx1 * cos(theta_1) + vecy1 * sin(theta_1), y1 - vecx1 * sin(theta_1) + vecy1 * cos(theta_1)};
    pair<long double, long double> p21 {x2 + vecx2 * cos(theta_2) - vecy2 * sin(theta_2), y2 + vecx2 * sin(theta_2) + vecy2 * cos(theta_2)};
    pair<long double, long double> p22 {x2 + vecx2 * cos(theta_2) + vecy2 * sin(theta_2), y2 - vecx2 * sin(theta_2) + vecy2 * cos(theta_2)};

    long double phi11, phi12, phi21, phi22;
    phi11 = 2 * asinl(distance(p11.X, p21.X, p11.Y, p21.Y) / (long double)(2 * red_r));
    phi21 = 2 * asinl(distance(p12.X, p21.X, p12.Y, p21.Y) / (long double)(2 * red_r));
    phi12 = 2 * asinl(distance(p11.X, p22.X, p11.Y, p22.Y) / (long double)(2 * red_r));
    phi22 = 2 * asinl(distance(p12.X, p22.X, p12.Y, p22.Y) / (long double)(2 * red_r));

    long double circum = 8000;
    circum = min(circum, phi11 * red_r);
    circum = min(circum, phi12 * red_r);
    circum = min(circum, phi21 * red_r);
    circum = min(circum, phi22 * red_r);

    cout << fixed << setprecision(10) << circum + distance(0, vecx1, 0, vecy1) + distance(0, vecx2, 0, vecy2) << endl;

    return 0;
}
