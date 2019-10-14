#include <iostream>
#include <cmath>

using namespace std;

int main() {

    int t;
    cin >> t;

    for (int i=0; i<t; i++) {
        int a, b, c, d, k;
        cin >> a >> b >> c >> d >> k;
        int utilities = ceil(a / (float)c) + ceil(b / (float)d);
        if (utilities > k) {
            cout << -1 << endl;
        } else {
            cout << ceil(a / (float)c) << ' ' << ceil(b / (float)d) << endl;
        }
    }

    return 0;
}
