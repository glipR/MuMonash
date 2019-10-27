#include <iostream>
#include <algorithm>
#include <vector>

#define pb(a) push_back(a)

using namespace std;

struct Rect {
    int l; int w;
    Rect () {}
    Rect (int a, int b, bool q = true)
    {
        if (q)
            if (a > b) swap(a, b);
        if (!q) 
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
    vector<Rect> x, y;
    for (int i = 0; i < n; i++)
    {
        int l, w;
        cin >> l >> w;
        x.pb(Rect(l, w));
        y.pb(Rect(l, w, false));
    }

    sort(x.begin(), x.end());
    sort(y.begin(), y.end());

    double ans = -1;

    int longest1 = 0;
    int longest2 = 0;

    for (int i = x.size() - 1; i >= 0; i--)
    {
        ans = max(ans, 1.0*(1.0*(x[i].l * x[i].w) / 2));
        ans = max(ans, 1.0*(x[i].l * min(longest1, x[i].w)));
        ans = max(ans, 1.0*(y[i].l * min(longest2, y[i].w)));
        longest1 = max(longest1, x[i].w);
        longest2 = max(longest2, y[i].w);
    }

    printf("%.1f\n", ans);
}
