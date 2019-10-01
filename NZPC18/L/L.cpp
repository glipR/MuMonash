#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

int cx, cy;

inline bool cover(int bigger, int smaller, int distance)
{
    return ((bigger - smaller) * cx) >= (cy * distance);
}

int tallest_covering(int height, int distance)
{
    double x = distance / cx;
    x *= cy;
    return height - x;
}

const int MAXN = 100001;

int main()
{
    int n;
    cin >> n >> cx >> cy;
    int h[MAXN];
    for (int i = 0; i < n; i++)
        cin >> h[i];


    sort(h, h + n);

    int l = 0, r = n;
    while (r - l > 1)
    {
        int mid = (r + l) / 2;
        bool happy = true;
        int dist = 1;

        multiset<int> remaining;
        for (int i = 0; i < n-mid; i++)
            remaining.insert(h[i]);

        for (int block = n-1; block >= n-mid; block--)
        {
            dist = 1;
            while (!remaining.empty())
            {
                auto it = remaining.upper_bound(tallest_covering(h[block], dist));
                if (it == remaining.begin())
                    break;
                it--;
                if (cover(h[block], *it, dist))
                {
                    dist++;
                    remaining.erase(it);
                }
                else break;
            }
        }

        if (remaining.empty())
            r = mid;
        else l = mid;
    }

    cout << n - r << endl;
}
