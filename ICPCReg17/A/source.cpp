#include <iostream>

using namespace std;

typedef long long ll;

const int MAXN = 200001;

ll col[MAXN];

void print_col(int n)
{
    for (int i = 0; i < n; i++)
        cout << col[i] << ' ';
    cout << endl;
}

int main()
{
    int n;
    cin >> n;
    ll block[MAXN];
    for (int i = 0; i < n; i++) cin >> block[i];

    if (n == 1)
    {
        cout << block[0] << endl;
        return 0;
    }

    col[0] = block[0];
    col[n-1] = block[n-1];

    ll sum = col[0] + col[n-1];
    
    for (int i = 1; i < n-1; i++)
    {
        col[i] = (col[i-1] % block[i]) ? ((col[i-1] / block[i]) + 1) * block[i] : col[i-1];
        sum += col[i];
    }

    //print_col(n);

    ll ans = sum;

    for (int i = n-2; i > 0; i--)
    {
        ll old = col[i];
        col[i] = (col[i+1] % block[i]) ? ((col[i+1] / block[i]) + 1) * block[i] : col[i+1];
        sum += col[i] - old;
        ans = min(ans, sum);
        //print_col(n);
    }

    cout << ans << endl;
}
