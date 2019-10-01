// MuMonash

#include <cmath>
#include <iostream>

#define MAX_LEN 19

using namespace std;

typedef long long ll;

struct Tree {

    Tree* children[10];
    int depth;
    int count;

    Tree(int d): depth(d), count(0) {
        for (int i=0; i<10; i++) {
            children[i] = NULL;
        }
    };

    void add_num(string num) {
        count += 1;
        if (depth == MAX_LEN) return;
        int idx = (int)(num[depth]) - (int)'0';
        // cerr << num[depth] << ' ' << idx << endl;
        if (children[idx] == NULL) {
            children[idx] = new Tree(depth+1);
        }
        children[idx]->add_num(num);
    }

    // Default the second arg to true.
    ll best_sum(string num, bool matching) {
        if (depth == MAX_LEN) {
            return (matching && (count == 1)) ? -1 : 0;
        }
        int idx = (int)(num[depth]) - (int)'0';
        // cerr << num[depth] << ' ' << idx << endl;
        for (int s=9; s>=0; s--) {
            int j = (s - idx);
            if (j < 0) j+= 10;
            // cerr << s << ' ' << idx << ' ' << j << endl;
            if (children[j] != NULL) {
                ll little_sum = children[j] -> best_sum(num, matching && (j == idx));
                if (little_sum != -1)
                    return s * powl(10, MAX_LEN - depth - 1) + little_sum;
            }
        }
        return -1;
    }

};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n;
    cin >> n >> ws;

    Tree root(0);

    string nums[n];
    for (int i=0; i<n; i++) {
        cin >> nums[i] >> ws;
        for (int j=nums[i].length(); j<MAX_LEN; j++) {
            nums[i].insert(0, 1, '0');
        }
        root.add_num(nums[i]);
    }

    ll best = -1;
    for (int i=0; i<n; i++) {
        best = max(best, root.best_sum(nums[i], true));
    }

    cout << best << endl;

    return 0;
}
