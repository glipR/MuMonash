#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

#define X first
#define Y second

using namespace std;

typedef long long ll;
typedef long double ld;

int main() {

    int n, k;
    cin >> n >> k;

    ll points[n+1];
    for (int i=0; i<n+1; i++) { cin >> points[i]; }

    for (int query=0; query<k; query++) {
        ld g;
        cin >> g;
        vector<ll> translated_points(n+1);
        vector<ll> values;
        vector<ll> leftmost;
        vector<ll> rightmost;
        for (int i=0; i<n+1; i++) {
            translated_points[i] = points[i] - 10 * i * g;
            // cerr << translated_points[i] << endl;
            if (binary_search(values.begin(), values.end(), translated_points[i])) {
                auto index = lower_bound(values.begin(), values.end(), translated_points[i]);
                rightmost[index - values.begin()] = i;
            } else {
                auto lm = lower_bound(values.begin(), values.end(), translated_points[i]);
                // cerr << "Inserting " << translated_points[i] << " at " << lm - values.begin() << endl;
                int index = lm - values.begin();
                values.insert(values.begin() + index, translated_points[i]);
                leftmost.insert(leftmost.begin() + index, i);
                rightmost.insert(rightmost.begin() + index, i);
            }
        }
        // We now have leftmost and rightmost, as well as all possible values.
        ll best = -1;
        vector<pair<ll, ll> > options;
        ll rm = -1;
        for (int i=values.size()-1; i>=0; i--) {
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

        if (best == 0) {
            cout << "impossible" << endl;
        }
        else {
            ld actual_best = best;
            for (auto option: options) {
                // Try extending either way.
                // Extending left:
                // translated[option.X] + (translated[option.X-1] - translated[option.X]) * y = translated[option.Y]
                // y = (translated[option.Y] - translated[option.X]) / (translated[option.X-1] - translated[option.X]).
                // Extending right:
                // x = (translated[option.X] - translated[option.Y]) / (translated[option.Y+1] - translated[option.Y]).
                if (option.X > 0)
                    actual_best = max(actual_best, best + ((ld)(translated_points[option.Y] - translated_points[option.X])) / ((ld)(translated_points[option.X-1] - translated_points[option.X])));
                if (option.Y < n)
                    actual_best = max(actual_best, best + ((ld)(translated_points[option.X] - translated_points[option.Y])) / ((ld)(translated_points[option.Y+1] - translated_points[option.Y])));
            }
            cout << setprecision(9) << fixed << actual_best << endl;
        }

    }


    return 0;
}
