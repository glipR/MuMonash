// MuMonash

#include <iostream>

using namespace std;

typedef pair<int, int> pii;

int main() {

    int biggest_x=-1;
    int biggest_y=-1;
    int second_biggest_x=-1;
    int second_biggest_y=-1;

    int num_coeffs;
    cin >> num_coeffs;

    pii polynomial[num_coeffs];

    for (int i=0; i<num_coeffs; i++) {
        int x, y;
        cin >> x >> y >> ws;
        polynomial[i] = pii(x, y);
        if (biggest_x == -1 || polynomial[biggest_x].first < x || (polynomial[biggest_x].first == x && polynomial[biggest_x].second < y)) {
            second_biggest_x = biggest_x;
            biggest_x = i;
        }
        if (biggest_y == -1 || polynomial[biggest_y].second < y || (polynomial[biggest_y].second == y && polynomial[biggest_y].first < x)) {
            second_biggest_y = biggest_y;
            biggest_y = i;
        }
    }

    bool bad = false;

    // cerr << biggest_x << ' ' << biggest_y << ' ' << second_biggest_x << ' ' << second_biggest_y << endl;

    // What happens if neither are removed?
        // Test bigx has x even
    if (polynomial[biggest_x].first % 2 == 1) {
        bad = true;
    }
        // Test bigy has y even
    if (polynomial[biggest_y].second % 2 == 1) {
        bad = true;
    }
    // What happens if bigx is removed?
    if (polynomial[second_biggest_x].first % 2 == 1) {
        bad = true;
    }
    // What happens if bigy is removed?
    if (polynomial[second_biggest_y].second % 2 == 1) {
        bad = true;
    }

    cout << (bad ? "Ani" : "Borna") << endl;

    return 0;
}
