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
#include <cmath>

#define mp(a, b) make_pair(a,b)
#define pb(a) push_back(a)

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef pair<int, int> pii;

void RUNTIME()
{
    int A = 10;
    int B = A / 2;
    cout << 1 / (A - B - B);
}

ll floorSqrt(ll x)  
{     
    if (x == 0 || x == 1)  
       return x; 
  
    ll l = 1, r = x, ans;    
    while (l <= r)  
    {         
        ll mid = (l + r) / 2; 
        
        if (mid*mid == x) 
            return mid; 
  
        if (mid*mid < x)  
        { 
            l = mid + 1; 
            ans = mid; 
        }  
        else r = mid-1;         
    } 
    return ans; 
}

ll euclidean(ll dx, ll dy, bool reverse) {
    ll t = dx * dx + dy * dy;

    if (reverse) return floorSqrt(t);
    ll d = floorSqrt(t);
    if (d * d == t)
        return d;
    return d + 1;
}

struct Edge {
    ll dist;
    int s, t;
    int cap;
    Edge () {cap = 1;}
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

                edges[i][j].cap = (i + j == 2*n + 1) ? 10 : 1; //edge_changes[i][j];
                edges[j][i].cap = edges[i][j].cap; //edge_changes[j][i];

                // edge_changes[i][j] = 0;
                // edge_changes[j][i] = 0;
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

            // edge_changes[parent[current]][current]++;
            // edge_changes[current][parent[current]]--;

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
            ll dist = euclidean(stones[i].first - stones[j].first, stones[i].second - stones[j].second, 0) - 2;
            //if (dist < 0)
                //RUNTIME();
            edges[i][j].dist = dist;
            edges[j][i].dist = dist;
            // edges[i][j].set_dist(dist);
            // edges[j][i].set_dist(dist);
        }
        // Island
        ll idist = euclidean(stones[i].first, stones[i].second, 0) - 1 - island;
        //if (idist < 0)
            //RUNTIME();
        edges[i][n].dist = idist;
        edges[n][i].dist = idist;

        // Lake
        ll ldist = lake - euclidean(stones[i].first, stones[i].second, 1) - 1;
        if (ldist < 0)
            RUNTIME();
        edges[i][n+1].dist = ldist;
        edges[n+1][i].dist = ldist;
    }

    edges[n][n+1].dist = lake - island;
    edges[n+1][n].dist = lake - island;
    edges[n][n+1].cap = 10;
    edges[n+1][n].cap = 10;

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
