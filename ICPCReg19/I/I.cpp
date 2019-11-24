// MuMonash
#include <iostream>
#include <vector>
#include <queue>

#define X first
#define Y second

using namespace std;

#define MAXN 200

bool grid[MAXN][MAXN];
int n;

bool interesting(int i, int j) {
    if ( i == j && ((i == 0) || (i == n-1))) return true;
    if (!grid[i][j]) return false;
    int x_n = 0;
    int y_n = 0;
    if (i > 0 && grid[i-1][j]) x_n++;
    if (i < n-1 && grid[i+1][j]) x_n++;
    if (j > 0 && grid[i][j-1]) y_n++;
    if (j < n-1 && grid[i][j+1]) y_n++;
    return !(x_n == 0 || y_n == 0);
}

typedef pair<int, int> pii;

int encode(int i, int j) { return 100 * i + j; }
pii decode(int a) { return {a / 100, a % 100}; }

int main() {

    cin >> n >> ws;

    for (int i=0; i<n; i++) for (int j=0; j<n; j++) {
        char c;
        cin >> c >> ws;
        grid[i][j] = c == '.';
    }

    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi adj(encode(n-1, n-1) + 1);
    for (int i=0; i<n; i++) for (int j=0; j<n; j++) if (interesting(i, j)) {
        // Generate the neighbour below and to the right of me.
        for (int a=i+1; a<n; a++) {
            if (!grid[a][j]) break;
            if (interesting(a, j)) {
                for (auto v: adj[encode(i, j)]) if (decode(v).Y == j) adj[v].push_back(encode(a, j));
                adj[encode(i, j)].push_back(encode(a, j));
                adj[encode(a, j)].push_back(encode(i, j));
                break;
            }
        }
        for (int b=j+1; b<n; b++) {
            if (!grid[i][b]) break;
            if (interesting(i, b)) {
                for (auto v: adj[encode(i, j)]) if (decode(v).X == i) adj[v].push_back(encode(i, b));
                adj[encode(i, j)].push_back(encode(i, b));
                adj[encode(i, b)].push_back(encode(i, j));
                break;
            }
        }
    }

    /*for (int i=0; i<n; i++) for (int j=0; j<n; j++) if (interesting(i, j)) {
        cerr << "Points for " << i << " " << j << ": " << endl;
        for (int v: adj[encode(i, j)]) {
            cerr << "(" << decode(v).X << "," << decode(v).Y << ") ";
        }
        cerr << endl;
    }*/

    // BFS time
    vi dist(encode(n-1, n-1)+1, n*n + 1);
    vi points;
    points.push_back(encode(0, 0));
    int iter = 0;
    int top_dist = n*n + 1;
    while (dist[encode(n-1, n-1)] == top_dist) {
        vi new_points;
        for (auto p: points) {
            dist[p] = iter;
            for (auto v: adj[p]) if (dist[v] == top_dist) new_points.push_back(v);
        }
        points = new_points;
        iter++;
    }

    cout << dist[encode(n-1, n-1)] << endl;

    return 0;
}
