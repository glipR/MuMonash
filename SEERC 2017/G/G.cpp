#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

double distance(vector<pll> v)
{
    double res = 0;
    ll speed = 0;
    for (int i = 0; i < v.size(); i++)
    {
        ll next_speed = speed + (v[i].first * v[i].second);
        res += ((speed + next_speed) / 2) * v[i].second;
        speed = next_speed;
    }
    return res;
}

int main()
{
    int n;
    cin >> n;

    vector<pll> v;

    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        v.pb(mp(a,b));
    }

    double def = distance(v);
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    double now = distance(v);

    printf("%0.1f\n", now-def);
}
