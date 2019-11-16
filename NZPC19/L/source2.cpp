#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

ll table[11][11][11][11]; // N D U L

void solve(int n, int d, int u, int l, ll k)
{
    if (n == 0) return;

    ll passed = 0;

    // digits
    for (int i = 0; i < 10; i++)
    {
        ll prev = passed;
        passed += table[n-1][max(0, d-1)][u][l];
        if (passed >= k)
        {
            cout << i;
            solve(n-1, max(0, d-1), u, l, k - prev);
            return;
        }
    }

    // U
    for (int i = 0; i < 26; i++)
    {
        ll prev = passed;
        passed += table[n-1][d][max(0, u-1)][l];
        if (passed >= k)
        {
            cout << (char)('A' + i);
            solve(n-1, d, max(0, u-1), l, k - prev);
            return;
        }
    }

    // L
    for (int i = 0; i < 26; i++)
    {
        ll prev = passed;
        passed += table[n-1][d][u][max(0, l-1)];
        if (passed >= k)
        {
            cout << (char)('a' + i);
            solve(n-1, d, u, max(0, l-1), k - prev);
            return;
        }
    }
}

int main()
{
    int n, d, u, l; cin >> n >> d >> u >> l;
    ll k; cin >> k;

    table[0][0][0][0] = 1;
    for (int i = 0; i <= n; i++)
    {
        for (int x = 0; x <= d; x++)
        {
            for (int y = 0; y <= u; y++)
            {
                for (int z = 0; z <= l; z++)
                {
                    if (x + y + z > i) { table[i][x][y][z] = 0; continue; }
                    if (i == 0) { table[i][x][y][z] = 1; continue; }
                    table[i][x][y][z] = 
                        10 * table[i-1][max(0, x-1)][y][z] + 
                        26 * table[i-1][x][max(0, y-1)][z] + 
                        26 * table[i-1][x][y][max(0, z-1)];
                }
            }
        }
    }

    solve(n, d, u, l, k);
    cout << endl;
}
