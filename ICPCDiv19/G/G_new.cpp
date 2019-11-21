#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef long double ld;

struct Rectangle {
    ll rx, ry, rw, rh;
};

int main() {

    int n;
    cin >> n;
    Rectangle bounding;
    cin >> bounding.rx >> bounding.ry >> bounding.rw >> bounding.rh;
    Rectangle blue;
    cin >> blue.rx >> blue.ry >> blue.rw >> blue.rh;
    vector<Rectangle> reds(n);
    for (int i=0; i<n; i++) {
        cin >> reds[i].rx >> reds[i].ry >> reds[i].rw >> reds[i].rh;
    }

    // First, find the interesting heights to consider placing the bottom right corner of the rectangle.
    vector<ll> points;
    for (int i=0; i<n; i++) {
        points.push_back(reds[i].ry + reds[i].rh);
        points.push_back(reds[i].ry - blue.rh);
    }
    points.push_back(blue.ry);
    points.push_back(bounding.ry + bounding.rh - blue.rh);
    points.push_back(bounding.ry);

    // Sort decreasing y.
    sort(points.begin(), points.end(), [](ll x, ll y) { return x > y; });
    // Sort rectangles by decreasing upper y.
    sort(reds.begin(), reds.end(), [](Rectangle r1, Rectangle r2){
        return r1.ry + r1.rh > r2.ry + r2.rh;
    });

    vector<Rectangle> current_rects;
    ll current_y = bounding.ry + bounding.rh + 1;
    ll best_square = 1e16;
    int current_rect_index = 0;
    for (int i=0; i<points.size(); i++) {
        if (points[i] > bounding.ry + bounding.rh - blue.rh) points[i] = bounding.ry + bounding.rh - blue.rh;
        if (points[i] < bounding.ry) continue;
        if (current_y == points[i]) continue;
        current_y = points[i];
        // cerr << "Checking y=" << current_y << endl;
        // Ensure all rectangles above me have been added
        // cerr << reds[current_rect_index].ry + reds[current_rect_index].rh << endl;
        while (current_rect_index < reds.size() && (reds[current_rect_index].ry + reds[current_rect_index].rh) > current_y) {
            // Sort by left hand side increasing.
            current_rects.insert(
                lower_bound(current_rects.begin(), current_rects.end(), reds[current_rect_index], [](Rectangle r1, Rectangle r2){
                    return r1.rx < r2.rx;
                }),
                reds[current_rect_index]
            );
            current_rect_index++;
        }
        // Try to find all sections of the line which can be reached.
        ll left_point = bounding.rx + blue.rw;
        ll right_point = left_point - 1;
        bool covers_end_point = false;
        for (auto rect: current_rects) {
            // cerr << rect.rx << " " << rect.ry << " " << rect.rw << " " << rect.rh << endl;
            if (rect.ry - blue.rh >= current_y) continue;
            if (rect.rx < bounding.rx + bounding.rw && rect.rx + rect.rw > bounding.rx + bounding.rw) {
                covers_end_point = true;
            }
            right_point = min(rect.rx, bounding.rx + bounding.rw);
            if (right_point >= left_point) {
                // cerr << "Left " << left_point << " to " << right_point << endl;
                // Possible values
                if (left_point >= blue.rx + blue.rw) {
                    // cerr << "Left" << endl;
                    best_square = min(best_square, (ll) (pow(blue.rx + blue.rw - left_point, 2) + pow(blue.ry - current_y, 2)));
                } else if (right_point <= blue.rx + blue.rw) {
                    // cerr << "Right" << endl;
                    best_square = min(best_square, (ll) (pow(blue.rx + blue.rw - right_point, 2) + pow(blue.ry - current_y, 2)));
                } else {
                    // cerr << "Point" << endl;
                    best_square = min(best_square, (ll) (pow(blue.ry - current_y, 2)));
                }
                // cerr << best_square << endl;
            }
            left_point = max(rect.rx + rect.rw + blue.rw, left_point);
            if (rect.rx > bounding.rx + bounding.rw) break;
        }
        if (!covers_end_point) {
            // We can go from left to end.
            if (bounding.rx + bounding.rw >= left_point) {
                // cerr << "Left " << left_point << " to " << bounding.rx + bounding.rw << endl;
                // Possible values
                if (left_point >= blue.rx + blue.rw) {
                    best_square = min(best_square, (ll) (pow(blue.rx + blue.rw - left_point, 2) + pow(blue.ry - current_y, 2)));
                } else if (bounding.rx + bounding.rw <= blue.rx + blue.rw) {
                    best_square = min(best_square, (ll) (pow(blue.rx + blue.rw - (bounding.rx + bounding.rw), 2) + pow(blue.ry - current_y, 2)));
                } else {
                    best_square = min(best_square, (ll) (pow(blue.ry - current_y, 2)));
                }
                // cerr << best_square << endl;
            }
        }
    }

    if (best_square == 1e16) {
        cout << -1 << endl;
    } else {
        cout << best_square << endl;
    }

    return 0;
}
