// MuMonash
// AC

#include <iostream>

using namespace std;

typedef long long ll;

int main() {

    int h, w;
    cin >> h >> w;

    int table[h][w];
    for (int r=0; r<h; r++) for (int c=0; c<w; c++) table[r][c] = -1;

    bool possible = true;

    for (int r=0; r<h; r++) {
        int val;
        cin >> val;
        for (int j=0; j<val; j++) {
            if (table[r][j] == 1 || table[r][j] == -1) table[r][j] = 1;
            else possible = false;
        }
        if (val < w) {
            if (table[r][val] == 1) possible = false;
            table[r][val] = 0;
        }
    }
    for (int c=0; c<w; c++) {
        int val;
        cin >> val;
        for (int j=0; j<val; j++) {
            if (table[j][c] == 1 || table[j][c] == -1) table[j][c] = 1;
            else possible = false;
        }
        if (val < h) {
            if (table[val][c] == 1) possible = false;
            table[val][c] = 0;
        }
    }

    ll res = 1;
    ll MOD = 1000000007;

    for (int r=0; r<h; r++) for (int c=0; c<w; c++) {
        //cerr << table[r][c] << ' ';
        //if (c == w-1) cerr << endl;
        if (table[r][c] == -1) {
            res *= 2;
            res %= MOD;
        }
    }

    if (possible) {
        cout << res << endl;
    } else {
        cout << 0;
    }

    return 0;
}
