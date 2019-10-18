#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <string>

#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)

using namespace std;

typedef long long ll;

int main()
{
    int n;
    cin >> n;
    vector<int> index[100011];
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        index[x].pb(i);
    }

    int res[100001], m = n;
    for (int i = 1; i <= n; i++)
    {
        if (index[i].size() == 0) continue;
        for (int j = 0; j < index[i].size(); j++)
            res[index[i][j]] = m--;
    }

    for (int i = 0; i < n; i++)
        cout << res[i] << ' ';
    cout << endl;
}
