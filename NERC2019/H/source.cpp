#include <iostream>
#include <set>

using namespace std;

typedef long long ll;

ll repeat(int a, int b)
{
    ll res = a;
    b--;
    while (b > 0)
    {
        res *= 10;
        res += a;
        b--;
    }
    return res;
}

ll powerr(ll a, ll b)
{
    if (b == 1) return a;
    if (b == 0) return 1;
    ll res = powerr(a, b/2);
    if (b % 2)
        return res * res * a;
    return res*res;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int min_len = 10000000;
        int min_digit = 10;
        for (int i = 0; i < 10; i++)
        {
            int x;
            cin >> x;
            if (i == 0)
            {
                if (min_len >= x+2)
                {
                    min_len = x+2;
                    min_digit = 0;
                }
            }
            else
            {
                if (min_len > x+1 || (min_len == x+1 && min_digit > i))
                {
                    min_len = x+1;
                    min_digit = i;
                }
            }
        }
        if (min_digit == 0) { cout << 1; min_len--; }
        for (int i = 0; i < min_len; i++)
        {
            cout << min_digit;
        }
        cout << endl;
    }
}
