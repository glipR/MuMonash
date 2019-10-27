#include <iostream>
#include <algorithm>
#include <vector>

#define pb(a) push_back(a)

using namespace std;

struct Rect {
    int l; int w;
    Rect () {}
    Rect (int a, int b)
    {
        if (a > b) swap(a, b);
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
        int l, w;
        cin >> l >> w;
        x.pb(Rect(l, w));
    }

    sort(x.begin(), x.end());

    double ans = -1;

    int longest = 0;

    for (int i = x.size() - 1; i >= 0; i--)
    {
        ans = max(ans, 1.0*(1.0*(x[i].l * x[i].w) / 2));
        ans = max(ans, 1.0*(x[i].l * min(longest, x[i].w)));
        longest = max(longest, x[i].w);
    }

    printf("%.1f\n", ans);
}
