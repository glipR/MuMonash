#include <iostream>

using namespace std;

int main()
{
    int a[4];
    int m1 = 1000000, m2 = -10, sum = 0;
    for (int i = 0; i < 4; i++)
    {
        float x; cin >> x; a[i] = x * 100;
        if (a[i] > m2) m2 = a[i];
        if (a[i] < m1) m1 = a[i];
        sum += a[i];
    }

    int target; float x; cin >> x; target = 300 * x;
    if (sum - m1 <= target)
        cout << "infinite" << endl;
    else if (sum - m2 > target)
        cout << "impossible" << endl;
    else
    {
        // printf("%.2f\n", (1.0 * (target - (sum - m1 - m2)) / 100.0));
        
        for (int ans = m2; ans >= m1; ans--)
            if (sum - m1 - m2 + ans <= target)
            {
                printf("%.2f\n", (1.0 * ans) / 100.0);
                return 0;
            }
        cout << "impossible" << endl;
        
    }
}
