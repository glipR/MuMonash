#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>
#include <queue>

#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)

using namespace std;

typedef long long ll;
typedef vector<int> vi;

const int MAXN = 100010;

int max_node = 0; // Starting id for nodes, to map
map<int, int> NM; // node map from [1..1e9] -> [1..N]
map<int, int> RM; // reverse map from [1..N] -> [1..1e9]

vi list[MAXN];

map<pair<int, int>, int> edge_between;

struct Triple {
    int a, b, c;
    Triple(int x, int y, int z) : a(x), b(y), c(z) {}
};

struct Edge {
    int u, v;
    int id;
    Edge () {}
    Edge (int a, int b) : u(a), v(b) {
        id = edge_between[mp(a,b)];
    }
};

struct Component {
    int node;
    Edge removable;
    Component(){}
    Component(int NODE, Edge e) : node(NODE), removable(e) {}
};

vector<Component> components;
int node_component[MAXN];

void global_resets(int n)
{
    NM.clear();
    RM.clear();
    for (int i = 0; i < max_node; i++)
        list[i].clear();
    max_node = 0;
    components.clear();
    memset(node_component, -1, sizeof(node_component));
    edge_between.clear();
}

Edge dfs_c(int node, int prev, int id)
{
    node_component[node] = id;
    Edge ans;
    bool any = false;
    for (int i = 0; i < list[node].size(); i++)
    {
        int new_node = list[node][i];
        if (node_component[new_node] != -1) continue;
        ans = dfs_c(new_node, node, id);
        any = 1;
    }
    if (any) return ans;
    return Edge(node, prev);
}

vector<Triple> build_solution()
{
    vector<Triple> ans;
    for (int i = 0; i < components.size()-1; i++)
        ans.pb(Triple(components[i].removable.id, components[i].removable.u, components[components.size()-1].node));
    return ans;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;

        global_resets(n);

        for (int i = 0; i < n; i++)
        {
            int u, v;
            cin >> u >> v;
            if (NM.find(u) == NM.end())
            {
                NM[u] = max_node++;
                RM[NM[u]] = u;
            }
            if (NM.find(v) == NM.end())
            {
                NM[v] = max_node++;
                RM[NM[v]] = v;
            }

            u = NM[u]; v = NM[v];

            edge_between[mp(u, v)] = i;
            edge_between[mp(v, u)] = i;

            list[u].pb(v);
            list[v].pb(u);
        }

        for (int i = 0; i < max_node; i++)
            if (node_component[i] == -1)
                components.pb(Component(i, dfs_c(i, -1, components.size()-1)));

        if (components.size() == 1)
        {
            cout << 0 << endl;
            continue;
        }

        vector<Triple> ans = build_solution();

        cout << ans.size() << endl;
        for (auto e : ans)
            cout << e.a + 1 << ' ' << RM[e.b] << ' ' << RM[e.c] << endl;
    }
}
