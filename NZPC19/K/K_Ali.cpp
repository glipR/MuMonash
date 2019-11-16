#include <iostream>

using namespace std;

const int MAXN = 1000001;

int n;
int x[MAXN];
int table[MAXN];

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++) cin >> x[i];
    table[0] = 0;
    for (int i = 1; i < n; i++)
    {
        int pre = table[i-1];
        while (pre > 0 && x[pre] != x[i])
            pre = table[pre-1];
        if (x[pre] == x[i])
            table[i] = pre + 1;
    }

    cout << n - table[n-1] << endl;
}
