#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> vi;

int main() {

    int n, m;

    cin >> n >> m;

    vi best(n);
    vi worst(n);
    vi current(n);
    vi at_loc(n);
    for (int i=0; i<n; i++) {
        best[i] = i;
        worst[i] = i;
        current[i] = i;
        at_loc[i] = i;
    }

    for (int i=0; i<m; i++) {
        int post;
        cin >> post;
        post--;
        if (current[post] == 0) continue;
        current[post]--;
        current[at_loc[current[post]]]++;
        swap(at_loc[current[post]+1], at_loc[current[post]]);
        best[post] = min(best[post], current[post]);
        best[at_loc[current[post]+1]] = min(best[at_loc[current[post]+1]], current[at_loc[current[post]+1]]);
        worst[post] = max(worst[post], current[post]);
        worst[at_loc[current[post]+1]] = max(worst[at_loc[current[post]+1]], current[at_loc[current[post]+1]]);
    }

    for (int i=0; i<n; i++) {
        cout << best[i]+1 << " " << worst[i]+1 << endl;
    }

    return 0;
}
