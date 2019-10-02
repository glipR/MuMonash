// MuMonash

// Currently WA :(

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct Rectangle {

    int lx, ly, w, h;

    Rectangle() {};
    Rectangle(int lx, int ly, int w, int h): lx(lx), ly(ly), w(w), h(h) {}

    bool operator < (const Rectangle& rect) const {
        return (ly + h > rect.ly + rect.h);
    }
};

struct left_less {
    inline bool operator() (const Rectangle& r1, const Rectangle& r2) {
        return (r1.lx < r2.lx);
    }
};

int main() {

    int best_dist = -1;

    int n_red;
    cin >> n_red >> ws;

    Rectangle bounding;
    cin >> bounding.lx >> bounding.ly >> bounding.w >> bounding.h >> ws;

    Rectangle blue;
    cin >> blue.lx >> blue.ly >> blue.w >> blue.h >> ws;

    Rectangle rectangles[n_red];
    for (int x=0; x<n_red; x++) {
        cin >> rectangles[x].lx >> rectangles[x].ly >> rectangles[x].w >> rectangles[x].h >> ws;
    }

    // We can place the bottom right corner of the blue rectangle as long as it doesn't intersect the rectangle
    // r_x, r_y, r_w + blue.w, r_h  For each red rectangle r_x, r_y - bh_y, r_w + blue.w, r_h + bh_y.

    int current_top=bounding.ly + bounding.h;
    vector<int> special_points;
    for (int x=0; x<n_red; x++) {
        special_points.push_back(rectangles[x].ly - blue.h);
        special_points.push_back(rectangles[x].ly + rectangles[x].h);
    }
    special_points.push_back(bounding.ly);
    // Special points in Y space decreasing.
    sort(special_points.begin(), special_points.end(), greater<int>());
    // Sort rectangles by decreasing top bound.
    sort(rectangles, rectangles + sizeof(rectangles) / sizeof(rectangles[0]));
    int prev_top = bounding.ly + bounding.h - blue.h;
    int included_rects = 0;
    vector<Rectangle> rects = vector<Rectangle>();
    for (int i=0; i<special_points.size(); i++) {
        if (special_points[i] < bounding.ly) special_points[i] = bounding.ly;
        if (special_points[i] > prev_top) {
            continue;
        }
        // Next special point is below the previous top, so we have to check the rectangles above the special point.
        while (included_rects < n_red && (rectangles[included_rects].ly + rectangles[included_rects].h) > special_points[i]) {
            rects.push_back(rectangles[included_rects]);
            included_rects++;
        };

        // Now any of the first `included_rects` rectangles COULD intersect the area from left to right.
        // Inner sweepline.
        // cerr << "Searching from " << special_points[i] << " to " << prev_top << endl;
        // cerr << "Using first " << included_rects << " rectangles" << endl;
        sort(rects.begin(), rects.end(), left_less());
        int right_bound = bounding.lx + blue.w;
        for (auto rect: rects) {
            if (rect.ly - blue.h >= prev_top) {
                // cerr << "We can skip " << rect.lx << rect.ly << endl;
                continue;
            }
            // cerr << rect.lx << ' ' << rect.ly << ' ' << rect.w << ' ' << rect.h << endl;
            if (rect.lx < right_bound) {
                right_bound = max(right_bound, rect.lx + rect.w + blue.w);
                continue;
            }
            // Free space between right_bound and rect.lx.
            // cerr << "Free from x " << right_bound << " to " << rect.lx << ", y " << special_points[i] << " to " << prev_top << endl;
            int dist = 0;
            if (blue.lx + blue.w < right_bound) dist += right_bound - blue.lx - blue.w;
            if (blue.lx + blue.w > rect.lx) dist += blue.lx + blue.w - rect.lx;
            if (blue.ly < special_points[i]) dist += special_points[i] - blue.ly;
            if (blue.ly > prev_top) dist += blue.ly - prev_top;
            if ((best_dist == -1) || (best_dist > dist)) best_dist = dist;
            right_bound = rect.lx + rect.w + blue.w;
        }
        if (right_bound <= bounding.lx + bounding.w) {
            // Free space between right_bound and rect.lx.
            // cerr << "Free from x " << right_bound << " to " << bounding.lx + bounding.w << ", y " << special_points[i] << " to " << prev_top << endl;
            int dist = 0;
            if (blue.lx + blue.w < right_bound) dist += right_bound - blue.lx - blue.w;
            if (blue.lx + blue.w > bounding.lx + bounding.w) dist += blue.lx + blue.w - bounding.lx + bounding.w;
            if (blue.ly < special_points[i]) dist += special_points[i] - blue.ly;
            if (blue.ly > prev_top) dist += blue.ly - prev_top;
            if ((best_dist == -1) || (best_dist > dist)) best_dist = dist;
        }
        prev_top = special_points[i];

    }

    if (best_dist == -1) {
        cout << -1 << endl;
    } else {
        // cerr << best_dist << endl;
        cout << setprecision(18) << powl(best_dist, 2) << endl;
    }

    return 0;
}
