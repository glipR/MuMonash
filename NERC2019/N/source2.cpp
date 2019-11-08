#include <iostream>
#include <vector>
#include <map>
#include <cstring>

#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)

using namespace std;

map<int, int> NM;
map<int, int> RM;

int max_node = 0;

struct Edge {
    int v;
    int id;
    Edge () {}
    Edge(int a, int b) : v(a), id(b) {}
};

struct Triple {
    int a, b, c;
    Triple(int x, int y, int z) : a(x), b(y), c(z) {}
};

const int MAXN = 200100;

vector<Edge> list[MAXN];

bool mark[MAXN];

void reset()
{
    for (int i = 0; i < max_node; i++) list[i].clear();
    NM.clear();
    RM.clear();
    max_node = 0;
    memset(mark, false, sizeof(mark));
}

int mapping(int x)
{
    if (NM.find(x) == NM.end())
    {
        NM[x] = max_node++;
        RM[NM[x]] = x;
    }
    return NM[x];
}

Edge last;

void dfs(int node)
{
    mark[node] = 1;
    for (int i = 0; i < list[node].size(); i++)
    {
        int new_node = list[node][i].v;
        if (mark[new_node]) continue;
        last = list[node][i];
        dfs(new_node);
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        reset();
        for (int i = 0; i < n; i++)
        {
            int a, b;
            cin >> a >> b;
            a = mapping(a);
            b = mapping(b);

            list[a].pb(Edge(b, i+1));
            list[b].pb(Edge(a, i+1));
        }

        vector<Edge> ans;
        for (int i = 0; i < max_node; i++)
        {
            if (mark[i]) continue;
            dfs(i);
            ans.pb(last);
        }
       
        cout << ans.size() - 1 << endl;
        for (int i = 1; i < ans.size(); i++)
            cout << ans[i].id << ' ' << RM[ans[i].v] << ' ' << RM[0] << endl;
    }
}
