#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

#define X first
#define Y second

using namespace std;

typedef long long ll;
typedef long double ld;

struct Point {
    ll val;
    int index;
};

int main() {

    int n, k;
    cin >> n >> k;

    ll points[n+1];
    for (int i=0; i<n+1; i++) { cin >> points[i]; }

    for (int query=0; query<k; query++) {
        ld g;
        cin >> g;
        vector<Point> translated_points(n+1);
        vector<ll> values;
        vector<Point> inter_values;
        vector<int> leftmost;
        vector<int> rightmost;
        for (int i=0; i<n+1; i++) {
            translated_points[i].val = (points[i] - 10 * i * g) * 1e5;
            translated_points[i].index = i;
        }
        inter_values = translated_points;
        sort(inter_values.begin(), inter_values.end(), [](Point a, Point b) {
            return (a.val < b.val) || ((a.val == b.val) && a.index < b.index);
        });
        values.push_back(inter_values[0].val);
        leftmost.push_back(inter_values[0].index);
        rightmost.push_back(inter_values[0].index);
        for (int i=1; i<inter_values.size(); i++) {
            if (inter_values[i].val != values[values.size() - 1]) {
                values.push_back(inter_values[i].val);
                leftmost.push_back(inter_values[i].index);
                rightmost.push_back(inter_values[i].index);
            } else {
                rightmost[rightmost.size() - 1] = inter_values[i].index;
            }
        }
        // We now have leftmost and rightmost, as well as all possible values.
        ll best = -1;
        vector<pair<ll, ll> > options;
        int rm = -1;
        for (int i=values.size()-1; i>=0; i--) {
            // Look at values decreasing.
            rm = max(rightmost[i], rm);
            // cerr << ">=" << values[i] << " is first seen at " << leftmost[i] << " and last seen at " << rm << endl;
            if (rm - leftmost[i] > best) {
                best = rm - leftmost[i];
                options.clear();
                options.push_back({ leftmost[i], rm });
            } else if (rm - leftmost[i] == best) {
                options.push_back({ leftmost[i], rm });
            }
        }

        if (best <= 0) {
            cout << "impossible" << endl;
        }
        else {
            ld actual_best = best;
            for (auto option: options) {
                // cerr << option.X << " " << option.Y << endl;
                // Try extending either way.
                // Extending left:
                // translated[option.X] + (translated[option.X-1] - translated[option.X]) * y = translated[option.Y]
                // y = (translated[option.Y] - translated[option.X]) / (translated[option.X-1] - translated[option.X]).
                // Extending right:
                // x = (translated[option.X] - translated[option.Y]) / (translated[option.Y+1] - translated[option.Y]).
                if (option.X > 0) {
                    actual_best = max(actual_best, best + ((ld)(translated_points[option.Y].val - translated_points[option.X].val)) / ((ld)(translated_points[option.X-1].val - translated_points[option.X].val)));
                    // cerr << "x" << best + ((ld)(translated_points[option.Y].val - translated_points[option.X].val)) / ((ld)(translated_points[option.X-1].val - translated_points[option.X].val)) << endl;
                }
                if (option.Y < n) {
                    actual_best = max(actual_best, best + ((ld)(translated_points[option.X].val - translated_points[option.Y].val)) / ((ld)(translated_points[option.Y+1].val - translated_points[option.Y].val)));
                    // cerr << "y" << best + ((ld)(translated_points[option.X].val - translated_points[option.Y].val)) / ((ld)(translated_points[option.Y+1].val - translated_points[option.Y].val)) << endl;
                }
            }

            cout << setprecision(12) << fixed << actual_best << endl;
        }

    }


    return 0;
}
