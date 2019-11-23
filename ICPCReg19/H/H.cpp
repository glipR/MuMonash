// MuMonash
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

template<typename T> struct Dinics {
    struct edge { int to; T flow, cap; }; T INF = numeric_limits<T>::max();
    int n, m; vi dist, work; queue<int> q; vector<edge> edges; vvi adj;
    bool bfs(int s, int t) {
        dist.assign(n, -1); dist[s] = 0; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto& i: adj[u]) {
                edge& e = edges[i]; int v = e.to;
                if (dist[v] < 0 && e.flow < e.cap) dist[v] = dist[u] + 1, q.push(v);
            }
        }
        return dist[t] >= 0;
    }
    T dfs(int u, int t, T f) {
        if (u == t) return f;
        for (int& i=work[u]; i<(int)adj[u].size(); i++) {
            auto& e = edges[adj[u][i]], &rev = edges[adj[u][i]^1];
            if (e.flow < e.cap && dist[e.to] == dist[u] + 1) {
                T df = dfs(e.to, t, min(f, e.cap - e.flow));
                if (df > 0) { e.flow += df; rev.flow -= df; return df; }
            }
        }
        return 0;
    }
    Dinics(int n): n(n), m(0), adj(n) {}
    int add_edge(int from, int to, T cap) {
        adj[from].push_back(m++), adj[to].push_back(m++);
        edges.push_back({to, 0, cap}), edges.push_back({from, 0, 0});
        return m - 2;
    }
    edge& get_edge(int i) { return edges[i]; }
    T max_flow(int s, int t) {
        T res = 0;// for (auto& e: edges) e.flow = 0;
        while (work.assign(n, 0), bfs(s, t))
            while (T delta = dfs(s, t, INF)) res += delta;
        return res;
    }
};

int main() {

    int n;
    cin >> n;
    Dinics<int> d(n+2);
    // 0 = source, n+1 = sink.
    vector<bool> locked;
    vvi opens;
    for (int i=0; i<n; i++) {
        int o;
        cin >> o;
        locked.push_back(o == 0);
        opens.push_back(vi(o));
        for (int i=0; i<o; i++) {
            cin >> opens[opens.size()-1][i];
        }
    }
    // Now that we know what is locked, go back through and add the edges.
    bool done = false;
    for (int i=0; i<n; i++) {
        if (!locked[i]) {
            for (auto v: opens[i]) if (v-1 > i && locked[v-1])
                d.add_edge(v, i+1, 1);
            d.add_edge(i+1, n+1, 1);
        } else {
            d.add_edge(0, i+1, 1);
            // Can we now solve this flow problem?
            if (d.max_flow(0, n+1) != 1) {
                // No. We can move just before this lock
                done = true;
                cout << i << endl;
                break;
            }
        }
    }
    if (!done) {
        cout << n << endl;
    }

    return 0;
}
