#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef long double ld;

int main() {

    int n, k;
    cin >> n >> k;

    ld probs[n];
    for (int i=0; i<n; i++) { cin >> probs[i]; }

    ld final_prob[n];

    // For each monster
    for (int i=0; i<n; i++) {
        // cerr << "Checking " << i << endl;
        // Generate the probability of n-k previous not chosen.
        ld prob = 1;
        for (int j=0; j<n-k; j++) {
            prob *= (ld)(n - k - j);
            prob /= (ld)(n - j);
        }
        ld sum = probs[i];
        int j = (i-(n-k));
        if (j < 0) j += n;
        for (; i != j; j = (j+1) % n) {
            sum += probs[j];
        }
        // cerr << "Current sum is " << sum << endl;
        // cerr << "Current prob is " << prob << endl;
        final_prob[i] = prob * sum;
        for (int j=1; j<=n-k; j++) {
            int index = (i - (n - k) + j - 1) % n;
            if (index < 0) index += n;
            sum -= probs[index];
            prob = prob * (k - 2 + j) / ((ld) j);
            // cerr << "New sum is " << sum << endl;
            // cerr << "New prob is " << prob << endl;
            final_prob[i] += prob * sum;
        }
    }

    cout << setprecision(8) << fixed;
    cout << final_prob[0];
    for (int i=1; i<n; i++) { cout << " " << final_prob[i]; }
    cout << endl;

    return 0;
}
