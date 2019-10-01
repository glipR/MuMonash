// MuMonash

#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n >> ws;

    int num_plays[1 << n];
    int plays[1 << n][n];
    for (int i=0; i<1 << n; i++) {
        num_plays[i] = 0;
        for (int j=0; j<n; j++) {
            plays[i][j] = -1;
        }
    }

    bool bad = false;
    for (int m=0; m< (1 << n) - 1; m++) {
        int p1, p2;
        cin >> p1 >> p2 >> ws;
        p1--;
        p2--;
        if ((++num_plays[p1] > n) || (++num_plays[p2] > n)) {
            bad = true;
            break;
        }
        plays[p1][num_plays[p1] - 1] = p2;
        plays[p2][num_plays[p2] - 1] = p1;
    }

    if (!bad) {
        // Make sure that every player plays 1 player less than him for every number less.
        // And make sure that he only plays 1 player above him.
        for (int p=0; p< (1 << n); p++) {
            if (num_plays[p] == 0) {
                bad = true;
                break;
            }
            // cerr << p << " played " << num_plays[p] << endl;
            if (num_plays[p] == n) {
                // We play one from every round.
                bool players_below[n];
                for (int k=0; k<n; k++) players_below[k] = false;
                for (auto p2: plays[p]) {
                    if (0 < num_plays[p2] && num_plays[p2] <= n) {
                        if (players_below[num_plays[p2] - 1]) {
                            bad = true;
                            break;
                        } else {
                            players_below[num_plays[p2] - 1] = true;
                        }
                    } else {
                        bad = true;
                        break;
                    }
                }
            } else {
                // last index isn't used but ensures we don't have 0 length array.
                bool players_below[num_plays[p]];
                bool above_player = false;
                for (int k=0; k<num_plays[p]-1; k++) players_below[k] = false;
                for (auto p2: plays[p]) {
                    if (p2 == -1) break;
                    if (0 < num_plays[p2] && num_plays[p2] < num_plays[p]) {
                        if (players_below[num_plays[p2] - 1]) {
                            bad = true;
                            break;
                        } else {
                            players_below[num_plays[p2] - 1] = true;
                        }
                    } else if (num_plays[p2] > num_plays[p]) {
                        if (above_player) {
                            bad = true;
                            break;
                        } else {
                            above_player = true;
                        }
                    } else {
                        bad = true;
                        break;
                    }
                }
            }
        }
    }

    cout << (bad ? "MISTAKE" : "OK") << endl;

    return 0;
}
