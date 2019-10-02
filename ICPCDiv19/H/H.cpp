// MuMonash

#include <iostream>

#define MAX_WALK 20

using namespace std;

bool valid(int i, int j, int r, int c) {
    return (0 <= i && i < r) && (0 <= j && j < c);
}

int main() {

    int m;
    cin >> m >> ws;
    string walk = "";
    if (m != 0) {
        getline(cin, walk);
    }

    int r, c;
    cin >> r >> c >> ws;
    int vals[r][c];

    for (int i=0; i<r; i++) for (int j=0; j<c; j++) {
        cin >> vals[i][j];
    }

    int best = 0;
    for (int i=-MAX_WALK; i<r + MAX_WALK; i++) {
        for (int j=-MAX_WALK; j<c + MAX_WALK; j++) {
            // Try starting at i, j.
            int dist = 0;
            bool marked[r][c];
            for (int x=0; x<r; x++) for (int y=0; y<c; y++) marked[x][y] = false;
            if (valid(i, j, r, c)) {
                dist += vals[i][j];
                marked[i][j] = true;
            }
            int p1=i;
            int p2=j;
            for (auto dir: walk) {
                if (dir == 'u') p1--;
                else if (dir == 'd') p1++;
                else if (dir == 'l') p2--;
                else if (dir == 'r') p2++;
                else continue;
                if (valid(p1, p2, r, c) && !marked[p1][p2]) {
                    dist += vals[p1][p2];
                    marked[p1][p2] = true;
                }
            }
            best = max(best, dist);
        }
    }

    cout << best << endl;

    return 0;
}
