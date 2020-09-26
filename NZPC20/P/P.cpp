#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

typedef long long ll;

ll GCD (ll a, ll b) {
    ll r, i;
    while(b != 0)
    {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

ll LCM (ll a, ll b)
{
    return (a * b) / GCD(a, b);
}

ll gcdExtended(ll a, ll b, ll *x, ll *y) {
   if (a == 0) {
      *x = 0;
      *y = 1;
      return b;
   }
   ll x1, y1;
   ll gcd = gcdExtended(b%a, a, &x1, &y1);
   *x = y1 - (b/a) * x1;
   *y = x1;
   return gcd;
}

struct Arm {
    ll weight;
    ll min_add;
    char lT, rT; // 'W' or 'A'
    ll lI, rI; // id
    ll lD, rD; // distance
    bool is_root;
};

Arm arms[10010];
ll weights[20010];

ll lweight(int arm)
{
    return arms[arm].lD * (arms[arm].lT == 'W' ? weights[arms[arm].lI] : arms[arms[arm].lI].weight);
}

ll rweight(int arm)
{
    return arms[arm].rD * (arms[arm].rT == 'W' ? weights[arms[arm].rI] : arms[arms[arm].rI].weight);
}

void solve(int arm)
{
    ll lT = arms[arm].lT, rT = arms[arm].rT, lI = arms[arm].lI, rI = arms[arm].rI;
    ll lD = arms[arm].lD, rD = arms[arm].rD;

    ll lMinAdd = -1, rMinAdd = -1;

    if (lT == 'W' && weights[lI] == -1)
        weights[lI] = 1;
    if (rT == 'W' && weights[rI] == -1)
        weights[rI] = 1;
    if (lT == 'A')
        solve(lI);
    if (rT == 'A')
        solve(rI);

    lMinAdd = lT == 'W' ? 1 : arms[lI].min_add;
    rMinAdd = rT == 'W' ? 1 : arms[rI].min_add;

    if (arm == 2)
        cerr << "--- " << lD << ' ' << rD << ' ' << arms[rI].weight << endl;

    ll A = lMinAdd * lD, B = rMinAdd * rD, C = rweight(arm) - lweight(arm);
    if (C < 0) C *= -1;

    if (lweight(arm) != rweight(arm))
    {
        // Ax - By = C
        // Ax' - By' = GCD(A,B)

        ll zA = lweight(arm) > rweight(arm) ? -1 : 1;
        ll zB = lweight(arm) < rweight(arm) ? -1 : 1;
        ll xp, yp;
        ll output = gcdExtended(zA*A, zB*B, &xp, &yp);
        ll M = C / output;
        xp *= M;
        yp *= M;

        cerr << zA*A << ' ' << zB*B << ' ' << xp << ' ' << yp << ' ' << M << ' ' << C << endl;

        if (lT == 'W')
            weights[lI] += xp;
        else
            arms[lI].weight += xp * lMinAdd;
        
        if (rT == 'W')
            weights[rI] += yp;
        else
            arms[rI].weight += yp * rMinAdd;
    }

/*
    while (lweight(arm) != rweight(arm))
    {
        if (lweight(arm) < rweight(arm))
        {
            ll min_add = lMinAdd * arms[arm].lD;
            ll amount = ((rweight(arm) - lweight(arm)) / min_add) + (((rweight(arm) - lweight(arm)) % min_add) != 0);
            if (lT == 'W')
                weights[lI] += amount;
            else
                arms[lI].weight += amount * lMinAdd;
        }

        if (rweight(arm) < lweight(arm))
        {
            ll min_add = rMinAdd * arms[arm].rD;
            ll amount = ((lweight(arm) - rweight(arm)) / min_add) + (((lweight(arm) - rweight(arm)) % min_add) != 0);
            if (rT == 'W')
                weights[rI] += amount;
            else
                arms[rI].weight += amount * rMinAdd;
        }
    }
*/
    arms[arm].weight = (lT == 'W' ? weights[lI] : arms[lI].weight) + (rT == 'W' ? weights[rI] : arms[rI].weight);
    ll mins_comply = LCM(lMinAdd, rMinAdd);
    arms[arm].min_add = LCM(mins_comply, (lD + rD) / GCD(lD, rD));
}

void init(int N)
{
    fill(weights, weights + N + N + 1, -1);
    for (int i = 0; i < N + 10; i++)
    {
        arms[i].weight = -1;
        arms[i].is_root = true;
    }
}

int main()
{
    int n;
    cin >> n;
    int cnt = 1;
    while (n != 0)
    {
        init(n + 1);
        for (int i = 1; i <= n; i++)
        {
            cin >> arms[i].lD >> arms[i].rD >> arms[i].lT >> arms[i].rT >> arms[i].lI >> arms[i].rI;
            if (arms[i].lT == 'A')
                arms[arms[i].lI].is_root = false;
            if (arms[i].rT == 'A')
                arms[arms[i].rT].is_root = false;
        }

        int m, w;
        cin >> m >> w;
        weights[m] = w;

        for (int i = 1; i <= n; i++)
            if (arms[i].is_root)
            {
                solve(i);
                cout << "Case " << cnt++ << ": " << arms[i].weight << endl;
                break;
            }

        cin >> n;
    }
}
