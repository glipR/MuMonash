// MuMonash

#include <cstdio>
#include <string>
#include <iostream>
#include <list>
#include <map>
#include <cmath>
#include <vector>
#include <limits>
#include <algorithm>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
typedef vector<ll> vi;
typedef vector<vector<ll> > vvi;

const ll MAX_M = 20;
const ll MAX_N = 200;
const ll MAX_DIFF = 450;
const ll MAX_ADD = 220;
const ll UNKNOWN = 100000;
const ll IMPOSSIBLE = 200000;

pair<pair<ll, ll>, bool> DP[MAX_N+1][MAX_DIFF][MAX_M+1];

int n, m;
vi p, d;

pair<pair<ll, ll>, bool> solve(ll i, ll j, ll k) {
    if (DP[i][j][k].first.first != UNKNOWN) return DP[i][j][k];
    if (i == n) {
        // At the end without selecting m jurers is impossible.
        if (k != m)
            return {{IMPOSSIBLE, IMPOSSIBLE}, false};
        // Else return our current diff.
        return {{j - MAX_ADD, 0}, false};
    }
    // We are looking at some jurer.
    // If k == m, we cannot select them
    if (k == m) {
        DP[i][j][k] = solve(i+1, j, k);
        DP[i][j][k].second = false;
        return DP[i][j][k];
    }
    // Try using or ignoring the candidate
    auto res1 = solve(i+1, j, k);
    res1.second = false;
    auto res2 = solve(i+1, j + p[i] - d[i], k+1);
    res2.second = true;
    res2.first.second = res2.first.second + p[i] + d[i];
    if (res1.first.first == IMPOSSIBLE) {
        DP[i][j][k] = res2;
    } else if (res2.first.first == IMPOSSIBLE) {
        DP[i][j][k] = res1;
    } else {
        // Both possible, select the one that is closer.
        if (abs(res1.first.first) < abs(res2.first.first)) {
            DP[i][j][k] = res1;
        } else if (abs(res2.first.first) < abs(res1.first.first)) {
            DP[i][j][k] = res2;
        } else if (res1.first.second > res2.first.second) {
            DP[i][j][k] = res1;
        } else if (res2.first.second > res1.first.second) {
            DP[i][j][k] = res2;
        } else {
            // Both are equal, pick the one where we choose this jurer for best alphanumeric.
            DP[i][j][k] = res2;
        }
    }
    return DP[i][j][k];
    
}

int main() {

    int a=1;
    while (1) {
        cin >> n >> m;
        if (n == 0) break;
        p.clear(); d.clear();
        for (int i=0; i<n; i++) {
            ll rp, rd;
            cin >> rp >> rd;
            p.push_back(rp); d.push_back(rd);
        }
        for (int i=0; i<=n; i++) {
            for (int j=0; j<MAX_DIFF; j++) {
                for (int k=0; k<=m; k++) {
                    DP[i][j][k] = {{UNKNOWN, 0}, false};
                }
            }
        }
        auto res = solve(0, MAX_ADD, 0);
        cout << "Jury #" << (a++) << endl;
        cout << "Best jury has value " << (res.first.first + res.first.second) / 2 << " for prosecution and value " << (res.first.second - res.first.first) / 2 << " for defence:" << endl;
        int i = 0;
        int j = MAX_ADD;
        int k = 0;
        while (k < m) {
            auto r = solve(i, j, k);
            if (r.second) {
                cout << " " << p[i] << " " << d[i] << endl;
                i ++;
                j = j + p[i] - d[i];
                k ++;
            } else {
                i ++;
            }
        }
        cout << endl;
    }


    return 0;
}