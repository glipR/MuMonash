#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <cstring>
#include <algorithm>

#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)

using namespace std;

string grid[20];

const int n = 19, m = 31;

struct Edge {
    int v, type;
    Edge(int a, int b) : v(a), type(b) {}
};

vector<Edge> list[n];

map<pair<int, int>, int> M;
map<int, pair<int, int> > RM;

int vertices = 0;
int vertex(int x, int y)
{
    if (M.find(mp(x, y)) == M.end())
    {
        M[mp(x,y)] = vertices;
        RM[vertices] = mp(x, y);
        vertices++;
    }
    return M[mp(x,y)];
}

void find_edge(int i, int j)
{
    int d = grid[i][j] == '>' ? -1 : 1;
    if (i-3 >= 0 && j + 3*d >= 0 && j + 3*d <= m-1)
    {
        if (grid[i-1][j+d] == grid[i-2][j+2*d] && grid[i-1][j+d] != '/' && grid[i-1][j+d] != '\\' && grid[i-1][j+d] != '.')
            list[vertex(i, j)].pb(Edge(vertex(i-3, j + 3*d), grid[i-1][j+d] - '0' ));
    }
    if (i+3 <= n-1 && j + 3*d >= 0 && j + 3*d <= m-1)
    {
        if (grid[i+1][j+d] == grid[i+2][j+2*d] && grid[i+1][j+d] != '/' && grid[i+1][j+d] != '\\' && grid[i+1][j+d] != '.')
            list[vertex(i, j)].pb(Edge(vertex(i+3, j + 3*d), grid[i+1][j+d] - '0' ));
    }
    
    d = -1 * d;
    if (j + 6*d < m && j + 6*d >= 0)
    {
        bool all = true;
        for (int q = 2; q <= 5; q++) all &= grid[i][j+d] == grid[i][j + q*d];
        if (all && grid[i][j+d] != '-' && grid[i][j+d] != '.')
            list[vertex(i, j)].pb(Edge(vertex(i, j+6*d), grid[i][j+d] - '0'));
    }
}


bool mark[n*m][n*m];

int longest_path(int v, int type)
{
    int ans = 0;
    for (auto edge : list[v])
    {
        if (edge.type != type || mark[v][edge.v]) continue;
        mark[v][edge.v] = 1; mark[edge.v][v] = 1;
        ans = max(ans, 1 + longest_path(edge.v, type));
        mark[v][edge.v] = 0; mark[edge.v][v] = 0;
    }
    return ans;
}

int main()
{
    for (int i = 0; i < n; i++) cin >> grid[i];
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '>' || grid[i][j] == '<')
                find_edge(i, j);
        }
    }

    if (0)
    {
    for (int i = 0; i < vertices; i++)
    {
        cout << "Edges from " << RM[i].first << ", " << RM[i].second << endl;
        for (auto edge : list[i])
            cout << "-- to: " << RM[edge.v].first << ", " << RM[edge.v].second << ", type: " << edge.type << endl;
        cout << endl;
    }
    }

    int ans[3] = {0, 0, 0};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            memset(mark, false, sizeof(mark));
            ans[i] = max(ans[i], longest_path(j, i+1));
        }
        cout << ans[i] << ' ';
    }
    cout << endl;

}
