// MuMonash

// Superhot AC
// Iterative
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
#define me (*this)
#define debug(a) cerr << #a << " = " << (a) << endl;
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
typedef long long ll;
typedef pair<int, int> pii;

#define UNREACHABLE -1
#define SOLVED -2

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int num_e, num_l, num_r;
    cin >> num_e >> num_l >> num_r >> ws;

    int enemies[max(num_e, 1)];
    int left_stack[max(num_l, 1)];
    int right_stack[max(num_r, 1)];

    for (int e=0; e<num_e; e++) {
        cin >> enemies[e];
    }
    cin >> ws;
    for (int l=0; l<num_l; l++) {
        cin >> left_stack[l];
    }
    cin >> ws;
    for (int r=0; r<num_r; r++) {
        cin >> right_stack[r];
    }
    cin >> ws;

    pii DP[num_l+1][num_r+1];

    bool solved = (num_e == 0);

    DP[0][0].x = 0;
    DP[0][0].y = 0;

    for (int i=1; i<num_l+1 + num_r+1; i++) {
        for (int j=0; j<=i; j++) {
            int a = i-j;
            int b = j;
            if (a <= num_l && b <= num_r) {
                DP[a][b].x = UNREACHABLE;
                DP[a][b].y = 0;
                if (a-1 >= 0) {
                    if (DP[a-1][b].x != UNREACHABLE) {
                        if (DP[a-1][b].x == SOLVED) {
                            continue;
                        }
                        int hp = enemies[DP[a-1][b].x] - DP[a-1][b].y;
                        if (left_stack[a-1] <= hp) {
                            hp -= left_stack[a-1];
                            if (hp == 0) {
                                DP[a][b].x = DP[a-1][b].x + 1;
                                DP[a][b].y = 0;
                                if (DP[a][b].x == num_e) {
                                    solved = true;
                                    DP[a][b].x = SOLVED;
                                }
                            } else {
                                DP[a][b].x = DP[a-1][b].x;
                                DP[a][b].y = enemies[DP[a-1][b].x] - hp;
                            }
                        }
                    }
                }
                if (b-1 >= 0) {
                    if (DP[a][b-1].x != UNREACHABLE) {
                        if (DP[a][b-1].x == SOLVED) {
                            continue;
                        }
                        int hp = enemies[DP[a][b-1].x] - DP[a][b-1].y;
                        if (right_stack[b-1] <= hp) {
                            hp -= right_stack[b-1];
                            if (hp == 0) {
                                DP[a][b].x = DP[a][b-1].x + 1;
                                DP[a][b].y = 0;
                                if (DP[a][b].x == num_e) {
                                    solved = true;
                                    DP[a][b].x = SOLVED;
                                }
                            } else {
                                DP[a][b].x = DP[a][b-1].x;
                                DP[a][b].y = enemies[DP[a][b-1].x] - hp;
                            }
                        }
                    }
                }
            }
        }
    }

    cout << (solved ? "YES" : "NO") << endl;

    return 0;
}
