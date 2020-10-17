#include <numeric>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <queue>
#include <complex>

using namespace std;

const double EPS = 1e-9;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> pii;
typedef pair<pii, pii> web;
typedef pair<pii, pii> rat_point;

map<rat_point, vector<bool> > connected;
map<rat_point, int > p_index;
int INDEX_COUNT = 0;

#define cpt const Pt&

int n;

ll gcd(ll a, ll b) {
    if (b == 0) { return ( a < 0) ? -a : a; }
    else { ll g = gcd(b, a%b); return g; }
}

void add_web(rat_point point, int index) {
    if (connected.count(point) == 0) {
        connected[point] = vector<bool>(n);
        p_index[point] = INDEX_COUNT++;
    }
    connected[point][index] = true;
}

ll det(pii p1, pii p2) {
    // (conj(a) * b).y
    // a.x * b.y + -a.y * b.x
    return p1.first * p2.second - p1.second * p2.first;
}

bool line_intersect(pii a, pii b, pii p, pii q, int ab_index, int pq_index) {
    pii ab = {b.first - a.first, b.second - a.second};
    pii qp = {p.first - q.first, p.second - q.second};
    pii ap = {p.first - a.first, p.second - a.second};
    ll s1=det(ap, qp);
    ll s2=det(ab, qp);
    ll t1=det(ab, ap);
    ll t2=det(ab, qp);
    if ((s2 == 0) || (t2 == 0)) {
        // Parallel. Check that they intersect or not.
        if (ab.first != 0) {
            if (
                ((min(a.first, b.first) <= p.first) && (max(a.first, b.first) >= p.first))
            ) {
                rat_point x = {{p.first, (ll)1}, {p.second, (ll)1}};
                add_web(x, ab_index);
                return true;
            } else if (
                ((min(a.first, b.first) <= q.first) && (max(a.first, b.first) >= q.first))
            ) {
                rat_point x = {{q.first, (ll)1}, {q.second, (ll)1}};
                add_web(x, ab_index);
                return true;
            }
        } else {
            if (
                ((min(a.second, b.second) <= p.second) && (max(a.second, b.second) >= p.second))
            ) {
                rat_point x = {{p.first, (ll)1}, {p.second, (ll)1}};
                add_web(x, ab_index);
                return true;
            } else if (
                ((min(a.second, b.second) <= q.second) && (max(a.second, b.second) >= q.second))
            ) {
                rat_point x = {{q.first, (ll)1}, {q.second, (ll)1}};
                add_web(x, ab_index);
                return true;
            } else {
                return false;
            }
        }
    }
    if (-EPS < s1 / s2 && s1 / s2 < 1 + EPS) {
        if (-EPS < t1 / t2 && t1 / t2 < 1 + EPS) {
            rat_point x = {{a.first * s2 + s1 * ab.first, s2}, {a.second * s2 + s1 * ab.second, s2}};
            ll gcd1 = gcd(x.first.first, x.first.second);
            ll gcd2 = gcd(x.second.first, x.second.second);
            x = {
                {x.first.first / gcd1, x.first.second / gcd1},
                {x.second.first / gcd1, x.second.second / gcd2}
            };
            add_web(x, ab_index);
            add_web(x, pq_index);
            return true;
        }
    }
    return false;
}

int main() {

    connected.clear();

    int w, d;
    cin >> w >> d >> n;
    vector<web> webs(n);
    for (int i=0; i<n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        webs[i] = {{x1, y1}, {x2, y2}};
    }

    // First, add simple points.
    for (int i=0; i<n; i++) {
        if ((webs[i].first.first == 0) || (webs[i].first.first == w)) {
            rat_point point = {{webs[i].first.first, 1}, {0, 1}};
            add_web(point, i);
        } else {
            rat_point point = {{webs[i].first.first, 1}, {webs[i].first.second, 1}};
            add_web(point, i);
        }
        if ((webs[i].second.first == 0) || (webs[i].second.first == w)) {
            rat_point point = {{webs[i].second.first, 1}, {0, 1}};
            add_web(point, i);
        } else {
            rat_point point = {{webs[i].second.first, 1}, {webs[i].second.second, 1}};
            add_web(point, i);
        }
    }

    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            line_intersect(webs[i].first, webs[i].second, webs[j].first, webs[j].second, i, j);
        }
    }

    vvi adj = vvi(INDEX_COUNT);

    // Now, every interesting point has been noted. Generate an edge between two points if they share an edge touching.
    for (int i=0; i<n; i++) {
        vector<int> points = vector<int>();
        for (auto v : connected) {
            if (v.second[i]) points.push_back(p_index[v.first]);
        }
        for (int i=0; i<points.size(); i++) {
            for (int j=i+1; j<points.size(); j++) {
                adj[points[i]].push_back(points[j]);
                adj[points[j]].push_back(points[i]);
            }
        }
    }
    
    for (auto v: connected) {
        cerr << "Point " << v.first.first.first << "/" << v.first.first.second << ", " << v.first.second.first << "/" << v.first.second.second << ". Index " << p_index[v.first] << endl;
        cerr << "Neighbours:" << endl;
        for (auto i: adj[p_index[v.first]]) {
            cerr << i << " ";
        }
        cerr << endl;
    }

    // Now we have our edges. Whether 2 flow from left to right is possible.


    return 0;
}