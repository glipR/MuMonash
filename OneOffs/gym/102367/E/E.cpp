// MuMonash
// This doesn't quite work.
// Not sure how to approach.

#include <cmath>
#include <iostream>

using namespace std;

#define MAX_BIN 12
#define MOD 1000000007

struct BinRep {
    bool integers[MAX_BIN];
    int count;

    BinRep(): count(0) {}

    void from_int(int n) {
        for (int i=0; i<MAX_BIN; i++) integers[i] = false;
        for (int i=0; (1 << i)<=n; i++) {
            if ((1 << i) & n) integers[i] = true;
        }
    }

    int diff(int dif) {
        int res=0;
        for (int i=0; i<MAX_BIN; i++) {
            if ((1 << i) & dif) {
                res += (1-integers[i]) * (1 << i);
            } else {
                res += (integers[i]) * (1 << i);
            }
        }
        return res;
    }
};

long long factorial(int n) {
    if (n == 0) return 1;
    if (n == 1) return 1;
    return n * factorial(n-1);
}

int main() {

    BinRep rep[1001];
    for (int i=0; i<=1000; i++) rep[i].from_int(i);

    int n;
    cin >> n >> ws;

    for (int x=0; x<n; x++) {
        int num;
        cin >> num >> ws;
        rep[num].count ++;
    }

    long long possible_options = 1;

    for (int diff=0; diff<1024; diff++) {
        for (int i=0; i<=1000; i++) {
            if (rep[i].count > 0) {
                int val = rep[i].diff(diff);
                if ((0 <= val) && (val <= 1000))
                if (rep[val].count > 0) {
                    // We can use both.
                    int decrease = min(rep[val].count, rep[i].count);
                    if (i == val) {
                        decrease = rep[i].count / 2;
                    };
                    cerr << i << ' ' << val << ' ' << diff << endl;
                    possible_options *= factorial(decrease);
                    possible_options %= MOD;
                    rep[i].count -= decrease;
                    rep[val].count -= decrease;
                }
            }
        }
    }

    cout << possible_options << endl;

    return 0;
}
