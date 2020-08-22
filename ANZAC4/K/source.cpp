#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

vector<ll> ans;
vector<pair<int, int> > nei[20000];
int n;

pii pairs[2600];

inline pii P(int index)
{
    return pairs[index - 2];
}

inline ll A(int index)
{
    return ans[index - n - 2];
}

map<ll, int> _A;
map<pair<int, int>, int> R;

bool mark[20000];

bool find_path(int node)
{
    if (node == 1) return true;
    bool res = 0;
    for (int i = 0; i < nei[node].size(); i++)
    {
        if (nei[node][i].second == 0)
            continue;
        nei[node][i].second = 0;
        if (find_path(nei[node][i].first))
        {
            nei[nei[node][i].first][R[mp(node, i)]].second = 1;
            return true;
        }
        nei[node][i].second = 1;
    }
    return false;
}

int main()
{
    // 0: source, 1: target, [2..N+1]: pairs, [N+2..]: answers.
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        ll a, b; cin >> a >> b;
        pairs[i] = mp(a,b);
        if (_A.find(a-b) == _A.end())
        {
            ans.pb(a-b);
            _A[a-b] = ans.size() - 1;
            nei[_A[a-b] + n + 2].pb(mp(0, 0));
            nei[0].pb(mp(_A[a-b] + n + 2, 1));
            R[mp(_A[a-b] + n + 2, nei[_A[a-b] + n + 2].size()-1)] = nei[0].size() - 1;
            R[mp(0, nei[0].size() - 1)] = nei[_A[a-b] + n + 2].size() - 1;
        }
        if (_A.find(a+b) == _A.end())
        {
            ans.pb(a+b);
            _A[a+b] = ans.size() - 1;
            nei[_A[a+b] + n + 2].pb(mp(0, 0));
            nei[0].pb(mp(_A[a+b] + n + 2, 1));
            R[mp(_A[a+b] + n + 2, nei[_A[a+b] + n + 2].size()-1)] = nei[0].size() - 1;
            R[mp(0, nei[0].size() - 1)] = nei[_A[a+b] + n + 2].size() - 1;
        }
        if (_A.find(a*b) == _A.end())
        {
            ans.pb(a*b);
            _A[a*b] = ans.size() - 1;
            nei[_A[a*b] + n + 2].pb(mp(0, 0));
            nei[0].pb(mp(_A[a*b] + n + 2, 1));
            R[mp(_A[a*b] + n + 2, nei[_A[a*b] + n + 2].size()-1)] = nei[0].size() - 1;
            R[mp(0, nei[0].size() - 1)] = nei[_A[a*b] + n + 2].size() - 1;
        }
        
        nei[_A[a-b] + n + 2].pb(mp(i+2, 1));
        nei[i+2].pb(mp(_A[a-b] + n + 2, 0));
        R[mp(_A[a-b] + n + 2, nei[_A[a-b] + n + 2].size()-1)] = nei[i+2].size() - 1;
        R[mp(i + 2, nei[i+2].size()-1)] = nei[_A[a-b] + n + 2].size() - 1;

        nei[_A[a+b] + n + 2].pb(mp(i+2, 1));
        nei[i+2].pb(mp(_A[a+b] + n + 2, 0));
        R[mp(_A[a+b] + n + 2, nei[_A[a+b] + n + 2].size()-1)] = nei[i+2].size() - 1;
        R[mp(i + 2, nei[i+2].size()-1)] = nei[_A[a+b] + n + 2].size() - 1;

        nei[_A[a*b] + n + 2].pb(mp(i+2, 1));
        nei[i+2].pb(mp(_A[a*b] + n + 2, 0));
        R[mp(_A[a*b] + n + 2, nei[_A[a*b] + n + 2].size()-1)] = nei[i+2].size() - 1;
        R[mp(i + 2, nei[i+2].size()-1)] = nei[_A[a*b] + n + 2].size() - 1;

        nei[1].pb(mp(i+2, 0));
        nei[i+2].pb(mp(1, 1));
        R[mp(1, nei[1].size() - 1)] = nei[i+2].size() - 1;
        R[mp(i+2, nei[i+2].size() - 1)] = nei[1].size() - 1;
    }

    int cnt = 0;
    while (find_path(0))
        cnt++;
    
    if (cnt < n)
    {
        cout << "impossible" << endl;
        return 0;
    }

    for (int i = 2; i <= n + 1; i++)
    {
        int connection = -1;
        for (int j = 0; j < nei[i].size() && connection == -1; j++)
            if (nei[i][j].second == 1 && nei[i][j].first != 1)
                connection = j;
        ll ans = A(nei[i][connection].first);
        ll a = pairs[i-2].first;
        ll b = pairs[i-2].second;
        cout << a << ' ';
        if (ans == a - b) cout << '-';
        else if (ans == a + b) cout << '+';
        else if (ans == a * b) cout << '*';
        cout << ' ' << b << " = " << ans << endl;
    }
}
