#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

int main()
{
    string s;
    cin >> s;
    int counts[100001];
    int cur = 0;
    counts[0] = cur;

    int minIndex = 0, maxIndex = 0;

    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == 'R') cur++;
        else if (s[i] == 'B') cur--;
        counts[i+1] = cur;
        if (counts[i+1] < counts[minIndex])
            minIndex = i + 1;
        if (counts[i+1] > counts[maxIndex])
            maxIndex = i + 1;
    }

    cout << min(minIndex, maxIndex) + 1 << ' ' << max(minIndex, maxIndex) << endl;
}
