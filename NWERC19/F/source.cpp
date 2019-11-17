#include <iostream>
#include <vector>
#include <map>
#include <queue>

#define pb(a) push_back(a)

using namespace std;

map<int, int> nom;

struct Edge {
    int v;
    int num;
    Edge(int a, int b) : v(a), num(b) {}
};

const int MAXN = 200001;

vector<Edge> list[MAXN];

struct Triple {
    int a, b, c;
    Triple (int A, int B, int C) : a(A), b(B), c(C) {}
};

bool mark[MAXN];

int main()
{
    int n; cin >> n;
    for (int i = 0; i < n; i++)
    {
        int m; cin >> m;
        for (int j = 0; j < m; j++)
        {
            int x; cin >> x;
            if (nom.find(x) == nom.end())
                nom[x] = i;
            else {
                list[i].pb(Edge(nom[x], x));
                list[nom[x]].pb(Edge(i, x));
            }
        }
    }

    queue<int> q;
    q.push(0);
    mark[0] = 1;
    vector<Triple> ans;

    while (!q.empty())
    {
        int front = q.front(); q.pop();
        for (int i = 0; i < list[front].size(); i++)
        {
            Edge edge = list[front][i];
            if (mark[edge.v]) continue;
            mark[edge.v] = 1;
            q.push(edge.v);
            ans.pb(Triple(front + 1, edge.v + 1, edge.num));
        }
    }
    
    if (ans.size() == n-1)
    {
        for (auto t : ans)
            cout << t.a << ' ' << t.b << ' ' << t.c << endl;
    }
    else cout << "impossible" << endl;

}
