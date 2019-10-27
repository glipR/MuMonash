#include <iostream>
#include <vector>
#include <cstring>

#define pb(a) push_back(a)

using namespace std;

typedef long long ll;
const int MAXN = 1e5 + 10;

struct Pair {
    int index;
    ll amount;
    Pair(){}
    Pair(int a, int b):index(a), amount(b) {}
};

int main()
{
    ll n, k, l, r;
    cin >> n >> l >> r >> k;
    ll x[MAXN];
    for (int i = 0; i < n; i++)
        cin >> x[i];

    vector<ll> ans;
    vector<Pair> changes;
    ll increases[MAXN];
    memset(increases, 0, sizeof(increases));
    ans.pb(l);
    changes.pb(Pair(0, 2000000000));
    
    ll increased_so_far = 0;

    for (int i = 1; i < n; i++)
    {
        if (x[i] > x[i-1])
        {
            ans.pb(ans[i-1]+1);
        }
        else if (x[i] == x[i-1])
            ans.pb(ans[i-1]);
         else 
         {
            changes.pb(Pair(i, k-1));
            ans.pb(ans[i-1] - k);
            if (ans[i] + increased_so_far < l)
            {
                ll needed = l - ans[i] - increased_so_far;
                increased_so_far += needed;
                ll size = changes.size();
                for (int i = size - 1; i >= 0; i--)
                {
                    ll amount = min(needed, changes[i].amount);
                    changes[i].amount -= amount;
                    needed -= amount;
                    increases[changes[i].index] += amount;
                    if (changes[i].amount == 0)
                        changes.pop_back();
                    else break;
                }
            }
         }
    }

    ll sum = 0;
    for (int i = 0; i < ans.size(); i++)
    {
        sum += increases[i];
        ans[i] += sum;
    }


    for (int i = 0; i < n; i++)
        if (ans[i] < l || ans[i] > r || (i > 0 && abs(ans[i]-ans[i-1]) > k) 
        || (i > 0 && ((x[i-1] > x[i] && ans[i-1] <= ans[i]) || (x[i-1] == x[i] && ans[i-1] != ans[i]) || (x[i-1] < x[i] && ans[i-1] >= ans[i]))))
        {
            cout << -1 << endl;
            return 0;
        }

    for (int i = 0; i < n; i++)
        cout << ans[i] << ' ';
    cout << endl;
}
