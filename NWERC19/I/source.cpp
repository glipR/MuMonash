#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1000001;

int x[MAXN];

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> x[i];

    int l = 0, pointer = 1;
    while (pointer < n && x[pointer] >= x[l])
    {
        if (x[pointer] > x[l]) l = pointer;
        pointer++;
    }

    int r = l;
    while (r < n-1 && x[r+1] <= x[r]) r++;

    reverse(x + l, x + r + 1);

    bool f = true;
    for (int i = 0; i < n-1; i++) f &= x[i+1] >= x[i];
    
    if (f) cout << l + 1 << ' ' << r + 1 << endl;
    else cout << "impossible" << endl;
}
