#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
    ll n, a, b;
    cin >> n >> a >> b;
    int valid = -1;
    for (ll i = 1; i <= 100000; i++) {
        if (i*a <= n && n <= i*b) {
            valid = i;
            break;
        }
    }
    if (valid == -1) {
        cout << "NO" << endl;
        return 0;
    }

    vector<int> soln(valid, a);
    int remaining = n - valid*a;
    for (int i = valid-1; i>=0; --i) {
        int change = min(remaining, (int)(b-a));
        soln[i] += change;
        remaining -= change;
    }
    cout << "YES" << endl;
    for (int i =0; i<valid; ++i) {
        cout << soln[i] << ' ';
    }
}
