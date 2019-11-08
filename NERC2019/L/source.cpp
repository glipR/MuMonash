#include <iostream>
#include <algorithm>

using namespace std;

int match_sizes(int g1, int g2, int g3, int rest)
{
    int M = max(g1, max(g2, g3));
    while (g1 < M && rest > 0) { g1++; rest--; }
    while (g2 < M && rest > 0) { g2++; rest--; }
    while (g3 < M && rest > 0) { g3++; rest--; }
    int div = rest / 3; rest %= 3;
    g1 += div;
    g2 += div;
    g3 += div;
    M = max(g1, max(g2, g3));
    int cnt = 0;
    cnt += g1 == M;
    cnt += g2 == M;
    cnt += g3 == M;
    if (cnt == 3)
    {
        if (rest > 0)
            return M + 1;
        return M;
    }
    if (cnt == 2)
    {
        if (rest > 1)
            return M + 1;
        return M;
    }
    if (cnt == 1)
        return M;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int a, b, c;
        cin >> a >> b >> c;

        int ans = 100000000;
        for (int size = 0; size <= a; size++)
            ans = min(ans, match_sizes(size, a-size, c, b));
        for (int size = 0; size <= c; size++)
            ans = min(ans, match_sizes(size, c-size, a, b));
        cout << ans << endl;
    }
}
