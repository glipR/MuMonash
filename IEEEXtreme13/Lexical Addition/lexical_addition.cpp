#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;

ll result[100011];
ll n, a, b;

void check(ll len)
{
    ll sum = len * a;
    for (int i = len - 1; i >= 0; i--)
    {
        if (sum >= n) break;
        result[i] += min(b-a, n-sum);
        sum += min(b-a, n-sum);
    }
}

int main()
{
    cin >> n >> a >> b;
    for (int i = 0; i < 100001; i++)
        result[i] = a;
    ll len = -1;
    for (int i = 1; i <= 100000; i++)
    {
        ll lower = i * a;
        ll upper = i * b;
        if (n >= lower && n <= upper)
        {
            len = i;
            break;
        }
    }
    if (len == -1) { cout << "NO" << endl; }
    else {
        cout << "YES" << endl;
        check(len);
        for (int i = 0; i < len; i++)
            cout << result[i] << ' ';
        cout << endl;
    }
}

