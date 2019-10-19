#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

struct Graph {
    int V;
    vvi adj;
    vi indegree;
    Graph(int n): V(n), adj(n, vi()), indegree(n, 0) {}
    void addEdge(int v, int w) {
        adj[v].push_back(w);
        indegree[w]++;
    }
    void allTopSortsUtil(vi& res, bool visited[], vvi& sol) {
        bool flag = false;
        for (int i=0; i<V; i++) {
            if (indegree[i] == 0 && !visited[i]) {
                for (auto j: adj[i]) {
                    indegree[j]--;
                }
                res.push_back(i);
                visited[i] = true;
                allTopSortsUtil(res, visited, sol);

                visited[i] = false;
                res.erase(res.end() - 1);
                for (auto j: adj[i]) {
                    indegree[j]++;
                }
                flag = true;
            }
        }
        if (!flag) {
            vi total;
            for (int i=0; i<res.size(); i++) total.push_back(res[i]);
            if (total.size() == V)
                sol.push_back(total);
        }
    }
    vvi allTopSorts() {
        vvi sol;
        bool *visited = new bool[V];
        for (int i=0; i<V; i++)
            visited[i] = false;
        vi res;
        allTopSortsUtil(res, visited, sol);
        return sol;
    }
};

int main() {

    int n, m;
    cin >> n >> m >> ws;
    Graph g(n);

    for (int i=0; i<m; i++) {
        char a, b;
        cin >> a >> b >> ws;
        g.addEdge((int)(a-'A'), (int)(b-'A'));
    }

    vvi sol = g.allTopSorts();
    if (sol.size() == 0) {
        cout << 0 << endl;
    } else if (sol.size() == 1) {
        cout << 1 << endl;
        for (auto solution: sol) {
            for (auto s1: solution) {
                cout << (char)(s1+'A');
            }
            cout << endl;
        }
    } else {
        vvi found;
        for (int i=0; i<n; i++) {
            found.push_back(vi(n, false));
        }
        for (auto solution: sol) {
            for (int i=0; i<n; i++) for (int j=i+1; j<n; j++) {
                found[solution[i]][solution[j]] = true;
            }
        }
        vector<pair<int, int> > indeterminate;
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
                if (found[i][j] && found[j][i]) {
                    indeterminate.push_back(pair<int, int>(i, j));
                    indeterminate.push_back(pair<int, int>(j, i));
                }

        vector<vector<bool> > possible_values;
        possible_values.push_back(vector<bool>(sol.size(), true));
        while (1) {
            vector<vector<bool> > new_values;
            for (auto values: possible_values) {
                for (int i=0; i<values.size(); i++) if (values[i]) {
                    // Try disabling i.
                    vector<bool> new_ones(values.size());
                    for (int j=0; j<values.size(); j++) new_ones[j] = values[j];
                    new_ones[i] = 0;
                    vvi found;
                    for (int i=0; i<n; i++) {
                        found.push_back(vi(n, false));
                    }
                    for (int j=0; j<values.size(); j++) {
                        if (new_ones[j]) for (int k=0; k<n; k++) for (int l=k+1; l<n; l++) {
                            found[sol[j][k]][sol[j][l]] = true;
                        }
                    }
                    bool correct = true;
                    for (auto x: indeterminate) {
                        if (!found[x.first][x.second]) {
                            correct = false;
                            break;
                        }
                    }
                    if (correct) {
                        new_values.push_back(new_ones);
                    }
                }
            }
            if (new_values.size() == 0) break;
            possible_values.clear();
            for (auto val: new_values) possible_values.push_back(val);
        }
        vector<bool> value = possible_values[0];
        int num = 0;
        for (int i=0; i<value.size(); i++) if (value[i]) num++;
        cout << num << endl;
        for (int i=0; i<value.size(); i++) if (value[i]) {
            for (auto s1: sol[i]) {
                cout << (char)(s1+'A');
            }
            cout << endl;
        }
    }


    return 0;
}
