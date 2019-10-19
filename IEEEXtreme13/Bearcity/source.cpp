#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>

#define pb(a) push_back(a)

using namespace std;

const int MAXN = 100001;
const int MAXM = 100001;

struct UnionFind {
    int root[MAXN];
    int color[MAXN];
    int size[MAXN];

    int nodes;

    UnionFind(int a) 
    {
        memset(root, -1, sizeof(root));
        memset(size, 1, sizeof(size));
        nodes = a;
        for (int i = 0; i < nodes; i++)
            color[i] = i;
    }

    int findRoot(int a)
    {
        int tmp = a;
        while (root[a] != -1)
            a = root[a];
        while (root[tmp] != -1)
        {
            tmp = root[tmp];
            root[tmp] = a;
        }
        return a;
    }

    void join(int a, int b)
    {
        int rootA = findRoot(a);
        int rootB = findRoot(b);
        if (rootA == rootB) return;
        if (size(rootA) > size(rootB))
            swap(rootA, rootB);
        root[rootA] = rootB;
    }

    int color(int a)
    {
        return color[findRoot(a)];
    }
};

struct Edge {
    int v;
    int cost;
    Edge(int a, int c)
    {
        v = a;
        cost = c;
    }
    Edge(){}

    bool operator < (const Edge& other) const
    {
        return cost < other.cost;
    }
};

struct DoubleEdge {
    int u; int v; int cost;
    DoubleEdge(int a, int b, int c): u(a), v(b), cost(c) {}
    DoubleEdge(){}

    bool operator < (const Edge& other) const
    {
        return cost < other.cost;
    }
};

vector<Edge> edges[MAXN];
multiset<Edge> edge_set;
vector<DoubleEdge> mst_ans;

void findMST(int n)
{
    UnionFind uni = UnionFind(n);
    while (!edge_set.empty())
    {
        DoubleEdge e = *edge_set.begin();
        edge_set.erase(edge_set.begin());
        if (uni.color(e.u) == uni.color(e.v))
            continue;
        mst_ans.pb(e);
        uni.join(e.u, e.v);
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int x, y, c;
        cin >> x >> y >> c;
        x--; y--;
        edges[x].pb(Edge(y, c));
        edges[y].pb(Edge(x, c));
        edge_set.insert(DoubleEdge(x, y, c));
    }

    findMST(n);
}
