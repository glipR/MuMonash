#include <numeric>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <queue>
#include <math.h>

#define mp(a, b) make_pair(a,b)
#define pb(a) push_back(a)

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef pair<int, int> pii;

double euclidean(double dx, double dy) {
    return sqrt(dx*dx + dy*dy);
}

/*template <typename F, typename C> struct MinCostFlow {
    struct edge { int from, to; F flow, cap; C cost; };
    const C INF = numeric_limits<C>::max(); vector<C> pi, dist;
    int n, m; vi pred, pe; vvi g; vector<edge> edges;
    typedef pair<C, int> pci; priority_queue<pci, vector<pci>
}*/

struct Edge {
    int dist;
    int s, t;
    int cap;
    Edge () {cap = 1;}
    void set_dist(double d)
    {
        dist = (int)(ceil(d));
    }
};

const int MAXN = 1010;
int n;
Edge edges[MAXN][MAXN];
int edge_changes[MAXN][MAXN];

int parent[MAXN];

bool find_path(int dist)
{
    vector<int> neis[MAXN];
    for (int i = 0; i < n + 2; i++)
        for (int j = i + 1; j < n + 2; j++)
            if (edges[i][j].dist <= dist)
            {
                neis[i].pb(j);
                neis[j].pb(i);

                edges[i][j].cap += edge_changes[i][j];
                edges[j][i].cap += edge_changes[j][i];

                edge_changes[i][j] = 0;
                edge_changes[j][i] = 0;
            }
   
    for (int i = 0; i < 4; i++)
    {
        fill(parent, parent + n + 2, -1);
        queue<int> q;
        q.push(n);
        parent[n] = -2;
        
        bool found = 0;

        while (!q.empty() && !found)
        {
            int front = q.front();
            q.pop();
            for (auto nei : neis[front])
            {
                if (edges[front][nei].cap > 0 && parent[nei] == -1)
                {
                    q.push(nei);
                    parent[nei] = front;
                    if (nei == n+1)
                        found = true;
                }
                if (found) break;
            }
        }
        
        if (!found)
            return false;

        int current = n + 1;
        while (parent[current] >= 0)
        {
            edges[parent[current]][current].cap--;
            edges[current][parent[current]].cap++;

            edge_changes[parent[current]][current]++;
            edge_changes[current][parent[current]]--;

            current = parent[current];
        }
    }
    return true;
}

int main() {

    vector<pii > stones;

    int lake, island;
    cin >> lake >> island >> n;

    for (int i = 0; i < n; i++) {
        int sx, sy;
        cin >> sx >> sy;
        stones.push_back(mp(sx, sy));
    }

    // Vertices are 0-(n-1) for stones, n for island, and n+1 for outside island.
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            double dist = euclidean(stones[i].first - stones[j].first, stones[i].second - stones[j].second) - 2;
            edges[i][j].set_dist(dist);
            edges[j][i].set_dist(dist);
        }
        // Island
        double idist = euclidean(stones[i].first, stones[i].second) - 1 - island;
        edges[i][n].set_dist(idist);
        edges[n][i].set_dist(idist);
        // Lake
        double ldist = lake - euclidean(stones[i].first, stones[i].second) - 1;
        edges[i][n+1].set_dist(ldist);
        edges[n+1][i].set_dist(ldist);
    }

    edges[n][n+1].set_dist(lake - island);
    edges[n+1][n].set_dist(lake - island);
    edges[n][n+1].cap = 1000;
    edges[n+1][n].cap = 1000;

    int l = 0, r = 1000000001;
    while (r - l > 1)
    {
        int mid = (l + r) / 2;
        if (find_path(mid))
            r = mid;
        else l = mid;
    }

    cout << r << endl;

    return 0;
}
