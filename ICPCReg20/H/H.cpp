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
    return floor(sqrt(x));
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

const int MAXN = 2010;
const int MAXW = 1000000010;

struct Edge {
    ll dist;
    ll cap;
    Edge () {cap = 1; dist = MAXW; }
};

int n;
Edge edges[MAXN][MAXN];
int edge_changes[MAXN][MAXN];

int parent[MAXN];

int O;

bool find_path(int dist)
{
    vector<int> neis[MAXN];
    for (int i = 0; i < 2*n + 2; i++)
        for (int j = 0; j < 2*n + 2; j++)
            if (edges[i][j].dist <= dist)
            {
                neis[i].pb(j);

                edges[i][j].cap += edge_changes[i][j];

                edge_changes[i][j] = 0;
            }
   
    for (int i = 0; i < 4; i++)
    {
        fill(parent, parent + 2*n + 2, -1);
        queue<int> q;
        q.push(n);
        parent[n] = -2;
        
        bool found = 0;

        while (!q.empty() && !found)
        {
            int front = q.front();
            q.pop();
            // if (dist == 4) cerr << front << " added: ";
            for (auto nei : neis[front])
            {
                if (edges[front][nei].cap > 0 && parent[nei] == -1)
                {
                    q.push(nei);
                    // cerr << nei << ", ";
                    parent[nei] = front;
                    if (nei == n+1)
                        found = true;
                }
                if (found) break;
            }
 //           cerr << endl;
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

    vector<pair<ll, ll> > stones;

    ll lake, island;
    cin >> lake >> island >> n;
    O = n + 2;

    for (int i = 0; i < n; i++) {
        ll sx, sy;
        cin >> sx >> sy;
        stones.push_back(mp(sx, sy));
    }

    // Vertices are 0-(n-1) for stones, n for island, and n+1 for outside island.
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            ll dist = euclidean(stones[i].first - stones[j].first, stones[i].second - stones[j].second, 0) - 2;
            edges[i + O][j].dist = dist;
            edges[j][i + O].dist = dist; edges[j][i + O].cap = 0;
            edges[j + O][i].dist = dist;
            edges[i][j + O].dist = dist; edges[i][j + O].cap = 0;
        }

        // Island
        ll idist = euclidean(stones[i].first, stones[i].second, 0) - 1 - island;
        edges[n][i].dist = idist;
        edges[n][i + O].dist = idist; edges[n][i + O].cap = 0;
        edges[i][n].dist = idist; edges[i][n].cap = 0;
        edges[i + O][n].dist = idist; edges[i + O][n].cap = 0;

        // Lake
        ll ldist = lake - euclidean(stones[i].first, stones[i].second, 1) - 1;
        edges[i + O][n+1].dist = ldist;
        edges[i][n + 1].dist = MAXW;
        edges[n+1][i].dist = MAXW;
        edges[n+1][i + O].dist = MAXW;
    }

    edges[n][n+1].dist = MAXW;
    edges[n+1][n].dist = MAXW;
    edges[n][n+1].cap = 0;
    edges[n+1][n].cap = 0;

    for (int i = 0; i < n; i++)
    {
        edges[i][i + O].dist = 0;
        edges[i][i + O].cap = 1;
        edges[i + O][i].dist = 0;
        edges[i + O][i].cap = 0;
    }

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
