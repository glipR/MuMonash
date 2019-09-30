#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>

using namespace std;

int h, w;
const int MAXH = 1010;

struct Pair {
    int x, y;
    Pair(){}
    Pair(int a, int b) { x = a; y = b; }
};

struct Cell {
    bool left, top, right, bottom;

    Cell () { left = true; top = true; right = true; bottom = true;};

    bool valid_move(int x, int y)
    {
        if (x == 0)
        {
            if (y == 1)
                return right;
            else if (y == -1)
                return left;
        }
        if (y == 0)
        {
            if (x == 1)
                return bottom;
            else if (x == -1)
                return top;
        }

        return false; // shouldn't reach here
    }
};

Cell maze[MAXH][MAXH];

void readMaze()
{
    string s;
    getline(cin, s);
    for (int i = 0; i < w; i++)
        maze[0][i].top = false;

    for (int i = 0; i < h; i++)
    {
        getline(cin, s);
        for (int j = 0; j < w; j++)
        {
            if (s[2*j] == '|')
            {
                maze[i][j].left = false;
                if (j-1 >= 0)
                    maze[i][j-1].right = false;
            }

            if (s[2*j + 1] == '_')
            {
                maze[i][j].bottom = false;
                if (i < h-1)
                    maze[i+1][j].top = false;
            }

            if (s[2*j + 2] == '|')
            {
                maze[i][j].right = false;
            }
        }
    }
}

void printMaze()
{
    for (int i = 0; i < w; i++)
        cout << " _";
    cout << endl;
    for (int i = 0; i < h; i++, cout << '|' << endl)
        for (int j = 0; j < w; j++)
        {
            if (maze[i][j].left)
                cout << ' ';
            else cout << '|';

            if (maze[i][j].bottom)
                cout << ' ';
            else cout << '_';
        }
}

inline bool in_maze(int x, int y)
{
    return x >= 0 && y >= 0 && x < h && y < w;
}

Pair parent[MAXH][MAXH][25];
int height[MAXH][MAXH];

void bfsTree()
{
    bool mark[MAXH][MAXH];
    queue<Pair> q;
    q.push(Pair(0, 0));
    mark[0][0] = 1;
    height[0][0] = 0;
    parent[0][0][0] = Pair(-1, -1);

    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    while (!q.empty())
    {
        Pair front = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int newX = front.x + dx[i];
            int newY = front.y + dy[i];
            if (!in_maze(newX, newY) || mark[newX][newY] || !maze[front.x][front.y].valid_move(dx[i], dy[i])) continue;

            mark[newX][newY] = 1;
            height[newX][newY] = height[front.x][front.y] + 1;
            parent[newX][newY][0] = front;
            q.push(Pair(newX, newY));
        }
    }
}

void computeAncestors()
{
    for (int p = 1; p < 22; p++)
    {
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
            {
                if (parent[i][j][p-1].x == -1)
                    parent[i][j][p] = Pair(-1, -1);
                else parent[i][j][p] = parent[parent[i][j][p-1].x][parent[i][j][p-1].y][p-1];
            }
    }
}

inline int get_height(Pair a) { return height[a.x][a.y]; }
inline bool same_pairs(Pair a, Pair b) { return a.x == b.x && a.y == b.y; }

Pair get_parent(Pair a, int num)
{
    int p = 0;
    while (num != 0)
    {   
        if (a.x == -1)
            return a;
        if (num % 2)
            a = parent[a.x][a.y][p];
        p++;
        num /= 2;
    }
    return a;
}

Pair get_lca(Pair a, Pair b)
{
    if (get_height(a) < get_height(b))
        b = get_parent(b, get_height(b) - get_height(a));
    else if (get_height(a) > get_height(b))
        a = get_parent(a, get_height(a) - get_height(b));
    if (same_pairs(a, b)) return a;
    int l = 0, r = 1e6 + 10;
    while (r - l > 1)
    {
        int mid = (r+l) / 2;
        if (same_pairs(get_parent(a, mid), get_parent(b, mid)))
            r = mid;
        else l = mid;
    }
    return get_parent(a, r);
}

int main()
{
    cin >> h >> w;
    string temp;
    getline(cin, temp);
    readMaze();
    //printMaze();

    bfsTree();
    computeAncestors();

    long long sum = 0;

    int q;
    cin >> q;
    int lastX, lastY;
    cin >> lastX >> lastY;
    lastX--; lastY--;
    for (int i = 1; i < q; i++)
    {
        int x, y;
        cin >> x >> y;
        x--; y--;
        Pair anc = get_lca(Pair(x, y), Pair(lastX, lastY));
        sum += height[x][y] + height[lastX][lastY] - 2*get_height(anc);

        lastX = x; lastY = y;
    }

    cout << sum << endl;

}
