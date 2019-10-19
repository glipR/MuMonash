#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>

#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)

using namespace std;

typedef pair<int, int> pii;

bool can_merge(string s, int start, pii p)
{
    int middle = p.first, end = p.second;
    int left = start, right = middle;
    while (left < middle && right < end)
    {
        if (s[left] > s[right]) return false;
        if (s[left] < s[right]) return true;
        left++; right++;
    }
    if (left == middle) return true;
    return false;
}

int main()
{
    int n;
    cin >> n;
    for (int q = 0; q < n; q++)
    {
        string s;
        cin >> s;
        vector<int> segs;
        int i = s.length() - 1;
        while (i > 0)
        {
            if (s[i-1] <= s[i])
                i--;
            else {
                segs.pb(i);
                i--;
            }
        }
        segs.pb(0);
        reverse(segs.begin(), segs.end());
        stack<pii> S;
        i = segs.size() - 1;
        S.push(mp(segs[i], s.length()));
        i--;
        while (i >= 0)
        {
            pii top = S.top();
            if (can_merge(s, segs[i], top))
            {
                S.pop();
                S.push(mp(segs[i], top.second));
            }
            else
            {
                S.push(mp(segs[i], top.first));
            }
            i--;
        }
        if (S.size() == 1 && S.top().first == 0 && S.top().second == s.length())
            cout << 1;
        else cout << 0;
    }
    cout << endl;
}
