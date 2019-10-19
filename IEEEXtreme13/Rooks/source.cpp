#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <string>

#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)

using namespace std;

typedef pair<int, char> rook_move;

struct Operation {
    char c;
    int x;
    int y;
    Operation (char cc, int a, int b)
    {
        // cc is ['r', 'l', 'u', 'd', 't', 'p']
        c = cc;
        x = a;
        y = b;
    }

    Operation(){}

    void print()
    {
        cout << x << ' ' << y << ' ' << (char)(c + ('A' - 'a')) << endl;
    }
};

vector<Operation> answer;

int dx[300], dy[300];

char oppositeDir(char c)
{
    if (c == 'r') return 'l';
    if (c == 'l') return 'r';
    if (c == 'd') return 'u';
    if (c == 'u') return 'd';
    return ' '; // Doesn't reach here
}

struct Item {
    int x; int y;
    int x_index, y_index;
    Item (int a, int b)
    {
        x = a;
        y = b;
        x_index = 0;
        y_index = 0;
    }
    Item () {}

    Operation move(char dir)
    {
        x += dx[dir];
        y += dy[dir];

        answer.pb(Operation(dir, x-dx[dir], y-dy[dir]));
        return Operation(oppositeDir(dir), x, y);
    }

    Operation disappear()
    {
        answer.pb(Operation('t', x, y));
        return Operation('p', x, y);
    }
};

struct ItemSorterX
{
    inline bool operator() (const Item& st1, const Item& st2)
    {
        return (st1.x < st2.x);
    }
};

struct ItemSorterY
{
    inline bool operator() (const Item& st1, const Item& st2)
    {
        return (st1.y < st2.y);
    }
};

vector<Item> rooks, targets;

void printRooks()
{
    for (int i = 0; i < rooks.size(); i++)
        cout << "Rook #" << i << ": " << rooks[i].x << ", " << rooks[i].y << endl;
}

struct GeneralItemSorter
{
    char dir;
    GeneralItemSorter(char d)
    {
        dir = d;
    }

    inline bool operator() (const int& left, const int& right)
    {
        if (dir == 'l')
            return rooks[left].x < rooks[right].x;
        if (dir == 'r')
            return rooks[left].x > rooks[right].x;
        if (dir == 'd')
            return rooks[left].y < rooks[right].y;
        if (dir == 'u')
            return rooks[left].y > rooks[right].y;
    }
};

void sortRooks(bool x)
{
    if (x)
        sort(rooks.begin(), rooks.end(), ItemSorterX());
    else sort(rooks.begin(), rooks.end(), ItemSorterY());
}

void sortTargets(bool x)
{
    if (x)
        sort(targets.begin(), targets.end(), ItemSorterX());
    else
        sort(targets.begin(), targets.end(), ItemSorterY());
}

int rookIndexByYIndex(int y_index)
{
    for (int i = 0; i < rooks.size(); i++)
        if (rooks[i].y_index == y_index)
            return i;
}

int rookIndexByX(int x)
{
    for (int i = 0; i < rooks.size(); i++)
        if (rooks[i].x == x)
            return i;
    return -1;
}

int rookIndexByY(int y)
{
    for (int i = 0; i < rooks.size(); i++)
        if (rooks[i].y == y)
            return i;
    return -1;
}



void log(string s)
{
    //return;
    cout << s << endl;
}

int main()
{
    dx['r'] = 1;
    dx['l'] = -1;
    dx['u'] = 0;
    dx['d'] = 0;
    dy['r'] = 0;
    dy['l'] = 0;
    dy['u'] = 1;
    dy['d'] = -1;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        rooks.pb(Item(x, y));
    }
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        targets.pb(Item(x, y));
    }

    sortRooks(1);
    sortTargets(1);
    for (int i = 0; i < n; i++)
    {
        rooks[i].x_index = i;
        targets[i].x_index = i;
    }

    sortRooks(0);
    sortTargets(0);
    for (int i = 0; i < n; i++)
    {
        rooks[i].y_index = i;
        targets[i].y_index = i;
    }

   
    sortTargets(1);
    for (int i = 0; i < targets.size(); i++)
    {
        int rookIndex = rookIndexByYIndex(targets[i].y_index);
        moveRook(rookIndex, targets[i].x < rooks[rookIndex].x ? 'l' : 'r', targets[i].x, rooks[rookIndex].y);
    }
    
    sortTargets(0);
    reverse(targets.begin(), targets.end());
    for (int i = 0; i < targets.size(); i++)
    {
        int rookId = rookIndexByX(targets[i].x);
        moveRook(rookId, rooks[rookId].y > targets[i].y ? 'd' : 'u', targets[i].x, targets[i].y);
    }

    cout << answer.size() << endl;
    for (int i = 0; i < answer.size(); i++)
        answer[i].print();
}
