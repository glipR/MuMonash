#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int main()
{
    ll n, k;
    cin >> n >> k;
    ll team[8010];
    for (int i = 0; i < n; i++)
    {
        ll x; cin >> x;
        team[x-1]++;
    }
    sort(team, team + k);
    
    ll ans = 10000000000000;
    
    ll start = 0;
    while (team[start] == 0) start++;
    
    k -= start;

    for (int num = 0; num <= k; num++)
    {
        if ((k - num) % 2 != 0) continue;
        ll out_max = 0;
        if (num > 0)
            out_max = team[k-1+start];
        ll r = (k - num) / 2;
        for (int i = 0; i < r; i++)
            out_max = max(out_max, team[i+start] + team[k - num - i - 1 + start]);

        ans = min(ans, (r + num) * out_max);
    }
    cout << ans << endl;
}
