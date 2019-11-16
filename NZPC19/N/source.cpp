#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <queue>
#include <algorithm>

#define pb(a) push_back(a)

using namespace std;
    
struct Node {
    int out;
    vector<int> in;

    bool in_circle;
    int circle_id;
    int circle_pos;
    int circle_size;
    
    Node () {
        in_circle = false;
    }
};

const int MAXN = 100001;
int n;

Node nodes[MAXN];

bool mark[MAXN];
bool mark2[MAXN];

void mark_circle(int x, int id)
{
    int cnt = 0;
    nodes[x].in_circle = 1;
    nodes[x].circle_id = id;
    nodes[x].circle_pos = cnt++;
    int start = x; x = nodes[x].out;
    while (start != x)
    {
        nodes[x].in_circle = 1;
        nodes[x].circle_id = id;
        nodes[x].circle_pos = cnt++;
        x = nodes[x].out;
    }

    nodes[start].circle_size = cnt;
    x = nodes[start].out;
    while (start != x)
    {
        nodes[x].circle_size = cnt;
        x = nodes[x].out;
    }
}

int circles_counter = 0;
void find_circles()
{
    memset(mark, 0, sizeof(mark));
    for (int i = 0; i < n; i++)
    {
        if (mark[i]) continue;
        int x = i;
        memset(mark2, 0, sizeof(mark2));
        while (!mark[x])
        {
            mark2[x] = 1;
            mark[x] = 1;
            x = nodes[x].out;
        }
        if (!mark2[x]) continue;
        mark_circle(x, circles_counter++);
    }
}

struct LCA {
    int root;
    int size;
    map<int, int> M;
    map<int, int> RM;
    vector<int> par[20];
    vector<int> height;

    void add_node(int x)
    {
        if (M.find(x) == M.end())
        {
            M[x] = size++;
            RM[M[x]] = x;
        }
        for (int i = 0; i < 20; i++)
            par[i].pb(-1);
        height.pb(0);
    }

    LCA(int x) : root(x) {
        RM[-1] = -1;
        size = 0;
        add_node(x);
        queue<int> q;
        q.push(x);
        while (!q.empty())
        {
            int front = q.front(); q.pop();
            for (auto incoming : nodes[front].in)
            {
                if (nodes[incoming].in_circle) continue;
                add_node(incoming);
                nodes[incoming].circle_pos = root;
                nodes[incoming].circle_size = nodes[root].circle_size;
                nodes[incoming].circle_id = nodes[root].circle_id;
                q.push(incoming);
                par[0][M[incoming]] = M[front];
                height[M[incoming]] = height[M[front]] + 1;
            }
        }

        for (int i = 1; i < 20; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (par[i-1][j] == -1) continue;
                par[i][j] = par[i-1][par[i-1][j]];
            }
        }
    }

    int get_par(int x, int p)
    {
        int P = 0;
        x = M[x];
        while (p > 0)
        {
            if (x == -1) return -1;
            if (p % 2)
                x = par[P][x];
            p /= 2;
            P++;
        }
        return RM[x];
    }

    int get_height(int a)
    {
        return height[M[a]];
    }

    int get_lca(int a, int b)
    {
        a = M[a]; b = M[b];
        if (height[a] < height[b]) b = M[get_par(RM[b], height[b]-height[a])];
        if (height[a] > height[b]) a = M[get_par(RM[a], height[a]-height[b])];

        if (a == b)
            return RM[a];

        for (int i = 19; i >= 0; i--)
        {
            if (par[i][a] == par[i][b]) continue;
            a = par[i][a];
            b = par[i][b];
        }

        return get_par(RM[a], 1); 
    }
};

int main()
{
    int q;
    cin >> n >> q;
    for (int i = 0; i < n; i++)
    {
        cin >> nodes[i].out;
        nodes[nodes[i].out].in.pb(i);
    }

    find_circles();

    vector<LCA> trees;
    map<int, int> tree_pos;

    for (int i = 0; i < n; i++)
    {
        if (nodes[i].in_circle)
        {
            tree_pos[i] = trees.size();
            trees.pb(LCA(i));
        }
    }

    while (0)
    {
        int a;
        cin >> a;
        cout << "Going to: " << nodes[a].out << endl;
        cout << "In circle: " << nodes[a].in_circle << endl;
        cout << "Circle id: " << nodes[a].circle_id << endl;
        cout << "Circle pos: " << nodes[a].circle_pos << endl;
    }

    for (int i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;
        if (nodes[a].in_circle && nodes[b].in_circle)
        {
            if (nodes[a].circle_id == nodes[b].circle_id)
            {
                if (nodes[b].circle_pos >= nodes[a].circle_pos)
                    cout << nodes[b].circle_pos - nodes[a].circle_pos << endl;
                else cout << nodes[a].circle_size - nodes[a].circle_pos + nodes[b].circle_pos << endl;
            }
            else cout << -1 << endl;
        }
        else if (nodes[b].in_circle && nodes[a].circle_id == nodes[b].circle_id)
        {
            int sum = trees[tree_pos[nodes[a].circle_pos]].get_height(a);
            a = nodes[a].circle_pos;
            if (nodes[b].circle_pos >= nodes[a].circle_pos)
                sum += nodes[b].circle_pos - nodes[a].circle_pos;
            else sum += nodes[a].circle_size - nodes[a].circle_pos + nodes[b].circle_pos;
            cout << sum << endl;
        }
        else if (nodes[b].circle_id == nodes[a].circle_id && !nodes[a].in_circle && !nodes[b].in_circle)
        {
            int anc = trees[tree_pos[nodes[b].circle_pos]].get_lca(a, b);
            if (anc == b)
                cout << trees[tree_pos[nodes[b].circle_pos]].get_height(a) - trees[tree_pos[nodes[b].circle_pos]].get_height(b) << endl;
            else cout << -1 << endl;
        }
        else cout << -1 << endl;
    }
}
