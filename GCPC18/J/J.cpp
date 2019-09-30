#include <iostream>
#include <vector>
#include <map>
#include <set>

#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

struct Triple {
    int right, bottom;
    int id;

    Triple() {}
    Triple(int a, int b, int c) { right = a; bottom = b; id = c; }

    const bool operator < (const Triple &other) const
    {
        if (other.right != right)
            return right < other.right;
        if (other.bottom != bottom)
            return bottom < other.bottom;
        return id < other.id;
    }
};

map<pii, set<Triple> > M;
vector<int> lleft[301001], ttop[301001], rright[301001], bbottom[301001];

vector<int> answer[301001];

bool markID[300011];

void insert_piece(int row, int col, int a, int b, int c, int d, int id)
{
    lleft[row].pb(a);
    ttop[row].pb(b);
    rright[row].pb(c);
    bbottom[row].pb(d);
    
    answer[row].pb(id);
    markID[id] = 1;
}

int top_rule(int row, int col)
{
    if (row == 0) return 0;
    if (bbottom[row-1].size() <= col) return -1;
    return bbottom[row-1][col];
}

int left_rule(int row, int col)
{
    if (col == 0) return 0;
    if (rright[row].size() <= col-1) return -1;
    return rright[row][col-1];
}

int used = 0;

void fill_row(int row)
{
    int col = -1;
    while (true)
    {
        col++;
        int left = left_rule(row, col);
        int top = top_rule(row, col);
        if (left == 0 && col != 0)
            return;
        if (top == 0 && row != 0)
            return;
        if (top == -1)
            return;
        if (M.find(mp(left, top)) == M.end())
            return;
        set<Triple> s = M[mp(left, top)];
        if (s.empty())
            return;
        Triple piece = *s.begin();
        while (markID[piece.id])
        {
            s.erase(s.begin());
            if (s.empty())
                return;
            piece = *s.begin();
        }
        used++;
        insert_piece(row, col, left, top, piece.right, piece.bottom, piece.id);
    }
}

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int x[4];
        for (int j = 3; j >= 0; j--) cin >> x[j];
        for (int j = 0; j < 4; j++)
        {
            if (M.find(mp(x[j], x[(j+1) % 4])) == M.end())
                M[mp(x[j], x[(j+1)%4])] = set<Triple>();
            M[mp(x[j], x[(j+1) % 4])].insert(Triple(x[(j+2)%4], x[(j+3)%4], i + 1));
        }
    }

    int row = 0;
    fill_row(row);
    int len = ttop[0].size();
    while (true)
    {
        row++;
        fill_row(row);
        if (ttop[row].size() == 0)
            break;
        if (ttop[row].size() != len)
        {
            cout << "impossible" << endl;
            return 0;
        }
    }

    if (used < n)
    {
        cout << "impossible" << endl;
        return 0;
    }

    for (int i = 0; i < row; i++)
        if (rright[i][len-1] != 0)
        {
            cout << "impossible" << endl;
            return 0;
        }
    for (int i = 0; i < len; i++)
        if (bbottom[row-1][i] != 0)
        {
            cout << "impossible" << endl;
            return 0;
        }
    
    cout << row << ' ' << len << endl;
    for (int i = 0; i < row; i++, cout << endl)
        for (int j = 0; j < len; j++)
            cout << answer[i][j] << ' ';
}
