#include <iostream>
#include <vector>
#include <algorithm>

#define X first
#define Y second

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

int main() {

    int x;
    cin >> x;

    vector<pll> trees(x);
    vector<pll> s1(x);
    vector<pll> s2;
    for (int i=0; i<x; i++) {
        cin >> trees[i].X >> trees[i].Y;
        s1[i].X = trees[i].X - trees[i].Y;
        s1[i].Y = i;
    }

    sort(s1.begin(), s1.end());
    ll cur = 1;
    int ptr = 0;
    vector<int> final(x, -1);
    while (ptr < s1.size() || s2.size()) {
        while (ptr < s1.size() && cur >= s1[ptr].X) {
            int i = s1[ptr++].Y;
            s2.insert(upper_bound(s2.begin(), s2.end(), pll(-(trees[i].X + trees[i].Y), i)), {-(trees[i].X + trees[i].Y), i});
        }
        if (!s2.size()) {
            cur = max(s1[ptr].X, cur);
            continue;
        }
        final[s2[s2.size()-1].Y] = cur++;
        s2.pop_back();
    }

    for (int i=0; i<x; i++) {
        cout << final[i];
        if (i == x-1) { cout << endl; }
        else { cout << " "; }
    }

    return 0;
}
