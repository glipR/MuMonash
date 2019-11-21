#include <iostream>
#include <queue>

#define X first
#define Y second

using namespace std;

typedef pair<int, int> pii;

int main() {

    int n, m;
    cin >> n >> m;

    char table[n][m];
    for (int i=0; i<n; i++) for (int j=0; j<m; j++) { cin >> table[i][j]; }

    int marking[n][m];
    for (int i=0; i<n; i++) for (int j=0; j<m; j++) { marking[i][j] = -2; }

    queue<pii> q;

    for (int i=0; i<n; i++) {
        if (table[i][0] == '0') {
            marking[i][0] = -1;
            q.push({ i, 0 });
        }
        if (table[i][m-1] == '0') {
            marking[i][m-1] = -1;
            q.push({ i, m-1 });
        }
    }
    for (int i=0; i<m; i++) {
        if (table[0][i] == '0') {
            marking[0][i] = -1;
            q.push({ 0, i });
        }
        if (table[n-1][i] == '0') {
            marking[n-1][i] = -1;
            q.push({ n-1, i });
        }
    }

    while (q.size()) {
        pii res = q.front(); q.pop();
        for (int a=-1; a<=1; a++) for (int b=-1; b<=1; b++) {
            int x = res.X + a;
            int y = res.Y + b;
            if (0 <= x && x < n && 0 <= y && y < m) {
                if (table[x][y] == '1') continue;
                if (marking[x][y] == -2) {
                    marking[x][y] = marking[res.X][res.Y];
                    q.push({ x, y });
                }
            }
        }
    }

    int comp = 0;
    int total_cycle = 0;

    for (int i=0; i<n-1; i++) for (int j=0; j<m-1; j++) {
        if (table[i][j] == '1') if (table[i][j+1] == '1') if (table[i+1][j] == '1') if (table[i+1][j+1] == '1') total_cycle = 4;
    }

    for (int i=0; i<n; i++) for (int j=0; j<m; j++) {
        if (marking[i][j] != -2) continue;
        if (table[i][j] == '1') continue;
        marking[i][j] = comp;
        int cycle_length = 0;
        q.push({ i, j });
        while (q.size()) {
            pii res = q.front(); q.pop();
            for (int a=-1; a<=1; a++) for (int b=-1; b<=1; b++) {
                int x = res.X + a;
                int y = res.Y + b;
                if (0 <= x && x < n && 0 <= y && y < m) {
                    // cerr << x << " " << y << endl;
                    if (table[x][y] == '1') {
                        if (marking[x][y] != - comp - 3) {
                            marking[x][y] = - comp - 3;
                            cycle_length ++;
                        }
                    }
                    if (marking[x][y] == -2) {
                        marking[x][y] = comp;
                        q.push({ x, y });
                    }
                }
            }
        }
        q.push({ i-1, j });
        marking[i-1][j] = n*m;
        int ones = 0;
        bool bad = false;
        while (q.size()) {
            pii res = q.front(); q.pop();
            // cerr << res.X << " " << res.Y << " " << marking[res.X][res.Y] << endl;
            ones++;
            int neighbours = 0;
            for (int a=-1; a<=1; a++) for (int b=-1; b<=1; b++) {
                if (abs(a) + abs(b) != 1) continue;
                int x = res.X + a;
                int y = res.Y + b;
                if (0 <= x && x < n && 0 <= y && y < m) {
                    if ((table[x][y] == '1') && (marking[x][y] == - comp - 3)) {
                        marking[x][y] = n*m;
                        // cerr << res.X << " " << res.Y << " to " << x << " " << y << endl;
                        q.push({ x, y });
                        neighbours++;
                    }
                }
            }
            if (res.X != i-1 || res.Y != j) if (neighbours > 1) bad = true;
        }
        comp++;
        // cerr << ones << endl;
        // cerr << bad << endl;
        // cerr << cycle_length << endl;
        if (bad) continue;
        if (cycle_length != ones) continue;
        total_cycle = max(total_cycle, cycle_length);
    }

    /*for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cerr << marking[i][j] << "\t";
        }
        cerr << endl;
    }*/

    cout << total_cycle << endl;

    return 0;
}
