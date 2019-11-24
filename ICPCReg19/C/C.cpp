// MuMonash

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define X first
#define Y second

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;

struct Person {
    int deg;
    vi neighbours;
};

int main() {

    vector<Person> vp;
    int n;
    cin >> n;

    for (int i=0; i<n; i++) {
        int d;
        cin >> d;
        vp.push_back({d});
        for (int j=0; j<d; j++) {
            int a;
            cin >> a;
            vp[vp.size() - 1].neighbours.push_back(a-1);
        }
    }

    if (n == 1)
        if (vp[0].deg == 0) { cout << "Yes" << endl; }
        else { cout << "No" << endl; }
    else {
    vi deg2;
    for (int i=0;i<n;i++) {
        if (vp[i].deg == 2) deg2.push_back(i);
    }
    if (deg2.size() != 4 ) { cout << "No" << endl; }
    else {
    vi par(n, -1);
    vi dist(n, -1);
    queue<pii> q;
    q.push({-1, deg2[0]});
    dist[deg2[0]] = 0;
    while (q.size() > 0) {
        pii e = q.front(); q.pop();
        if (par[e.Y] != -1) continue;
        par[e.Y] = e.X;
        dist[e.Y] = e.X == -1 ? 0 : dist[e.X] + 1;
        for (auto n: vp[e.Y].neighbours) q.push({e.Y, n});
    }
    int m = max(max(dist[deg2[1]], dist[deg2[2]]), dist[deg2[3]]);
    bool bad = false;
    for (int i=0; i<n; i++) if (dist[i] == -1) { bad = true; break; }
    if (bad) { cout << "No" << endl; }
    else {
    if (dist[deg2[1]] == m) {
        int a = deg2[1];
        deg2[1] = deg2[3];
        deg2[3] = a;
    }
    vi top_row(1, deg2[1]);
    bad = false;
    while (top_row[top_row.size()-1] != deg2[0]) {
        top_row.push_back(par[top_row[top_row.size()-1]]);
        if (vp[top_row[top_row.size()-1]].deg != 3 && top_row[top_row.size()-1] != deg2[0]) {
            bad = true;
            break;
        }
    }
    if (n % top_row.size()) { bad = true; }
    if (bad) { cout << "No" << endl; }
    else {
    // Check all of the neighbours in the top row.
    bad = false;
    for (int i=0; i<top_row.size()-1; i++) {
        bool bad_check = true;
        for (auto p: vp[top_row[i+1]].neighbours) {
            if (p == top_row[i]) bad_check = false;
        }
        bad |= bad_check;
    }
    if (bad) { cout << "No" << endl; }
    else {
    // Start adding each row.
    bad = false;
    vector<bool> matched(n, false);
    for (auto a: top_row) matched[a] = true;
    // cerr << top_row.size() << endl;
    for (int i=0; i<(n/top_row.size())-1; i++) {
        vi next_row;
        for (int i=0; i<top_row.size(); i++) if (!bad) {
            int next = -1;
            int count = 0;
            for (auto p: vp[top_row[i]].neighbours) if (!matched[p]) {
                count++;
                next = p;
            }
            if (count != 1) { bad = true; break; }
            next_row.push_back(next);
            matched[next] = true;
            if (i != 0) {
                bool found1 = false;
                bool found2 = false;
                for (auto n: vp[next_row[i-1]].neighbours) if (n == next) found1 = true;
                for (auto n: vp[next].neighbours) if (n == next_row[i-1]) found2 = true;
                if (!(found1 && found2)) { bad = true; break; }
            }
        }
        top_row = next_row;
    }
    if (bad) { cout << "No" << endl; }
    else {
    // Last: Check degrees.
    for (int i=1; i<top_row.size()-1; i++) if (vp[top_row[i]].deg != 3) { bad = true; break; }
    if (vp[top_row[0]].deg != 2) { bad = true; }
    if (vp[top_row[top_row.size()-1]].deg != 2) { bad = true; }
    if (bad) { cout << "No" << endl; }
    else { cout << "Yes" << endl; }
    }
    }
    }
    }
    }
    }

    return 0;
}
