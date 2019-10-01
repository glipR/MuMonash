// MuMonash

#include <iostream>

using namespace std;

int main() {

    int n;
    cin >> n;

    int rows[n];
    int cols[n];

    for (int i=0; i<n; i++) {
        cin >> rows[i];
    }
    for (int j=0; j<n; j++) {
        cin >> cols[j];
    }

    int solution[n][n];
    for (int i=0; i<n; i++) for (int j=0; j<n; j++)
        solution[i][j] = 0;

    int cur_r = 0;
    int cur_c = 0;

    while ((cur_r != n) && (cur_c != n)) {
        int val = min(rows[cur_r], cols[cur_c]);
        // cerr << cur_r << '/' << rows[cur_r] << ' ' << cur_c << '/' << cols[cur_c] << ' ' << val << endl;
        rows[cur_r] -= val;
        cols[cur_c] -= val;
        solution[cur_r][cur_c] = val;
        while ((cur_r != n) && (rows[cur_r] == 0))
            cur_r++;
        while ((cur_c != n) && (cols[cur_c] == 0))
            cur_c++;
    }

    if ((cur_r != n) || (cur_c != n))
        cout << -1 << endl;
    else {
        for (int i=0; i<n-1; i++) {
            for (int j=0; j<n-1; j++) {
                cout << solution[i][j] << ' ';
            }
            cout << solution[i][n-1] << endl;
        }
        for (int j=0; j<n-1; j++) {
            cout << solution[n-1][j] << ' ';
        }
        cout << solution[n-1][n-1];
    }

    return 0;
}
