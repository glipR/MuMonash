// MuMonash

#include <iostream>

using namespace std;

typedef pair<int, int> pii;

#define EMPTY 0
#define KING 1
#define ENEMY 2
#define SPOTTED 3

int main() {

    int n;
    cin >> n >> ws;

    pii king_position;

    int BOARD[n][n];
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            char x;
            cin >> x;
            if (x == '*') {
                BOARD[i][j] = ENEMY;
            } else if (x == 'K') {
                BOARD[i][j] = KING;
                king_position = pii(i, j);
            } else {
                BOARD[i][j] = EMPTY;
            }
        }
    }

    int pawns = 0;
    bool possible = true;

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (BOARD[i][j] == ENEMY) {
                if (abs(i - king_position.first) <= 1 && abs(j - king_position.second) <= 1) {
                    BOARD[i][j] = SPOTTED;
                    continue;
                }
                if (i+1 < n && j+1 < n && BOARD[i+1][j+1] == EMPTY) {
                    // Choose the right side where possible
                    pawns += 1;
                    if (j+2 < n && BOARD[i][j+2] == ENEMY) BOARD[i][j+2] = SPOTTED;
                } else if (i+1 < n && j-1 < n && BOARD[i+1][j-1] == EMPTY) {
                    pawns += 1;
                } else {
                    possible = false;
                }
            }
        }
    }

    if (possible) {
        cout << pawns << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}
