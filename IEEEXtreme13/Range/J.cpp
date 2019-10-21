#include <iostream>

using namespace std;

typedef long long ll;
const ll B = 1000001;
const ll MOD = 1000000007;
ll sing[B];
ll total[B];

ll foo(int b) {
    if (sing[b] != -1) return sing[b];
    if (b == 0 || b == 1) return 1;
    int i = 1;
    ll ans = 0;
    while ((1 << i) - 1 <= b) {
        ans += foo(b - (1 << i) +1);
        ans %= MOD;
        i++;
    }
    sing[b] = ans;
    return ans;
}

ll final_foo(int b) {
    if (b != 0) {
        ll res = foo(b);
        return (res * 2) % MOD;
    }
    return 1;
}

int main() {

    for (int i=0; i<B; i++) {
        sing[i] = -1;
        total[i] = -1;
    }

    total[0] = final_foo(0);
    for (int i=1; i<B; i++) {
        total[i] = (total[i-1] + final_foo(i)) % MOD;
    }

    int n;
    cin >> n;
    for (int i=0; i<n; i++) {
        int a, b;
        cin >> a >> b;
        ll ans = (total[b] - ( (a == 0) ? 0 : total[a-1])) % MOD;
        if (ans < 0) ans += MOD;
        cout << ans << endl;
    }
    for (int i=0; i<0; i++) {
        cerr << total[i] << endl;
    }
    return 0;
}
