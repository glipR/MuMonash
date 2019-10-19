#include <iostream>
#include <cmath>

using namespace std;


typedef long long bigint;

char solve(bigint b, bigint x) {
    bigint extra = 1;
    bigint current = 0;
    bigint total = 0;
    int iterations = 0;
    while (total <= x) {
        iterations++;
        extra *= b;
        current = b * current + extra;
        total += current;
    }
    char strings[iterations];
    bigint total_negative = 0;
    bigint mult = 1;
    for (bigint y=0; y<iterations; y++) {
        mult *= b;
        int h = (total - total_negative - x) / (current / mult) - 1;
        bigint negative = ((bigint)h+1) * (bigint)(current / mult);
        if (total - (total_negative + negative) <= x) h--;
        total_negative += ((bigint)h+1) * (bigint)(current / mult);
        strings[y] = ((char)('a' + (int)(b - h - 2)));
    }
    return strings[(x - (total - total_negative)) + iterations];
}

int main() {

    int t;
    cin >> t;

    for (int i=0; i<t; i++) {
        bigint b, x;
        cin >> b >> x;
        cout << solve(b, x) << endl;
    }

    return 0;
}
