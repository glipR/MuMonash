#include <iostream>
#include <vector>
#include <algorithm>

#define pb(a) push_back(a)

using namespace std;

const int MAXN = 200;

struct Task {
    int rating;
    int change;
    Task (int a, int b) : rating(a), change(b) {}
    Task () {}
};

bool compareRating(const Task& a, const Task& b) { return a.rating < b.rating; }
bool compareBoth(const Task& a, const Task& b) { return a.rating - a.change < b.rating - b.change; }

int dp[MAXN][60010];

int main()
{
    int n, r;
    cin >> n >> r;

    vector<Task> pos, neg;
    for (int i = 0; i < n; i++) 
    {
        int a, b; cin >> a >> b;
        if (b > 0) pos.pb(Task(a, b));
        else neg.pb(Task(a,-1*b));
    }

    sort(pos.begin(), pos.end(), compareRating);
    for (int i = 0; i < neg.size(); i++) neg[i].rating = max(neg[i].rating, neg[i].change);
    sort(neg.begin(), neg.end(), compareBoth);

    int cnt = 0;

    for (int i = 0; i < pos.size(); i++) 
        if (r >= pos[i].rating)
        {
            r += pos[i].change;
            cnt++;
        }

    for (int i = 0; i <= 60000; i++)
        dp[0][i] = cnt;

    for (int i = 1; i <= neg.size(); i++)
    {
        for (int j = 0; j <= 60000; j++)
        {
            dp[i][j] = dp[i-1][j];
            if (j >= neg[i-1].rating && j - neg[i-1].change >= 0)
                dp[i][j] = max(dp[i][j], 1 + dp[i-1][j - neg[i-1].change]);
        }
    }

    cout << dp[neg.size()][r] << endl;

}
