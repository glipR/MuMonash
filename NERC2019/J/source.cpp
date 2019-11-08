#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

ll c[30010];
ll table[30010];

ll check(ll n, ll row)
{
    for (int i = 0; i < n; i++)
        table[i] = c[i];

    ll res = 0;
    for (int i = 0; i < n-1; i++)
    {
        res += table[i] / row;
        table[i] %= row;
        if (table[i] > 0 && table[i] + table[i+1] >= row)
        {
            table[i+1] -= row - table[i];
            res++;
        }
    }
    res += table[n-1] / row;
    return res;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        ll n, k;
        cin >> n >> k;
        for (int i = 0; i < n; i++)
            cin >> c[i];

        ll l = 0, r = 3 * 1e16;
        while (r - l > 1)
        {
            ll mid = (l + r) / 2;
            if (check(n, mid) >= k)
                l = mid;
            else r = mid;
        }
        cout << l * k << endl;
    }
}
