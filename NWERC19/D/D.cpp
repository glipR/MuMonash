#include <iostream>
#include <vector>

using namespace std;

#define X first
#define Y second

typedef vector<int> vi;
typedef long long ll;

template<typename T> struct BellmanFord {
    typedef pair<T, int> pti; vector<vector<pti> > adj;
    int n = -1; const T INF = numeric_limits<T>::max() / 2;
    BellmanFord(int n) : adj(n), n(n) {}
    void add_edge(int u, int v, T weight) { adj[u].emplace_back(weight, v); }
    pair<vector<vector<T> >, vector<vector<bool> > > shortest_paths(int src, int length) {
        vector<vector<T> > dist(n+1); vector<vector<bool> > pred(n);
        for (int i=0; i<n; i++) pred[i] = vector<bool>(n, false);
        for (int i=0; i<n; i++) dist[i] = vector<T>(n+1, INF);
        for (int i=0; i<n+1; i++) dist[src][i] = 0;
        for (int k=0; k<(length == -1 ? n : length); k++) {
            for (int u=0; u<n; u++) if (dist[u][k] < INF) for (auto &e: adj[u]) {
                int v = e.Y; T len = dist[u][k] + e.X;
                if (len < dist[v][k+1]) {
                    for (int i=k+1; i<n+1; i++) dist[v][i] = len;
                    for (int i=0; i<n; i++) pred[v][i] = i == u;
                } else if (len == dist[v][k+1] && !pred[v][u]) {
                    pred[v][u] = true;
                }
            }
        }
        return {dist, pred};
    }
};

int main() {

    int n, m;
    cin >> n >> m;

    BellmanFord<ll> bf(n);
    for (int i=0; i<m; i++) {
        ll a, b, l;
        cin >> a >> b >> l;
        a--;
        b--;
        bf.add_edge(a, b, l);
        bf.add_edge(b, a, l);
    }

    vector<bool> marked(n, false);
    vector<int> dist(n, -1);
    dist[n-1] = 0;

    auto res = bf.shortest_paths(0, -1);
    // The paths that are optimal when c = 0.
    // BFS out from n and mark nodes as used.
    vector<int> nodes(1, n-1);

    /*for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cerr << res.Y[i][j];
        }
        cerr << endl;
    }*/

    while (nodes.size()) {
        auto node = nodes[nodes.size() - 1];
        marked[node] = true;
        nodes.pop_back();
        for (int i=0; i<n; i++) if (res.Y[node][i]) {
            dist[i] = dist[node] + 1;
            nodes.push_back(i);
        }
    }

    // cerr << "Done in " << dist[0] << " steps" << endl;

    // Now we need to find the shortest length path of length k, with BFS.
    auto res2 = bf.shortest_paths(0, dist[0]);
    /*for (int i=0; i<n; i++) {
        cerr << "Distances for " << i+1 << endl;
        for (int j=0; j<res2.X[i].size(); j++) {
            cerr << res2.X[i][j] << " ";
        }
        cerr << endl;
    }*/
    long double c = bf.INF;
    ll total_length = dist[0];
    ll total_dist = res.X[n-1][dist[0]];
    for (int i=0; i<dist[0]; i++) {
        // cerr << "Trying to find paths with length " << i << endl;
        long double new_c = ((long double) (res.X[n-1][i] - total_dist)) / ((long double) (dist[0] - i));
        // cerr << new_c << endl;
        if (new_c >= c - 1e-18) continue;
        c = new_c;
        vector<int> nodes2(1, n-1);
        for (int j=i; j>0; j--) {
            vector<int> nodes3;
            for (auto node: nodes2) {
                // cerr << "Distance " << j << " node " << node + 1 << endl;
                marked[node] = true;
                for (auto n: bf.adj[node]) {
                    // cerr << "Checking node " << n.Y + 1 << ". " << res2.X[node][j] << " " << n.X << " " << res2.X[n.Y][j-1] << endl;
                    if (res2.X[node][j] == res2.X[n.Y][j-1] + n.X) {
                        // cerr << n.Y << endl;
                        nodes3.push_back(n.Y);
                    }
                }
            }
            nodes2 = nodes3;
        }
    }

    vector<int> unused;
    for (int i=0; i<n; i++) if (!marked[i]) unused.push_back(i);

    cout << unused.size() << endl;
    if (unused.size()) {
        cout << unused[0] + 1;
        for (int i=1; i<unused.size(); i++) { cout << " " << unused[i] + 1;}
        cout << endl;
    }


    return 0;
}
