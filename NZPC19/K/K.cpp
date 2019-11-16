#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;

template<typename T> vi z_array(const T& s) {
    int n = (int)s.size(), L = 0, R = 0; vi z(n, n-1);
    for (int i=1, j; i<n; i++) {
        j = max(min(z[i-L],R-i),0);
        for (; i+j < n && s[i+j] == s[j]; j++);
        z[i] = j;
        if (i + z[i] > R) R = i + z[i], L = i;
    }
    return z;
}

int main() {

    int n;
    cin >> n;

    vi values(n);
    for (int i=0; i<n; i++) { cin >> values[i]; }

    vi val = z_array<vi>(values);

    int p;
    for (p=1; p<=n; p++) {
        if (p == n) break;
        if (val[p] == n - p) break;
    }

    cout << p << endl;

    return 0;
}
