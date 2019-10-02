#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll gcd(ll a, ll b)
{
    if (a < b)
        swap(a, b);
    while (b != 0)
    {
        int c = a % b;
        a = b;
        b = c;
    }
    return a;
}

struct Frac {
    ll num;
    ll den;
    Frac() { num = 0; den = 1; }
    Frac(ll a, ll b){ num = a; den = b; }

    void add(Frac f)
    {
        if (zero())
        {
            num = f.num;
            den = f.den;
            return;
        }
        if (f.zero()) return;
        ll newDen = (den * f.den) / gcd(den, f.den);
        ll newNum = (newDen / den) * num + (newDen / f.den) * f.num;
        num = newNum % MOD;
        den = newDen % MOD;
    }

    void subt(Frac f)
    {
        if (zero())
        {
            num = -1 * f.num;
            den = f.den;
            return;
        }
        if (f.zero()) return;
        ll newDen = (den * f.den) / gcd(den, f.den);
        ll newNum = (newDen / den) * num - (newDen / f.den) * f.num;
        num = newNum % MOD;
        den = newDen % MOD;
    }

    void mult(ll i)
    {
        num *= i;
        num %= MOD;
    }

    void mult(Frac f)
    {
        if (zero()) return;
        if (f.zero()) { num = 0; return; }
        num *= f.num;
        den *= f.den;

        num %= MOD;
        den %= MOD;
    }

    void inverse()
    {
        swap(num, den);
    }

    bool zero() { return num == 0; }
};

const int MAXN = 111;
int CONST;

int n;
Frac eq[MAXN][MAXN + 1];

void check_row_self(int i)
{
    if (!eq[i][i].zero())
    {
        if (eq[i][i].num == eq[i][i].den)
        {
            // Shouldn't reach here! (Written in a way that gives RE but not CE)
            int aa = 1;
            int bb = 10;
            cout << 1 / (10*aa - bb) << endl;
            //cout << "WWWW" << endl;
        }
        Frac change(1,1); 
        change.subt(eq[i][i]);
        change.inverse();
        eq[i][i].num = 0;
        for (int col = 0; col <= n; col++)
            eq[i][col].mult(change);
    }
}

void reduce(int row)
{
    for (int i = 0; i < row; i++)
    {
        if (eq[i][row].zero()) continue;
        for (int col = 0; col <= n; col++) // <= n because we also have CONST
        {
            if (eq[row][col].zero()) continue;
            Frac addition;
            addition.add(eq[row][col]);
            addition.mult(eq[i][row]);
            eq[i][col].add(addition);
        }
        eq[i][row].num = 0;
    }
}

void print_row(int row) // debug function
{
    for (int i = 0; i <= n; i++)
        cout << eq[row][i].num << '/' << eq[row][i].den << ", ";
    cout << endl;
}


ll power(ll a, ll b)
{
    if (b == 0) return 1;
    ll res = 1;
    if (b % 2)
    {
        res *= a;
        res %= MOD;
        b--;
    }
    ll sub = power(a, b/2) % MOD;
    res *= sub; res %= MOD;
    res *= sub; res %= MOD;
    return res;
}

ll inverse(ll x)
{
    return power(x, MOD-2);
}


int main()
{
    cin >> n;
    int x[MAXN];
    CONST = n;
    for (int i = 0; i < n; i++) cin >> x[i];

    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            int dest = i + j + 1;
            if (dest >= n-1) continue;
            if (x[dest] != 0) dest = x[dest]-1;

            eq[i][dest].add(Frac(1,6));
        }
        eq[i][CONST].num = 1;
        eq[i][CONST].den = 1;
    }


    for (int i = n-1; i >= 0; i--)
    {
        /*for (int row = 0; row < n; row++)
            print_row(row);
        cout << "=======" << endl;*/
        check_row_self(i);
        reduce(i);
    }
    //print_row(0);
    //cout << 1 << endl;
    cout << (eq[0][CONST].num * inverse(eq[0][CONST].den)) % MOD << endl;

}
