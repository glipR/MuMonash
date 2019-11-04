#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

struct BipartiteMatching {
    int L, R, p; vi m, used, d; vvi adj; queue<int> q;
    bool bfs() {
        for (int v=0; v<R; v++) if (!used[v]) d[v] = p, q.push(v);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            if (d[v] != d[R]) for (int u: adj[v]) if (d[m[u]] < p)
                d[m[u]] = d[v] + 1, q.push(m[u]);
        }
        return d[R] >= p;
    }
    int dfs(int v) {
        if (v == R) return 1;
        for (int u : adj[v]) if (d[m[u]] == d[v] + 1 && dfs(m[u])) return m[u] = v, 1;
        d[v] = d[R]; return 0;
    }
    BipartiteMatching(int L, int R): L(L), R(R), d(R+1), adj(R) {}
    void add_edge(int u, int v) {
        adj[v].push_back(u);
    }
    pair<int, vi> match() {
        int res = 0; m.assign(L, R), used.assign(R+1, 0);
        for (p=0; bfs(); p = d[R]+1) for (int v=0; v<R; v++)
            if (!used[v] && dfs(v)) used[v] = 1, res++;
        replace(m.begin(), m.end(), R, -1); return {res, m};
    }
};

struct BipartiteMatchingCap {
    int L, R, p; vi m, used, d, capacity; vvi adj; queue<int> q;
    bool bfs() {
        for (int v=0; v<R; v++) if (used[v] < capacity[v]) d[v] = p, q.push(v);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            if (d[v] != d[R]) for (int u: adj[v]) if (d[m[u]] < p)
                d[m[u]] = d[v] + 1, q.push(m[u]);
        }
        return d[R] >= p;
    }
    int dfs(int v) {
        if (v == R) return 1;
        for (int u : adj[v]) if (d[m[u]] == d[v] + 1 && dfs(m[u])) return m[u] = v, 1;
        d[v] = d[R]; return 0;
    }
    BipartiteMatchingCap(int L, int R): L(L), R(R), d(R+1), adj(R), capacity(R, 1) {}
    void add_edge(int u, int v) {
        adj[v].push_back(u);
    }
    pair<int, vi> match() {
        int res = 0; m.assign(L, R), used.assign(R+1, 0);
        for (p=0; bfs(); p = d[R]+1) for (int v=0; v<R; v++)
            if ((used[v] < capacity[v]) && dfs(v)) used[v]++, res++;
        replace(m.begin(), m.end(), R, -1); return {res, m};
    }
};

int main() {

    BipartiteMatching bm(3, 3);
    BipartiteMatchingCap bmc(3, 3);
    bm.add_edge(0, 0);
    bm.add_edge(0, 1);
    bm.add_edge(1, 1);
    bm.add_edge(2, 1);
    bmc.add_edge(0, 0);
    bmc.add_edge(0, 1);
    bmc.add_edge(1, 1);
    bmc.add_edge(2, 1);
    bmc.capacity[1] = 2;

    auto m = bm.match();
    auto mc = bmc.match();

    cout << "Non capacity:" << endl;
    cout << m.first << " matchings!" << endl;
    for (auto v: m.second) {
        cout << v << " ";
    }
    cout << endl;

    cout << "capacity:" << endl;
    cout << mc.first << " matchings!" << endl;
    for (auto v: mc.second) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}
