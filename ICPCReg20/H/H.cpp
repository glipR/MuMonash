#include <numeric>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vii;

double euclidean(double dx, double dy) {
    return sqrt(dx*dx + dy*dy);
}

template <typename F, typename C> struct MinCostFlow {
    struct edge { int from, to; F flow, cap; C cost; };
    const C INF = numeric_limits<C>::max(); vector<C> pi, dist;
    int n, m; vi pred, pe; vvi g; vector<edge> edges;
}

int main() {

    vector<pair<double, double> > stones;
    stones.clear();

    double lake, island;
    int n;
    cin >> lake >> island >> n;

    for (int i=0; i<n; i++) {
        double sx, sy;
        stones.push_back({sx, sy});
    }

    vector<pair<double, pair<int, int> > > edges;

    // Vertices are 0-(n-1) for stones, n for island, and n+1 for outside island.
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            double dist = euclidean(stones[i].first - stones[j].first, stones[i].second - stones[j].second) - 2;
            edges.push_back({dist, {i, j}});
        }
        // Island
        double idist = euclidean(stones[i].first, stones[i].second) - 1 - island;
        edges.push_back({idist, {i, n}});
        // Lake
        double ldist = lake - euclidean(stones[i].first, stones[i].second) - 1;
        edges.push_back({ldist, {i, n+1}});
    }



    return 0;
}