#include <algorithm>
#include <iostream>
#include <vector>

#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3

#define X first
#define Y second

using namespace std;

typedef long long ll;

template<typename T, typename U> struct SegmentTree {
    int S, H;

    T z;
    vector<T> v; // Actual values (May not be up to date)

    U noop; // No Operation constant
    vector<bool> d; // Dirty array (What needs updating)
    vector<U> p; // Lazy propogated updates.

    SegmentTree<T, U>(int _S, T _z = T(), U _noop = U()) {
        z = _z, noop = _noop;
        for (S = 1, H = 1; S < _S; ) S *= 2, H++;
        v.resize(2*S, z);
        d.resize(2*S, false);
        p.resize(2*S, noop);
    }

    void set_leaves(vector<T> &l) {
        copy(l.begin(), l.end(), v.begin() + S);
        for (int i = S - 1; i > 0; i--)
            v[i] = v[2 * i] + v[2 * i + 1];
    }

    void apply(int i, U &up) {
        v[i] = up(v[i]);
        if(i < S) {
            p[i] = p[i] + up;
            d[i] = true;
        }
    }

    void rebuild(int i) {
        for (int l = i/2; l; l /= 2) {
            T c = v[2*l] + v[2*l+1];
            v[l] = p[l](c);
        }
    }

    void prop(int i) {
        for (int h = H; h > 0; h--) {
            int l = i >> h;

            if (d[l]) {
                apply(2*l, p[l]);
                apply(2*l+1, p[l]);

                p[l] = noop;
                d[l] = false;
            }
        }
    }

    void upd(int i, int j, U update) {
        i += S, j += S;
        prop(i), prop(j);

        for (int l = i, r = j; l <= r; l /= 2, r /= 2) {
            if((l&1) == 1) apply(l++, update);
            if((r&1) == 0) apply(r--, update);
        }

        rebuild(i), rebuild(j);
    }

    T query(int i, int j){
        i += S, j += S;
        prop(i), prop(j);

        T res_left = z, res_right = z;
        for(; i <= j; i /= 2, j /= 2){
            if((i&1) == 1) res_left = res_left + v[i++];
            if((j&1) == 0) res_right = v[j--] + res_right;
        }
        return res_left + res_right;
    }
};

struct segNode {
    ll value;

    segNode operator+(const segNode &n) {
        return { max(value, n.value) };
    }
};

struct segUpdate {
    ll value;

    // How do we apply an operation?
    segNode operator()(const segNode &n) {
        if (value != -1) return { value };
        return { n.value };
    }

    segUpdate operator+(const segUpdate &u) {
        if (value == -1) return { u.value };
        return { value };
    }
};

const segNode segZero { -1 };
const segUpdate segNoUp { -1 };

ll dx[4] = { 1, -1, 0, 0 };
ll dy[4] = { 0, 0, 1, -1 };
ll inf = 2e17;

struct Point {
    ll x, y;
    int dir, index;
};

struct Arrow {
    ll x1, y1, x2, y2;
    int dir;
    Point special_point;
    int index;

    Arrow(ll x1, ll y1, ll x2, ll y2, int index): x1(x1), x2(x2), y1(y1), y2(y2), index(index) {
        if (x1 < x2) dir = RIGHT;
        else if (x1 > x2) dir = LEFT;
        else if (y1 < y2) dir = UP;
        else dir = DOWN;
        special_point = Point({ x2 + dx[dir], y2 + dy[dir], dir, index });
    }

    Point dirmost(int d) {
        return {
            dx[d] == 0 ? x1 : abs(max(x1 * dx[d], x2 * dx[d])),
            dy[d] == 0 ? y1 : abs(max(y1 * dy[d], y2 * dy[d])),
            dir,
            index
        };
    }

    ll distance2(Point p) {
        if (p.dir == UP) return max((ll) 0, min(y1, y2) - p.y);
        if (p.dir == DOWN) return max((ll) 0, p.y - max(y1, y2));
        if (p.dir == RIGHT) return max((ll) 0, min(x1, x2) - p.x);
        if (p.dir == LEFT) return max((ll) 0, p.x - max(x1, x2));
    }

    ll distance1(Point p) {
        ll p1 = abs(p.x - special_point.x) + abs(p.y - special_point.y);
        ll p2 = distance2(p);
        if (p1 < p2) {
            // This occurs if the point and vector are facing towards each other.
            // The actual distance should be 1 more, because we move into the vector head and then move back.
            return p2 + 1;
        }
        return p1;
    }

};

bool cmp(Point a, Point b, int dir) {
    return (a.x * dx[dir] + a.y * dy[dir]) > (b.x * dx[dir] + b.y * dy[dir]);
}

struct LCA {
    // The LCA allows for cycles here, so the maximum parent level we care about is 10^15 high.
    int LOGN = 50;
    int k;
    vector<vector<int> > par;
    // Dist 1 -> Distance to the end of the line.
    // Dist 2 -> Distance to the intersection with the line.
    vector<vector<ll> > dist;
    vector<vector<ll> > dist2;
    LCA(int k): k(k), par(k), dist(k), dist2(k) {
        for (int i=0; i<k; i++) { par[i].assign(LOGN+1, -1); dist[i].assign(LOGN+1, -1); dist2[i].assign(LOGN+1, -1); }
    }
    void set_par(int u, int v, ll d1, ll d2) {
        par[u][0] = v;
        dist[u][0] = d1;
        dist2[u][0] = d2;
    }
    void build() {
        for (int i=1; i<=LOGN; i++) for (int u=0; u<k; u++) {
            if (par[u][i-1] == -1) continue;
            par[u][i] = par[par[u][i-1]][i-1];
            if (par[u][i] != -1) {
                dist[u][i] = dist[u][i-1] + dist[par[u][i-1]][i-1];
                if (dist[u][i] > inf) dist[u][i] = inf;
                dist2[u][i] = dist[u][i-1] + dist2[par[u][i-1]][i-1];
                if (dist2[u][i] > inf) dist2[u][i] = inf;
            }
        }
    }
    pair<int, ll> last_point(int start, ll d) {
        for (int i=LOGN; i>=0; i--) {
            if (par[start][i] == -1) continue;
            if (dist[start][i] <= d) { d -= dist[start][i]; start = par[start][i]; }
        }
        return { start, d };
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    ll n, b;
    cin >> n >> b;

    vector<Arrow> arrows;
    for (int i=0; i<n; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        arrows.push_back(Arrow(x1, y1, x2, y2, i));
    }

    int q;
    cin >> q;
    vector<Point> queryPoints(q);
    vector<ll> queryDistances(q);

    for (int i=0; i<q; i++) {
        queryPoints[i].index = n + i;
        cin >> queryPoints[i].x >> queryPoints[i].y >> ws;
        char foo;
        cin >> foo;
        if (foo == 'D') queryPoints[i].dir = DOWN;
        else if (foo == 'U') queryPoints[i].dir = UP;
        else if (foo == 'L') queryPoints[i].dir = LEFT;
        else queryPoints[i].dir = RIGHT;
        cin >> queryDistances[i];
    }

    LCA lca(n+q);

    // Construct the neighbours for each interesting point.
    for (int dir=0; dir<4; dir++) {
        cerr << "Checking for direction " << dir << endl;
        // Get all interesting points which are facing this direction.
        vector<Point> points;
        for (auto a: arrows) {
            if (a.special_point.dir == dir) points.push_back(a.special_point);
        }
        for (auto p: queryPoints) if (p.dir == dir) points.push_back(p);
        cerr << points.size() << endl;
        // Sort these points from their furthest along in their respective direction decreasing.
        sort(points.begin(), points.end(), [dir](const Point a, const Point b) {
            return cmp(a, b, dir);
        });
        // cerr << arrows.size() << endl;
        // Now sort the arrows by the same metric.
        sort(arrows.begin(), arrows.end(), [dir](Arrow a, Arrow b) {
            return cmp(a.dirmost(dir), b.dirmost(dir), dir);
        });
        SegmentTree<segNode, segUpdate> st(b+1, segZero, segNoUp);
        int cur_index = 0;
        for (auto p: points) {
            // cerr << p.x << " " << p.y << endl;
            while (cur_index < arrows.size() && !cmp(p, arrows[cur_index].dirmost(dir), dir)) {
                // cerr << "Adding arrow " << arrows[cur_index].index << " before point " << p.x << " " << p.y << endl;
                int p1, p2;
                if (dir == UP || dir == DOWN) {
                    p1 = min(arrows[cur_index].x1, arrows[cur_index].x2);
                    p2 = max(arrows[cur_index].x1, arrows[cur_index].x2);
                } else {
                    p1 = min(arrows[cur_index].y1, arrows[cur_index].y2);
                    p2 = max(arrows[cur_index].y1, arrows[cur_index].y2);
                }
                st.upd(p1, p2, { cur_index });
                cur_index++;
            }
            int loc = abs(dy[dir]) * p.x + abs(dx[dir]) * p.y;
            int par = st.query(loc, loc).value;
            if (par != -1) {
                ll d1 = arrows[par].distance1(p);
                ll d2 = arrows[par].distance2(p);
                cerr << p.x << " " << p.y << " is distance " << d2 << " from line " << arrows[par].index << ", and " << d1 << " from the endpoint." << endl;
                lca.set_par(p.index, arrows[par].index, d1, d2);
            }
        }
    }

    /*for (int i=0; i<n; i++) {
        cerr << "Arrow " << arrows[i].index << " ends at " << arrows[i].special_point.x << " " << arrows[i].special_point.y << " and has parent " << lca.par[arrows[i].index][0] << endl;
    }

    for (int i=0; i<q; i++) {
        cerr << "Point " << i << " has parent " << lca.par[n+i][0] << endl;
    }
    lca.build();*/

    // Go back to the correct ordering of arrows.
    sort(arrows.begin(), arrows.end(), [](Arrow a, Arrow b) { return a.index < b.index; });

    for (int i=0; i<q; i++) {
        // cerr << i << endl;
        ll d = queryDistances[i];
        Point p = queryPoints[i];
        pair<int, ll> x = lca.last_point(p.index, d);
        // cerr << x.X << endl;
        Point new_point;
        if (x.X < n) { // Arrow.
            new_point = arrows[x.X].special_point;
        } else new_point = queryPoints[x.X - n];
        // Try moving up the tree a bit.
        if (lca.par[x.X][0] != -1 && lca.dist2[x.X][0] <= x.Y) {
            new_point.x = new_point.x + dx[new_point.dir] * lca.dist2[x.X][0];
            new_point.y = new_point.y + dy[new_point.dir] * lca.dist2[x.X][0];
            if (lca.par[x.X][0] < n) new_point.dir = arrows[lca.par[x.X][0]].dir;
            else new_point.dir = queryPoints[lca.par[x.X][0] - n].dir;
            x.Y -= lca.dist2[x.X][0];
        }
        // cerr << new_point.x << " " << new_point.y << endl;
        // Move remaining distance.
        new_point.x = new_point.x + dx[new_point.dir] * x.Y;
        new_point.y = new_point.y + dy[new_point.dir] * x.Y;
        new_point.x = max(min(new_point.x, b), (ll) 0);
        new_point.y = max(min(new_point.y, b), (ll) 0);
        cout << new_point.x << " " << new_point.y << endl;
    }

    return 0;
}

