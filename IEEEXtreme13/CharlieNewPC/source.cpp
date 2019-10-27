#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#define pb(a) push_back(a)

using namespace std;

int b, n;
int k[11];

vector<int> options[11];
int current_option[11];

int optimal(int budget, int mask)
{
    int backMask = mask;
    int p = 0;
    int best = budget;
    while (backMask > 0)
    {
        if (backMask % 2)
        {
            mask -= (1 << p);
            if (current_option[p] + 1 < k[p])
            {
                int newBudget = budget - options[p][current_option[p] + 1] + options[p][current_option[p]];
                if (newBudget >= 0)
                {
                    current_option[p]++;
                    best = min(best, optimal(newBudget, mask));
                    current_option[p]--;
                }
            }
            best = min(best, optimal(budget, mask));
        }
        backMask /= 2;
        p++;
    }
    return best;
}

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        cin >> b >> n;
        int backB = b;
        for (int i = 0; i < n; i++)
            cin >> k[i];
        for (int i = 0; i < n; i++)
        {
            options[i].clear();
            for (int j = 0; j < k[i]; j++)
            {
                int x;
                cin >> x;
                options[i].pb(x);
            }
            sort(options[i].begin(), options[i].end());
            b -= options[i][0];
            current_option[i] = 0;
        }
        if (b < 0)
            cout << 0 << endl;
        else cout << backB-optimal(b, (1 << n) - 1) << endl;
    }
}
