#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <cstring>

#define pb(a) push_back(a)

using namespace std;

typedef long long ll;

// An edge between vertext `index` and `dest` with weight `weight`
struct Edge {
	int index;
	int dest;
	ll weight;

	Edge () {}
	Edge (int i, int d, ll w) { index = i; weight = w; dest = d; }

	bool const operator < (const Edge& e) const
	{
		return weight < e.weight;
	}
};

struct DisjointSet {
	int *parent;
	int *size;

	DisjointSet (int N)
	{
		parent = new int[N];
		size = new int[N];
		for (int i = 0; i < N; i++)
		{
			parent[i] = i;
			size[i] = 1;
		}
	}

	int root(int node)
	{
		int res = node;
		while (parent[res] != res)
			res = parent[res];

		while (node != res)
		{
			int oldParent = parent[node];
			parent[node] = res;
			node = oldParent;
		}

		return res;
	}

	int unionn(int a, int b)
	{
		int rootA = root(a);
		int rootB = root(b);
		if (rootA == rootB) return 0;
		if (size[rootA] > size[rootB])
			swap(rootA, rootB);
		parent[rootA] = rootB;
		size[rootB] += size[rootA];
		return 1;
	}
};

const int MAXN = 510;
int n;
int group[MAXN], groupsCnt = 0;
ll groupWeight[MAXN];
vector<Edge> in_vec[MAXN], out_vec[MAXN];

void prim(int node)
{
	ll res = 0;

	bool covered[MAXN];
	memset(covered, false, sizeof(covered));
	multiset<Edge> edges;

	covered[node] = 1;
	for (int i = 0; i < in_vec[node].size(); i++)
		edges.insert(in_vec[node][i]);

	while (!edges.empty())
	{
		Edge front = *edges.begin();
		if (covered[front.index])
		{
			edges.erase(edges.begin());
			continue;
		}

		edges.erase(edges.begin());
		covered[front.index] = 1;
		res += front.weight;

		for (int i = 0; i < in_vec[front.index].size(); i++)
		{
			if (covered[in_vec[front.index][i].index]) continue;
			edges.insert(in_vec[front.index][i]);
		}
	}
	groupWeight[group[node]] = res;
}

ll kruskal()
{
	ll res = 0;
	DisjointSet ds(groupsCnt);
	multiset <Edge> edges;
	for (int i = 0; i < groupsCnt; i++)
		for (int j = 0; j < out_vec[i].size(); j++)
			edges.insert(out_vec[i][j]);

	while (!edges.empty())
	{
		Edge front = *edges.begin();
		if (ds.unionn(front.index, front.dest) == 0)
		{
			edges.erase(edges.begin());
			continue;
		}
		res += front.weight;
	}

	for (int i = 0; i < groupsCnt; i++)
		if (ds.root(i) != ds.root(0))
			return -1;

	return res;
}

void groupNodes()
{
	memset(group, -1, sizeof(group));
	for (int i = 0; i < n; i++)
	{
		if (group[i] == -1)
		{
			group[i] = groupsCnt++;
			queue<int> q;
			q.push(i);
			while (!q.empty())
			{
				int front = q.front();
				q.pop();
				for (int j = 0; j < in_vec[front].size(); j++)
				{
					int nei = in_vec[front][j].index;
					if (group[nei] != -1) continue;
					q.push(nei);
					group[nei] = group[front];
				}
			}
		}
	}
}

int mat[MAXN][MAXN];
int groupsMat[MAXN][MAXN];

int main()
{
	cin >> n;
	for (int i = 0; i < n-1; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			int x;
			cin >> x;
			if (x < 0)
			{
				in_vec[i+1].pb(Edge(j, i+1, -1*x));
				in_vec[j].pb(Edge(i+1, j, -1*x));
			} else if (x != 0)
			{
				mat[i+1][j] = x;
				mat[j][i+1] = x;
			}
		}
	}
	
	groupNodes();

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (mat[i][j] != 0)
				groupsMat[group[i]][group[j]] = 
					groupsMat[group[i]][group[j]] == 0 ? mat[i][j] :
						min(mat[i][j], groupsMat[group[i]][group[j]]);

	
	memset(groupWeight, -1, sizeof(groupWeight));
	for (int i = 0; i < n; i++)
		if (groupWeight[group[i]] == -1)
			prim(i);
	
	for (int i = 0; i < groupsCnt; i++)
		for (int j = 0; j < groupsCnt; j++)
			if (groupsMat[i][j] > 0)
				out_vec[i].pb(Edge(j, i, groupsMat[i][j] + groupWeight[i] + groupWeight[j]));

	ll res = kruskal();
	if (res == -1)
		cout << "impossible" << endl;
	else cout << res << endl;

}
