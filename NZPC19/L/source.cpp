#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

ll mpow(ll a, ll b)
{
    ll res = 1;
    while (b--)
        res *= a;
    return res;
}

ll table[11][11][11]; // D U L

string res = "", ans = "";
void solve(ll n, ll d, ll u, ll l, ll k)
{
    if (n == 0) return;
    
    ll passed = 0;
    // Digits
    if (d > 0)
    {
        for (int i = 0; i < 10; i++)
        {
            passed += table[d-1][u][l];
            if (passed >= k)
            {
                res += (char)('0' + i);
                solve(n-1, d-1, u, l, k - (passed - table[d-1][u][l]));
                return;
            }
        }
    }

    // U
    if (u > 0)
    {
        for (int i = 0; i < 26; i++)
        {
            passed += table[d][u-1][l];
            if (passed >= k)
            {
                res += (char)('A' + i);
                solve(n-1, d, u-1, l, k - (passed - table[d][u-1][l]));
                return;
            }
        }
    }

    // L
    if (l > 0)
    {
        for (int i = 0; i < 26; i++)
        {
            passed += table[d][u][l-1];
            if (passed >= k)
            {
                res += (char)('a' + i);
                solve(n-1, d, u, l-1, k - (passed - table[d][u][l-1]));
                return;
            }
        }
    }

}

int main()
{
    int n, l, u, d;
    cin >> n >> d >> u >> l;
    ll k;
    cin >> k;

    table[0][0][0] = 1;

    ll C[11][11];
    for (int i = 0; i <= 10; i++)
    {
        C[0][i] = 0;
        C[i][0] = 1;
    }

    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
            C[i][j] = C[i-1][j-1] + C[i-1][j];

    for (int c1 = 0; c1 <= 10; c1++)
        for (int c2 = 0; c2 <= 10; c2++)
            for (int c3 = 0; c3 <= 10; c3++)
            {
                int len = c1 + c2 + c3;
                table[c1][c2][c3] = C[len][c1] * C[len-c1][c2] * mpow(10, c1) * mpow(26, c2 + c3);
            }

    for (int i = d; i <= n; i++)
        for (int j = u; j <= n; j++)
        {
            int z = n - i - j;
            if (z < l) continue;
            res = "";
            solve(n, i, j, z, k);
            cerr << "digits: " << i << ", upper: " << j << ", lower: " << z << ", res: " << res << endl;
            if (res.length() == n && (ans == "" || res < ans))
                ans = res;
        }

    cout << ans << endl;

}
