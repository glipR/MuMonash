#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

typedef long long ll;

template<typename T, typename U> struct SegmentTree2 {
    T I, t[4]; int N, h; vector<T> A; // I is the identity value.
    SegmentTree2(const vector<T>& data, T I=T()): I(I), N(data.size()),
    h(sizeof(int)*8-__builtin_clz(N)), A(2*N, I) {
        copy(data.begin(), data.end(), A.begin()+N);
        for (int i=N-1; i;i--) op(i);
    }
    void op(int i) { A[i].op(A[2*i], A[2*i+1]); }
    void prop(int i) { A[2*i].us(A[i].U); A[2*i+1].us(A[i].U); A[i].NU(); }
    void push(int i) {for (int j=h;j;j--) prop(i>>j); }
    void update(int l, int r, U v) { // Acts on [l, r)
        push(l+=N); push((r+=N)-1); bool cl=0,cr=0;
        for (;l<r;l/=2,r/=2) {
            if (cl) op(l-1); if (cr) op(r);
            if (l&1) A[l++].us(v), cl=1;
            if (r&1) A[--r].us(v), cr=1;
        }
        if (l==1 && cr) op(1);
        else for (l--;r>0;l/=2,r/=2) {
            if (cl && l) op(l);
            if (cr && (!cl || (l!=r && r!=1))) op(r);
        }
    }
    T query(int l, int r) { // Acts on [l, r)
        push(l+=N); push((r+=N)-1);
        t[0]=t[2]=I; int i=0, j=2;
        for(;l<r;l/=2,r/=2) {
            if (l&1) t[i^1].op(t[i],A[l++]), i^=1;
            if (r&1) t[j^1].op(A[--r],t[j]), j^=1;
        }
        t[i^1].op(t[i],t[j]);
        return t[i^1];
    }
};

struct RangeMin {
    int a = INT_MAX, U = INT_MIN;
    void op(RangeMin& b, RangeMin& c) { a=min(b.a, c.a); }
    void us(int v) { if (v!=INT_MIN) a=U=v; }
    void NU() { U=INT_MIN; }
};

struct RangeSum {
    int a = 0, U = INT_MAX;
    void op(RangeSum& b, RangeSum& c) { a = b.a + c.a; }
    void us(int v) { if (v!=INT_MAX) a=U=v; }
    void NU() { U=INT_MAX; }
};

int main() {

    int n, m, s;
    cin >> n >> m >> s;

    SegmentTree2<RangeSum, int> broken = SegmentTree2<RangeSum, int>(vector<RangeSum>(s));
    broken.update(0, s, 0);

    vector<pair<int, int>> brakes;
    for (int i=0; i<n; i++) {
        int a, b;
        cin >> a >> b;
        brakes.push_back(pair<int, int>(a, b));
        broken.update(a-1, b, 1);
    }
    vector<pair<ll, pair<int, int> > > stored_powers;
    priority_queue<pair<double, int > > powers;
    for (int i=0; i<m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        stored_powers.push_back(pair<ll, pair<int, int> >(c, pair<int, int>(a, b)));
        int planks = broken.query(a-1, b).a;
        if (planks == 0) continue;
        cerr << planks << endl;
        double score = planks / (double) c;
        powers.push(pair<double, int >(score, i));
    }

    ll cost = 0;
    while (broken.query(0, s).a > 0 && powers.size()) {
        pair<double, int> power = powers.top(); powers.pop();
        cerr << "Selecting " << power.first << " " << power.second << endl;
        int planks = broken.query(stored_powers[power.second].second.first-1, stored_powers[power.second].second.second).a;
        if (planks == 0) continue;
        broken.update(stored_powers[power.second].second.first-1, stored_powers[power.second].second.second, 0);
        cost += stored_powers[power.second].first;
    }

    if (broken.query(0, s).a > 0) {
        cout << -1 << endl;
    } else {
        cout << cost << endl;
    }

    return 0;
}
