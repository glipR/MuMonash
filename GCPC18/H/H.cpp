#include <iostream>
#include <cstring>

using namespace std;

typedef long long ll;

ll pow(ll a, ll b)
{
    if (b == 0) return 1;
    if (b == 1) return a;
    if (b == 2) return a*a;
    ll res = pow(a, b / 2);
    res *= res;
    if (b % 2) res *= a;
    return res;
}

int main()
{
    ll m;
    cin >> m;

    for (int n = 3; n <= 60; n++)
    {
        ll res = 0;
        ll s = 1;
        while (res < m)
            res += pow(s++, n-1);
        if (res == m)
        {
            cout << n << ' ' << s - 1 << endl;
            return 0;
        }
    }
    cout << "impossible" << endl;
}
