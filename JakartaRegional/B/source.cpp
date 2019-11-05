#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>

#define pb(a) push_back(a)

using namespace std;

typedef vector<int> vi;
typedef long long ll;

const int MAXN = 1e5 + 10;
const ll MOD = 1e9 + 7;

const int debug = 0;

ll powerr(ll a, ll b)
{
    if (b == 1)
        return a;
    if (b == 0)
        return 1;
    ll res = powerr(a, b / 2);
    if (b % 2)
        return (((res * a) % MOD) * res) % MOD;
    return (res * res) % MOD;
}

ll modular_inverse(ll x)
{
    return powerr(x, MOD-2);
}

ll dp[MAXN][3];

vi ordered_nodes;
vi list[MAXN];
int par[MAXN];

void bfs_order(int node)
{
    bool mark[MAXN];
    memset(mark, false, sizeof(mark));

    mark[node] = 1;
    ordered_nodes.pb(node);
    par[node] = -1;

    queue<int> q;
    q.push(node);

    while (!q.empty())
    {
        int front = q.front(); q.pop();
        for (auto new_node : list[front])
        {
            if (mark[new_node]) continue;
            mark[new_node] = 1;
            ordered_nodes.pb(new_node);
            q.push(new_node);
            par[new_node] = front;
        }
    }
}

inline ll mul(ll a, ll b)
{
    return ( (a % MOD) * (b % MOD) ) % MOD;
}

inline ll sum(ll a, ll b)
{
    return (a + b) % MOD;
}

ll sub(ll a, ll b)
{
    a -= b;
    if (a < 0)
        a += MOD;
    return a;
}

ll compute_f0(int node)
{
    if ((list[node].size() == 1 && par[node] != -1) || (list[node].size() == 0))
        return 1;
    ll res1 = 1;
    ll res2 = 0;
    ll all2 = 1;

    int zero = -1;

    for (auto child:list[node])
    {
        if (child == par[node]) continue;
        res1 = mul(res1, dp[child][1]);
        if (dp[child][2] == 0)
        {
            if (zero == -1) zero = child;
            else zero = -2;
        }
        else
            all2 = mul(all2, dp[child][2]);
    }
    if (zero == -1)
    {
        for (auto child:list[node])
        {
            if (child == par[node]) continue;

                res2 = sum(res2, 
                    mul(
                        mul(all2, modular_inverse(dp[child][2])),
                        dp[child][0]
                    )
                );
        }
    }
    else if (zero != -2)
    {
        res2 = mul(all2, dp[zero][0]);
    }
    
    return (res1 + res2) % MOD;
}

ll compute_f1(int node)
{
    if ((par[node] != -1 && list[node].size() < 3) || (list[node].size() < 2))
        return 0;
    ll p[MAXN];
    ll all2 = 1;

    int zero1 = -1;
    int zero2 = -1;
    int totalZs = 0;

    for (auto child:list[node])
    {
        if (child == par[node]) continue;
        if (dp[child][2] == 0)
        {
            totalZs++;
            if (zero1 == -1)
                zero1 = child;
            else zero2 = child;
        }
        else
            all2 = mul(all2, dp[child][2]);
    }

    if (totalZs > 2) return 0;
    if (totalZs == 2)
    {
        return mul(dp[zero1][0], mul(dp[zero2][0], all2));
    }
    if (totalZs == 1)
    {
        ll newRes = 0;
        for (auto child:list[node])
        {
            if (child == par[node] || child == zero1) continue;
            newRes = sum(newRes, mul(dp[zero1][0], mul(dp[child][0], mul(all2, modular_inverse(dp[child][2])))));
        }
        return newRes;
    }

    for (int i = 0; i < list[node].size(); i++)
    {
        int child = list[node][i];
        if (child == par[node])
        {
            p[i] = 0;
            continue;
        }
        p[i] = mul(mul(all2, modular_inverse(dp[child][2])), dp[child][0]);
    }

    ll partial[MAXN];
    partial[0] = p[0];
    for (int i = 1; i < list[node].size(); i++)
        partial[i] = sum(partial[i-1], p[i]);

    ll res = 0;
    for (int i = 0; i < list[node].size(); i++)
    {
        int left = list[node][i];
        if (par[node] == left) continue;
        res = sum(res, mul(
            dp[left][0], mul(sub(partial[list[node].size()-1], partial[i]), modular_inverse(dp[left][2]))
        ));
    }

    return res;
}

ll compute_f2(int node)
{
    if ((list[node].size() == 1 && par[node] != -1) || (list[node].size() == 0))
        return 1;
    ll res1 = 1;
    ll all1 = 1;

    int zero = -1;

    for (auto child:list[node])
    {
        if (child == par[node]) continue;
        res1 = mul(res1, dp[child][1]);
        if (dp[child][1] == 0)
        {
            if (zero == -1) zero = child;
            else zero = -2;
        }
        else
            all1 = mul(all1, dp[child][1]);
    }

    ll res2 = 0;
    if (zero == -1)
    {
        for (auto child:list[node])
        {
            if (zero == -2)
                break;
            if (zero != -1 && zero != child)
                continue;
            if (child == par[node]) continue;

                res2 = sum(res2, 
                    mul(
                        mul(all1, modular_inverse(dp[child][1])),
                        dp[child][0]
                    )
                );
        }
    }
    else if (zero != -2)
    {
        res2 = mul(all1, dp[zero][0]);
    }

    return sum(sum(res1, res2), compute_f1(node));
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n-1; i++)
    {
        int u, v;
        cin >> u >> v;
        u--; v--;
        list[u].pb(v);
        list[v].pb(u);
    }

    bfs_order(0);
    reverse(ordered_nodes.begin(), ordered_nodes.end());

    for (int i = 0; i < ordered_nodes.size(); i++)
    {
        int node = ordered_nodes[i];
        dp[node][0] = compute_f0(node);
        dp[node][1] = compute_f1(node);
        dp[node][2] = compute_f2(node);
    }

    while (debug)
    {
        int a, b;
        cin >> a >> b;
        a--;
        cout << dp[a][b] << endl;
    }

    cout << dp[0][2] << endl;
    
}
