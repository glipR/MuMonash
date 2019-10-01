// MuMonash
// AC

#include <iostream>
#include <vector>
#include <limits>

#define NEXT 0
#define PREV 1
#define GTE 2
#define LTE 3

#define X first
#define Y second

using namespace std;

typedef vector<int> vi;

template <typename T> struct BellmanFord {
    typedef pair<T, int> pti; vector<vector<pti> > adj;
    int n, last = -1; const T INF = numeric_limits<T>::max() / 2;
    BellmanFord(int n) : adj(n), n(n) {}
    void add_edge(int u, int v, T weight) {adj[u].emplace_back(weight, v); }
    pair<vector<T>, vi> shortest_paths(int src) {
        vector<T> dist(n, INF); dist[src] = 0; vi pred(n, -1); last = 0;
        for (int k=0; k<n && last != -1; k++) { last = -1;
            for (int u=0; u<n; u++)
                if (dist[u] < INF)
                    for (auto &e: adj[u]) {
                        int v = e.Y; T len = dist[u] + e.X;
                        if (len < dist[v]) dist[v] = len, pred[v] = u, last = v;
                    }
        }
        return {dist, pred};
        // If last != -1 then negative cycle.
    }
    bool had_negative_cycle() { return last != -1; }
};

int main() {

    int n, g, r, c;
    cin >> n >> g >> r >> c >> ws;
    int rows[62500][4];
    int cols[62500][4];

    // Construct 2 graphs, each with n+1 nodes.
    BellmanFord<int> row_solver(n+1);
    for (int r_n=1; r_n<n+1; r_n++) {
        row_solver.add_edge(0, r_n, 0);
    }
    BellmanFord<int> column_solver(n+1);
    for (int c_n=1; c_n<n+1; c_n++) {
        column_solver.add_edge(0, c_n, 0);
    }

    for (int c_r=0; c_r < r; c_r++) {
        cin >> rows[c_r][NEXT] >> rows[c_r][PREV] >> rows[c_r][GTE] >> rows[c_r][LTE] >> ws;
        // dist(PREV) <= dist(NEXT) - GTE (Next is at least GTE away from PREV)
        row_solver.add_edge(rows[c_r][NEXT], rows[c_r][PREV], -rows[c_r][GTE]);
        // dist(NEXT) <= dist(PREV) + LTE (NExt is at most LTE away from PREV)
        row_solver.add_edge(rows[c_r][PREV], rows[c_r][NEXT], rows[c_r][LTE]);
    }
    for (int c_c=0; c_c < c; c_c++) {
        cin >> cols[c_c][NEXT] >> cols[c_c][PREV] >> cols[c_c][GTE] >> cols[c_c][LTE] >> ws;
        // dist(PREV) <= dist(NEXT) - GTE (Next is at least GTE away from PREV)
        column_solver.add_edge(cols[c_c][NEXT], cols[c_c][PREV], -cols[c_c][GTE]);
        // dist(NEXT) <= dist(PREV) + LTE (NExt is at most LTE away from PREV)
        column_solver.add_edge(cols[c_c][PREV], cols[c_c][NEXT], cols[c_c][LTE]);
    }

    // Now see if we have a valid solution for both rows and columns.
    pair<vi, vi> row_ans = row_solver.shortest_paths(0);
    pair<vi, vi> col_ans = column_solver.shortest_paths(0);

    // cerr << (row_solver.had_negative_cycle() ? "row" : "") << ' ' << (column_solver.had_negative_cycle() ? "column" : "") << endl;

    if (row_solver.had_negative_cycle() || column_solver.had_negative_cycle()) {
        cout << -1 << endl;
    } else {
        bool bad = false;
        for (int x=1; x<n+1; x++) {
            if ((g + row_ans.X[x] <= 0) || (g + col_ans.X[x] <= 0))
                bad = true;
        }
        if (bad) cout << -1 << endl;
        else for (int x=1; x<n+1; x++) cout << g + row_ans.X[x] << ' ' << g + col_ans.X[x] << endl;
    }

    return 0;
}
