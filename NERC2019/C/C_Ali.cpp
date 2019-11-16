#include <iostream>
#include <vector>
#include <algorithm>

#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)

using namespace std;

const int MAXN = 200001;

typedef long long ll;
typedef pair<ll,int> pii;

pii pii_max(pii a, pii b)
{
    if (a.first > b.first) return a;
    return b;
}

struct Node {
    pii M;
    ll lazy;
    int l, r;
    Node *left, *right;
    Node (int a, int b) : l(a), r(b) 
    { 
        left = NULL; right = NULL; lazy = 0; M = mp(0, a);
        if (b - a > 1)
        {
            left = new Node(a, (a+b)/2);
            right = new Node((a+b)/2, b);
        }
    }

    void add(int L, int R, ll K)
    {
        if (L >= r || R <= l) return;
        if (L <= l && R >= r)
        {
            M.first += K;
            lazy += K;
            return;
        }
        if (left != NULL)
        {
            left->add(l, r, lazy);
            left->add(L, R, K);
        }
        if (right != NULL)
        {
            right->add(l, r, lazy);
            right->add(L, R, K);
        }
        lazy = 0;
        M = pii_max(left->M, right->M);
    }

    pii query(int L, int R)
    {
        if (L >= r || R <= l) return mp(-1,l);
        if (L <= l && R >= r) return M;
        pii res = mp(-1, 0);
        if (left != NULL)
        {
            if (lazy > 0)
                left->add(l, r, lazy);
            res = pii_max(res, left->query(L, R));
        }
        if (right != NULL)
        {
            if (lazy > 0)
                right->add(l, r, lazy);
            res = pii_max(res, right->query(L, R));
        }
        lazy = 0;
        return res;
    }
};

struct Task {
    int l, r, id;
    ll p;
    Task(int i, int a, int b, ll c) : id(i), l(a), r(b), p(c) {}
};

bool compare(const Task& a, const Task& b) { return a.l < b.l; }

int main()
{
    int n;
    ll k;
    cin >> n >> k;
    ll ans = 0;
    vector<Task> v;
    for (int i = 0; i < n; i++)
    {
        int a, b; ll p;
        cin >> a >> b >> p;
        v.pb(Task(i+1, a, b, p));
    }
    
    sort(v.begin(), v.end(), compare);

    Node *root = new Node(1, MAXN);
    int pointer = v.size() - 1;

    int ansL;
    int ansR;

    for (int i = MAXN-1; i >= 1; i--)
    {
        root->add(i, MAXN, -1*k);
        while (pointer >= 0 && v[pointer].l == i)
        {
            root->add(v[pointer].r, MAXN, v[pointer].p);
            pii q = root->query(v[pointer].l, MAXN);
            if (q.first > ans)
            {
                ans = q.first;
                ansL = i;
                ansR = q.second;
            }
            pointer--;
        }
//        if (pointer == -1) break;
    }
    cout << ans;
    if (ans == 0) cout << endl;
    else
    {
        vector<int> anss;
        cout << ' ' << ansL << ' ' << ansR;
        ll checker = -1 * k * (ansR - ansL + 1);
        for (auto task:v)
        {
            if (ansL <= task.l && ansR >= task.r)
            {
                anss.pb(task.id);
                checker += task.p;
            }
        }
        if (checker != ans) cout << "SHIT" << endl;
        cout << ' ' << anss.size() << endl;
        for (auto p:anss) cout << p << ' ';
        cout << endl;
    }
}
