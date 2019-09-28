// MuMonash
// AC

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1001;

int x[MAXN];
int y[MAXN];
int n;

int solve(int days, int start)
{
	if (start == n)
		return 0;

	if (x[start] + days > y[start])
		return 0;

	int equal = max(0, y[start] - (x[start] + days));

	return min(equal + 1, equal + solve(days + equal, start + 1));
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> x[i];
	for (int i = 0; i < n; i++)
		cin >> y[i];

	cout << solve(0, 0) << endl;
}
