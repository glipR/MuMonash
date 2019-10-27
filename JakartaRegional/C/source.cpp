#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1e5 + 10;

int main()
{
    ios::sync_with_stdio(0);
    int n; cin >> n;
    int r[MAXN], c[MAXN];
    int sumR[MAXN], sumC[MAXN];
    int q; cin >> q;
    int x;
    for (int i = 0; i < n; i++) 
    { 
        cin >> x;
        r[i] = x % 2;
        sumR[i] = r[i];
        if (i != 0)
            sumR[i] += sumR[i-1];
    }
    for (int i = 0; i < n; i++) 
    {
        cin >> x;
        c[i] = x % 2;
        sumC[i] = c[i];
        if (i != 0)
            sumC[i] += sumC[i-1];
    }

    for (int i = 0; i < q; i++)
    {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        if (r1 > r2) swap(r1, r2);
        if (c1 > c2) swap(c1, c2);
        r1--; r2--; c1--; c2--;
        int rValue = sumR[r2] - (r1 > 0 ? sumR[r1-1] : 0);
        int cValue = sumC[c2] - (c1 > 0 ? sumC[c1-1] : 0);
        if ((rValue == 0 || rValue == (r2 - r1 + 1)) && (cValue == 0 || cValue == (c2 - c1 + 1)))
            cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}
