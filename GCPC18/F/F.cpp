// MuMonash
// WA

#include <bits/stdc++.h>

#define pb(a) push_back(a)

using namespace std;

const int MAXN = 100001;

struct Pair {
	int a, b;
	Pair() { a = -1; b = -1; }
	Pair(int x, int y) { a = x; b = y; }
};

Pair winner[2000001];
int indexx[MAXN];

int main()
{
	int n;
	cin >> n;
	int power[MAXN];
	memset(indexx, -1, sizeof(indexx));
	int firstOne = -1, secondOne = -1;
	for (int i = 0; i < n; i++)
	{
		cin >> power[i];
		if (power[i] == 1)
		{
			if (firstOne == -1)
				firstOne = i;
			else secondOne = i;
		}

		indexx[power[i]] = i;
	}

	if (firstOne != -1 && secondOne != -1)
	{
		cout << firstOne + 1 << " " << secondOne + 1 << endl;
		return 0;
	}

	int l = 1, r = 1;
	while (l <= 1e6 + 100 && r <= 1e6 + 100)
	{
		if (winner[l].a == -1)
			winner[l].a = r;
		else winner[l].b = r;

		if (winner[r].a == -1)
			winner[r].a = l;
		else winner[r].b = l;

		if (l < r)
			l += r;
		else r += l;
	}

	for (int i = 0; i < n; i++)
	{
		if (winner[power[i]].a != -1)
		{
			int id = winner[power[i]].a;
			if (indexx[id] != -1 && indexx[id] != i)
			{
				int index1 = i, index2 = indexx[id];
				if (power[index1] > power[index2]) swap(index1, index2);
				cout << index1 + 1 << ' ' << index2 + 1 << endl;
				return 0;
			}
		}
		if (winner[power[i]].b != -1)
		{
			int id = winner[power[i]].b;
			if (indexx[id] != -1 && indexx[id] != i)
			{
				int index1 = i, index2 = indexx[id];
				if (power[index1] > power[index2]) swap(index1, index2);
				cout << index1 + 1 << ' ' << index2 + 1 << endl;
				return 0;
			}
		}
	}
	cout << "impossible" << endl;
}
