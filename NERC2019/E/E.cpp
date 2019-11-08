#include <iostream>
#include <vector>

#define UNKNOWN 1
#define SAME 2
#define DIFF 3

using namespace std;

typedef long long ll;
typedef vector<int> vi;

int main() {

    int t;
    cin >> t;

    for (int testno=0; testno<t; testno++) {
        int n, m, k;
        cin >> n >> m >> k;
        // cerr << "Test " << testno << endl;

        int necklaces[n][m];
        for (int i=0; i<n; i++) for (int j=0; j<m; j++) {
            char c;
            cin >> c;
            necklaces[i][j] = (c != '0');
        }

        int adj[n][n];
        for (int i=0; i<n; i++) for (int j=0; j<n; j++) adj[i][j] = UNKNOWN;

        bool impossible = false;
        for (int i=0; i<n; i++) for (int j=i+1; j<n; j++) {
            // How can we group i and j?
            int same = 0;
            int diff = 0;
            for (int l=0; l<m; l++) {
                if (necklaces[i][l] == necklaces[j][l]) same++;
                if (necklaces[i][l] == necklaces[j][m - l - 1]) diff++;
            }
            // cerr << i << " " << j << " " << same << " " << diff << endl;
            if (same >= k && diff >= k) continue;
            else if (same >= k) {
                adj[i][j] = SAME;
            } else if (diff >= k) {
                adj[i][j] = DIFF;
            } else {
                impossible = true;
            }
        }

        if (!impossible) {
            // Floyd Warshall's.
            for (int j=0; j<n; j++) {
                for (int i=0; i<n; i++) {
                    if (i == j) continue;
                    for (int l=0; l<n; l++) {
                        if (j == l || i == l) continue;
                        int a = min(i, l);
                        int b = max(i, l);
                        // cerr << a << " to " << b << " thru " << j << endl;
                        if ((adj[min(a, j)][max(a, j)] == UNKNOWN) || (adj[min(j, b)][max(j, b)] == UNKNOWN)) continue;
                        if (adj[min(a, j)][max(a, j)] == adj[min(j, b)][max(j, b)]) {
                            if (adj[a][b] == DIFF) impossible = true;
                            adj[a][b] = SAME;
                        } else {
                            if (adj[a][b] == SAME) impossible = true;
                            adj[a][b] = DIFF;
                        }
                    }
                }
            }

            if (!impossible) {
                /* for (int i=0; i<n; i++) {
                    for (int j=i+1; j<n; j++) {
                        cerr << adj[i][j] << " ";
                    }
                    cerr << endl;
                }*/
                // We have a solution, solve for each variable.
                int soln[n];
                for (int i=0; i<n; i++) soln[i] = UNKNOWN;
                for (int i=0; i<n; i++) if (soln[i] == UNKNOWN) {
                    int same = 0;
                    int diff = 0;
                    for (int j=i+1; j<n; j++) {
                        if (adj[i][j] == SAME) same++;
                        if (adj[i][j] == DIFF) diff++;
                    }
                    if (same >= diff) {
                        soln[i] = SAME;
                        for (int j=i+1; j<n; j++) {
                            if (adj[i][j] == SAME) soln[j] = SAME;
                            if (adj[i][j] == DIFF) soln[j] = DIFF;
                        }
                    } else {
                        soln[i] = DIFF;
                        for (int j=i+1; j<n; j++) {
                            if (adj[i][j] == SAME) soln[j] = DIFF;
                            if (adj[i][j] == DIFF) soln[j] = SAME;
                        }
                    }
                }

                int flipped = 0;
                for (int i=0; i<n; i++) if (soln[i] == DIFF) flipped ++;
                cout << flipped << endl;
                bool first = true;
                for (int i=0; i<n; i++) if (soln[i] == DIFF) {
                    if (!first) {
                        cout << " ";
                    }
                    cout << i+1;
                    first = false;
                }
                cout << endl;
            }
        }

        if (impossible) {
            cout << -1 << endl;
        }
    }

    return 0;
}
