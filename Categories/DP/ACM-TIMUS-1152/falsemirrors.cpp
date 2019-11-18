// MuMonash

#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> balconies;
vector<int> damage;
vector<int> dp;

int soln(int mask) {
  if (dp[mask] != -1) { return dp[mask]; }

  int best = -1;

  for (int i=0; i<n; ++i) {
    int new_mask = mask;

    for (int j=0; j<3; ++j) {
      int new_balcony = (i+j) % n;
      int new_bit = 1 << new_balcony;
      new_mask |= new_bit;
    }

    if (new_mask == mask) { continue; }

    int this_soln = soln(new_mask) + damage[new_mask];

    if (best == -1) {
      best = this_soln;
    } else {
      best = min(best, this_soln);
    }
  }

  if (best == -1) { best = 0; }

  dp[mask] = best;
  return best;
}

int main() {
  cin >> n;

  for (int i=0; i<n; ++i) {
    int x;
    cin >> x;
    balconies.push_back(x);
  }

  damage.reserve(1<<n);
  dp.reserve(1<<n);

  for (int i=0; i<(1<<n); ++i) {
    dp[i] = -1;
    damage[i] = 0;

    // If we have the ith balcony not destroyed, add its damage
    for (int j=0; j<n; ++j) {
      int ith_balcony_destroyed = (i & (1<<j));
      if (ith_balcony_destroyed == 0) {
        damage[i] += balconies[j];
      }
    }
  }

  dp[(1<<n) - 1] = 0;

  cout << soln(0) << endl;

  return 0;
}
