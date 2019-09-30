#include <iostream>
#include <iomanip>

// We need a bit extra in the DP table because we allow the left hand side of the first cable to persist.
#define EXTRA 20

using namespace std;

long double calculate_overlap(int num_cables, int total_length, int distance) {
    if (total_length == -1) return -1;
    int overlaps = num_cables + 1;
    int overlap_length = 10 + total_length - 5 * overlaps;
    if (overlap_length > distance) return -1;
    return 5 - (distance - overlap_length) / (long double) overlaps;
}

int main() {

    int n, g;
    cin >> n >> g >> ws;

    // DP[i][j] - We can reach i+1 packed space when using j+1 cables.

    bool DP[g+EXTRA][n];
    for (int x=0; x<g+EXTRA; x++)
        for (int y=0; y<n; y++)
            DP[x][y] = false;

    for (int x=0; x<n; x++) {
        int length;
        cin >> length >> ws;
        for (int j=n-1; j >= 1; j--)
            for (int i=0; i<g+EXTRA; i++)
                if (DP[i][j-1])
                    if (i + length - 5 < g+EXTRA)
                        DP[i + length - 5][j] = true;
        if (length < g+EXTRA)
            DP[length][0] = true;
    }

    // Find the maximum valid distance for every amount of cables. Print the maximum remaining overlap.
    long double best_overlap = calculate_overlap(0, 0, g);
    for (int x=0; x<n; x++) {
        for (int i=g-1+EXTRA; i >= 0; i--) {
            if (DP[i][x] == false) continue;
            // We subtracted 5 for every subsequent cable.
            if (calculate_overlap(x+1, i + 5 * x, g) >= 0) {
                best_overlap = max(best_overlap, calculate_overlap(x+1, i + 5 * x, g));
                // We only need to see the largest distance most successful for each x.
                break;
            }
        }
    }
    /*
    for (int x=0; x<n; x++) {
        for (int y=0; y<g+EXTRA; y++) {
            cerr << DP[y][x] << ' ';
        }
        cerr << endl;
    }
    */

    if (best_overlap >= 0) {
        cout << fixed << setprecision(10) << best_overlap << endl;
    } else {
        cout << "impossible" << endl;
    }

    return 0;
}
