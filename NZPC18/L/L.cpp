#include <iostream>
#include <algorithm>

using namespace std;

int cx, cy;

inline bool cover(int bigger, int smaller, int distance)
{
    return ((bigger - smaller) * cx) >= (cy * distance);
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
        int block = n - mid, distance = 1;
        bool happy = true;
        for (int i = 0; i < n-mid; i++)
        {
            if (block == n)
            {
                happy = false;
                break;
            }
            if (cover(h[block], h[i], distance))
                distance++;
            else {
                block++;
                distance = 1;
                i--;
            }
        }

        if (happy)
            r = mid;
        else l = mid;
    }

    cout << n - r << endl;
}
