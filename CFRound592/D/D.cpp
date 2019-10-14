#include <iostream>
#include <vector>

using namespace std;

// If the tree is anything but a path, impossible.
// So assert the degree of every node is 1 or 2
// Then calculate the cost of going:
// 1, 2, 3, 1, 2, 3
// 1, 3, 2, 1, 3, 2
// ... Every other permutation of 1, 2, 3.

typedef long long ll;

struct Tree {
    int n;
    vector<vector<int>> adj;
    vector<vector<ll>> colours;
    vector<int> choice;

    Tree(int n): n(n) {
        adj.assign(n, vector<int>());
        colours.assign(n, vector<ll>());
        choice.assign(n, -1);
    }

    void add_edge(int a, int b) {
        adj[a].push_back(b), adj[b].push_back(a);
    }

    void add_color(int u, ll c) {
        colours[u].push_back(c);
    }

    bool is_path() {
        for (auto v: adj) {
            if (v.size() > 2) {
                return false;
            }
        }
        return true;
    }

    int first() {
        for (int i=0; i<n; i++) {
            if (adj[i].size() == 1) {
                return i;
            }
        }
    }

    ll score(int i, int j, int k, ll cur_best) {
        // cerr << i << ' ' << j << ' ' << k << endl;
        ll current_score = 0;
        int current = first();
        vector<int> popped;
        for (int l=0; l<n; l++) {
            if (l % 3 == 0) current_score += colours[current][i];
            if (l % 3 == 1) current_score += colours[current][j];
            if (l % 3 == 2) current_score += colours[current][k];
            int old = current;
            for (auto v: adj[old]) {
                if (adj[old].size() == 1 || popped[popped.size() - 1] != v) {
                    current = v;
                    break;
                }
            }
            popped.push_back(old);
        }
        if (current_score < cur_best || cur_best == -1) {
            int current2 = first();
            vector<int> popped2;
            for (int l=0; l<n; l++) {
                if (l % 3 == 0) choice[current2] = i;
                if (l % 3 == 1) choice[current2] = j;
                if (l % 3 == 2) choice[current2] = k;
                int old = current2;
                for (auto v: adj[old]) {
                    if (adj[old].size() == 1 || popped2[popped2.size() - 1] != v) {
                        current2 = v;
                        break;
                    }
                }
                popped2.push_back(old);
            }
            return current_score;
        }
        return cur_best;
    }
};

int main() {

    int n;
    cin >> n;

    ll colours[n][3];
    Tree t = Tree(n);

    for (int i=0; i<3; i++) {
        for (int j=0; j<n; j++) {
            cin >> colours[j][i];
            t.add_color(j, colours[j][i]);
        }
    }

    for (int i=0; i<n-1; i++) {
        int a, b;
        cin >> a >> b;
        t.add_edge(a-1, b-1);
    }

    if (t.is_path()) {
        ll m = t.score(0, 1, 2, -1);
        m = t.score(0, 2, 1, m);
        m = t.score(1, 0, 2, m);
        m = t.score(1, 2, 0, m);
        m = t.score(2, 0, 1, m);
        m = t.score(2, 1, 0, m);
        cout << m << endl;
        for (int i=0; i<n; i++) {
            if (i != 0) cout << ' ';
            cout << t.choice[i]+1;
        }
        cout << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}
