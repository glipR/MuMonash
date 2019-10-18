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

struct Change {
    int current;
    ll cost;

    Change(int c, ll co) { current = c; cost = co; }

    bool const operator < (const Change &other) const {
        if (current != other.current)
            return current > other.current;

        if (current == 1)
            return cost > other.cost;
        return cost < other.cost;
    }
};

int main()
{
    int n;
    cin >> n;
    ll cost[10001];
    for (int i = 0; i < n; i++)
        cin >> cost[i];

    string a;
    cin >> a;

    vector<Change> changes;

    for (int i = 0; i < n; i++)
    {
        char c;
        cin >> c;
        if (c != a[i])
            changes.pb(Change(a[i]-'0', cost[i]));
    }
    sort(changes.begin(), changes.end());

    ll ans = 0;
    ll current = 0;
    for (int i = 0; i < n; i++)
        if (a[i] == '1')
            current += cost[i];

    for (int i = 0; i < changes.size(); i++)
    {
        //cerr << "current change is " << changes[i].current << " , " << changes[i].cost << endl;
        if (changes[i].current == 1)
            current -= changes[i].cost;
        else current += changes[i].cost;
        ans += current;
    }
    cout << ans << endl;
}
