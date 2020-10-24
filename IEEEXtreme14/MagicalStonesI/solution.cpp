#include <iostream>
#include <vector>
#include <queue>

#define pb(a) push_back(a)

using namespace std;

const int MAXN = 100001;

int incoming[MAXN], outgoing[MAXN];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x; cin >> x;
        outgoing[i] = x - 1;
        incoming[x-1]++;
    }
    
    vector<int> obtainables;
    obtainables.pb(n);
    
    queue<int> zeros;
    for (int i = 0; i < n; i++)
        if (incoming[i] == 0)
            zeros.push(i);
    
    int remain = n;
    while (1)
    {
        int cnt = zeros.size();
        if (cnt == 0)
            break;
        remain -= cnt;
        obtainables.pb(remain);
        for (int i = 0; i < cnt; i++)
        {
            int f = zeros.front();
            zeros.pop();
            if (--incoming[outgoing[f]] == 0)
                zeros.push(outgoing[f]);
        }
    }
    
    int ans[MAXN];
    fill(ans, ans + MAXN, -1);
    for (int i = 0; i < obtainables.size(); i++)
        ans[obtainables[i]] = i;
    
    int q; cin >> q;
    for (int i = 0; i < q; i++)
    {
        int x; cin >> x;
        cout << ans[x] << endl;
    }
    
    return 0;
}
