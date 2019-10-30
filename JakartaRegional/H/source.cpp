#include <iostream>
#include <algorithm>
#include <vector>

#define pb(a) push_back(a)

using namespace std;

typedef long long ll;

struct Rect {
    ll l; ll w;
    Rect () {}
    Rect (ll a, ll b)
    {
        if (a < b) swap(a, b);
        l = a;
        w = b;
    }

    bool operator < (const Rect& other) const
    {
        return l < other.l;
    }
};


int main()
{
    int n;
    cin >> n;
    vector<Rect> x;
    for (int i = 0; i < n; i++)
    {
        ll l, w;
        cin >> l >> w;
        x.pb(Rect(l, w));
    }

    sort(x.begin(), x.end());

    ll sameLand = -1;

    ll differentLand = -1;

    ll longest = 0;

    for (int i = x.size() - 1; i >= 0; i--)
    {
        if (x[i].l * x[i].w > sameLand)
            sameLand = x[i].l * x[i].w;
        differentLand = max(differentLand, (x[i].l * min(longest, x[i].w)));
        longest = max(longest, x[i].w);
    }
    if (sameLand > 2*differentLand)
    {
        if (sameLand % 2)
        {
            sameLand++;
            sameLand /= 2;
            sameLand--;
            cout << sameLand << ".5" << endl;
        }
        else
        {
            cout << sameLand / 2 << ".0" << endl;
        }
    }
    else
    {
        cout << differentLand << ".0" << endl;
    }
}
