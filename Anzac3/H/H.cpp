#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

vector<vector<pii> > edges;

class Node {
    int parentID;
    int parentCol;
    int parentIndex;

    vector<bool> up_prop;

    vector<pii> children;

    bool bad_above;
    bool bad_below;
    int ID;

    Node() {}

    Node(int i, int par, int parCol, int parIndex);

    void prop_bad_down();
    void prop_bad_up(int chInd);
    void check_bad();
};

vector<Node> nodes;

Node::Node(int i, int par, int parCol, int parIndex) {
    bad_above = false;
    bad_below = false;
    ID = i;
    parentID = par;
    parentCol = parCol;
    parentIndex = parIndex;
    children = vector<pii>();
    up_prop = vector<bool>();

    int j=0;
    for (auto x: edges[ID]) {
        if (parentID == x.first)
            continue;
        Node n = Node(x.first, i, x.second, j++);
        children.push_back(x);
        nodes[x.first] = n;
        up_prop.push_back(false);
    }
    sort(children.begin(), children.end(), [](pii x, pii y) { return x.second > y.second; });
}

void Node::prop_bad_down() {
    if (bad_below) {
        return;
    }
    bad_below = true;
    for (auto x: children) {
        nodes[x.first].prop_bad_down();
    }
}

void Node::prop_bad_up(int chInd) {
    if (up_prop[chInd]) {
        return;
    }
    up_prop[chInd] = true;
    bad_above = true;
    if (parentID != -1) {
        nodes[parentID].prop_bad_up(parentIndex);
    }
    int j = 0;
    for (auto x: children) {
        if (j++ != nodes[x.first].parentIndex) {
            nodes[x.first].prop_bad_down();
        }
    }
}

void Node::check_bad() {
    for (auto x: children) {
        if (nodes[x.first].parentCol == parentCol) {
            nodes[parentID].prop_bad_up(parentIndex);
            nodes[x.first].prop_bad_down();
        }
    }
    for (int j=1; j<children.size(); j++) {
        if (children[j].second == children[j-1].second) {
            nodes[children[j-1].first].prop_bad_down();
            nodes[children[j].first].prop_bad_down();
        }
    }
    for (auto x: children) {
        nodes[x.first].check_bad();
    }
}

int main () {

    int n;
    cin >> n;

    nodes = vector<Node>(n);

    for (int i=0; i<n; i++) {
        edges.push_back(vector<pii>());
    }
    for (int i=0; i<n-1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edges[a-1].push_back(pii(b-1, c));
        edges[b-1].push_back(pii(a-1, c));
    }

    nodes[0] = Node(0, -1, -1, -1);
    nodes[0].check_bad();

    vector<int> good = vector<int>();

    for (int i=0; i<n; i++) {
        if (nodes[i].bad_above || nodes[i].bad_below) {
            continue;
        }
        good.push_back(i+1);
    }

    cout << good.size(); << endl;
    for (auto x: good) {
        cout << x << endl;
    }

    return 0;
}
