#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>
#include <iostream>

#define pb(a) push_back(a)

using namespace std;

const int MAXN = 100001;
const int MAXM = 100001;

int parent[20][MAXN];
int height[MAXN];

struct LCAA {

    int cnt;
    LCAA(int n) 
    {
        memset(parent, -1, sizeof(parent));
        memset(height, -1, sizeof(height));
        cnt = n;
    }

    LCAA(){}

    int moveNHigher(int a, int n)
    {
        int p = 0;
        while (n > 0)
        {
            if (n % 2)
                a = parent[p][a];
            n /= 2;
            p++;
        }
        return a;
    }

    void sameHeight(int& a, int& b)
    {
        if (height[a] < height[b])
            swap(a, b);
        int diff = height[a] - height[b];
        a = moveNHigher(a, diff);
    }

    int query(int a, int b)
    {
        if (height[a] != height[b])
            sameHeight(a, b);

        if (a == b)
            return a;
        
        int l = 0, r = MAXN + 1;
        while (r - l > 1)
        {
            int mid = (l + r) / 2;
            if (moveNHigher(a, mid) == moveNHigher(b, mid))
                r = mid;
            else l = mid;
        }
        return moveNHigher(a, r);
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
    bool redun;
    DoubleEdge(int a, int b, int c): u(a), v(b), cost(c) { redun = false; }
    DoubleEdge(){ redun = false; }

    bool operator < (const DoubleEdge& other) const
    {
        return cost < other.cost;
    }
};

vector<Edge> edges[MAXN];
multiset<DoubleEdge> edge_set;
vector<DoubleEdge> mst_ans;

bool marked[MAXN];

vector<DoubleEdge> edgeByWeight[10001];

void findMSTT(int N)
{
    //cerr << 3 << endl; // ------
    LCAA lca(N);
    //cerr << 4 << endl; // ------
    height[0] = 1;
    marked[0] = 1;
    for (int i = 0; i < edges[0].size(); i++)
        edge_set.insert(DoubleEdge(0, edges[0][i].v, edges[0][i].cost));

                for (int i = 0; i < N; i++)
                    cout << parent[0][i] << ' ';
                cout << endl;
    while (!edge_set.empty())
    {
        DoubleEdge e = *edge_set.begin();
        edge_set.erase(edge_set.begin());
        if (marked[e.v])
        {
            cerr << "failed trying of adding " << e.v << endl; // ------------------
            int new1 = e.v;
            int new2 = e.u;
            for (int i = 0; i < edgeByWeight[e.cost].size(); i++)
            {
                int old1 = edgeByWeight[e.cost][i].u;
                int old2 = edgeByWeight[e.cost][i].v;
                if ((old1 == new1 && old2 == new2) || (old1 == new2 && old2 == new1)) continue;
                int newLca = lca.query(new1, new2);
                int oldLca = lca.query(old1, old2);
                int newOld11 = lca.query(new1, old1);
                int newOld12 = lca.query(new1, old2);
                int newOld21 = lca.query(new2, old1);
                int newOld22 = lca.query(new2, old2);
                int appHeight = height[newLca];
                cerr << "new1: " << new1 << " , new2: " << new2 << " , old1: " << old1 << " , old2: " << old2 << endl;
                cerr << "newOld11: " << newOld11 << " , newOld12: " << newOld12 << " , newOld21: " << newOld21 << " , newOld22: " << newOld22 << endl;
                for (int i = 0; i < N; i++)
                    cout << parent[0][i] << ' ';
                cout << endl;
                if (
                    height[oldLca] <= appHeight && 
                    ((newOld11 == old1 && newOld12 == old2) || (newOld21 == old1 && newOld22 == old2))
                ) {
                    edgeByWeight[e.cost][i].redun = true;
                    cerr << "Here" << endl; //---------        
                }
            }
            continue;
        }
        cerr << "adding "<< e.v << endl; // -----------
        mst_ans.pb(e);
        marked[e.v] = 1;
        edgeByWeight[e.cost].pb(e);
        parent[0][e.v] = e.u;
        height[e.v] = height[e.u] + 1;
        for (int i = 1; i < 20; i++)
        {
            if (parent[i-1][parent[i-1][e.v]] != -1)
                parent[i][e.v] = parent[i-1][parent[i-1][e.v]];
            else break;
        }
        for (int i = 0; i < edges[e.v].size(); i++)
            edge_set.insert(DoubleEdge(e.v, edges[e.v][i].v, edges[e.v][i].cost));
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
    }
    //cerr << 1 << endl; // ------
    findMSTT(n);
    //cerr << 2 << endl; // --------


    int redun = 0;
    for (int c = 1; c <= 10000; c++)
        for (int i = 0; i < edgeByWeight[c].size(); i++)
            if (edgeByWeight[c][i].redun)
                redun++;
    cout << n-1-redun << endl;
}
