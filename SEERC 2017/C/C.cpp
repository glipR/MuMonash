#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct triple {
    int x, y, z;
    triple (int a, int b, int c) : x(a), y(b), z(c) {}
};

int main() {

    int n, m;
    cin >> n >> m >> ws;

    int colours[n];
    pair<int, int> first_last[m];
    bool used[m];

    for (int i=0; i<m; i++) {
        first_last[i] = {-1, -1};
        used[i] = false;
    }

    for (int i=0; i<n; i++) {
        cin >> colours[i] >> ws;
        if (first_last[colours[i]-1].first == -1) {
            first_last[colours[i]-1].first = i;
        }
        first_last[colours[i]-1].second = i;
    }

    vector<triple> actions;
    for (int i=0; i<n; i++) {
        if (!used[colours[i]-1]) {
            // Colour from first to last occurence.
            actions.push_back(triple(colours[i], first_last[colours[i]-1].first, first_last[colours[i]-1].second));
            used[colours[i]-1] = true;
        }
    }

    for (int i=0; i<m; i++) {
        if (!used[i]) {
            cout << i+1 << ' ' << 1 << ' ' << 1 << endl;
        }
    }
    for (triple t: actions) {
        cout << t.x << ' ' << t.y + 1 << ' ' << t.z + 1 << endl;
    }

    return 0;
}
