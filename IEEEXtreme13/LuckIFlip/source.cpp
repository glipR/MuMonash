#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

typedef long long ll;

int computeDist(ll a, ll b)
{
    ll res = a ^ b;
    ll cnt = 0;
    while (res > 0)
    {
        cnt += res % 2;
        res /= 2;
    }
    return cnt;
}

int main()
{
    int n;
    cin >> n;
    
    ll bets[200];
    ll wins[200];
    memset(wins, 0, sizeof(wins));
    memset(bets, 0, sizeof(bets));

    ll len = 0;

    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        len = s.length();
        for (int q = 0; q < s.length(); q++)
        {
            char c = s[q];
            bets[i] *= 2;
            bets[i] += c - '0';
        }
    }

    for (ll draw = 0; draw < (1 << len); draw++)
    {
        ll minValue = 100;
        bool moreThanOne = false;
        int minIndex;
        for (int i = 0; i < n; i++)
        {
            int value = computeDist(draw, bets[i]);
            if (value < minValue)
            {
                minValue = value;
                minIndex = i;
                moreThanOne = false;
            }
            else if (value == minValue)
            {
                moreThanOne = true;
            }
        }
        if (!moreThanOne)
            wins[minIndex]++;
    }

    sort(wins, wins + n);
    cout << wins[0] << endl;
}
