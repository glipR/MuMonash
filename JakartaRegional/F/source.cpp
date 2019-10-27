#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <cstring>

#define pb(a) push_back(a)

using namespace std;

struct Pair {
    int a;
    int b;
    Pair(){}
    Pair(int x, int y) 
    {
        if (x > y)
            swap(x, y);
        a = x;
        b = y;
    }
    bool operator < (const Pair& other) const
    {
        if (a == other.a)
            return b < other.b;
        return a < other.a;
    }
    bool operator == (const Pair& other) const
    {
        return (a == other.a && b == other.b) || (a == other.b && b == other.a);
    }
};

map<Pair, int> edge_type;

const int MAXN = 1e5  + 10;

int node_cnt[MAXN];

int root;

vector<int> edges[MAXN];

bool mark[MAXN];

void count_nodes(int node)
{
    mark[node] = 1;
    node_cnt[node] = 1;
    for (int i = 0; i < edges[node].size(); i++)
    {
        int new_node = edges[node][i];
        if (mark[new_node]) continue;
        count_nodes(new_node);
        node_cnt[node] += node_cnt[new_node];
    }
}

void fill_edge_types(int node, int target)
{
    edge_type.clear();
    memset(mark, false, sizeof(mark));
    mark[node] = 1;
    mark[target] = 1;
    queue<int> q;
    q.push(node);
    while (!q.empty())
    {
        int front = q.front();
        q.pop();
        for (int i = 0; i < edges[front].size(); i++)
        {
            int new_node = edges[front][i];
            if (mark[new_node]) continue;
            mark[new_node] = 1;
            q.push(new_node);
            int deg1 = edges[front].size();
            int deg2 = edges[new_node].size();
            if (front == node) deg1--;
            edge_type[Pair(deg1, deg2)]++;
        }
    }
}

bool is_good_node(int node)
{
    if (edges[node].size() == 1) return false;
    int wanted_cnt = node_cnt[root] - node_cnt[node];
    for (int i = 0; i < edges[node].size(); i++)
    {
        if (node_cnt[edges[node][i]] > node_cnt[node]) continue;
        if (node_cnt[edges[node][i]] != wanted_cnt) return false;
    }

    fill_edge_types(edges[node][0], node);
    map<Pair, int> backup(edge_type);

    for (int i = 0; i < edges[node].size(); i++)
    {
        fill_edge_types(edges[node][i], node);
        if (backup != edge_type)
            return false;
    }
    return true;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n-1; i++)
    {
        int x, y;
        cin >> x >> y;
        x--; y--;
        edges[x].pb(y);
        edges[y].pb(x);
    }

    for (int i = 0; i < n; i++)
        if (edges[i].size() == 1)
            root = i;

    count_nodes(root);
    int good_node = -1;
    for (int i = 0; i < n; i++)
        if (is_good_node(i))
            good_node = i;
    
    if (good_node == -1)
        cout << -1 << endl;
    else cout << edges[good_node].size() << endl;

}
