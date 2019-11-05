#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstring>
#include <queue>
#include <algorithm>

#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)

using namespace std;

struct Edge {
    int u, v;
    vector<int> types;

    bool inCycle;
    bool removed;

    Edge () {}
    Edge (int a, int b) : u(a), v(b) { inCycle = false; removed = false; }
};

const int MAXN = 2010;

pair<int, int> mat[MAXN][MAXN];
bool mark[3*MAXN];
int n;
vector<Edge> edges;

vector<pair<int, int> > findCList[MAXN];

int dfsMat(int node)
{
    mark[node] = 1;
    int res = 1;
    for (int i = 0; i < findCList[node].size(); i++)
    {
        int new_node = findCList[node][i].first;
        int edge_index = findCList[node][i].second;
        if (!edges[edge_index].removed && !mark[new_node])
            res += dfsMat(new_node);
    }
    return res;
}

struct FlowEdge {
    int x;
    int cap;
    int rev;
    FlowEdge () {}
    FlowEdge (int a, int c) : x(a), cap(c) {}
};

char flowEdgeType[3*MAXN];

vector<FlowEdge> flowList[3*MAXN];

map<int, vector<int> > workerMap;
int workers[MAXN];

bool flowBfs(int s, int t)
{
    queue<int> q;
    q.push(s);
    pair<int, int> par[3*MAXN];
    mark[s] = 1;
    while (!q.empty())
    {
        int front = q.front();
        q.pop();
        if (front == t)
        {
            int cur = t;
            while (cur != s)
            {
                int p = par[cur].first;
                int index = par[cur].second;
                flowList[p][index].cap -= 1;
                flowList[flowList[p][index].x][flowList[p][index].rev].cap += 1;
                cur = p;
            }
            return true;
        }
        for (int i = 0; i < flowList[front].size(); i++)
        {
            if (mark[flowList[front][i].x] || flowList[front][i].cap <= 0) continue;
            mark[flowList[front][i].x] = 1;
            q.push(flowList[front][i].x);
            par[flowList[front][i].x] = mp(front, i);
        }
    }
    return false;
}

bool flowDfs(int s, int t)
{
    if (s == t) return true;
    for (int i = 0; i < flowList[s].size(); i++)
    {
        if (mark[flowList[s][i].x] || flowList[s][i].cap <= 0) continue;
        mark[flowList[s][i].x] = 1;
        flowList[s][i].cap -= 1;
        flowList[flowList[s][i].x][flowList[s][i].rev].cap += 1;
        bool res = flowDfs(flowList[s][i].x, t);
        if (!res)
        {
            flowList[s][i].cap += 1;
            flowList[flowList[s][i].x][flowList[s][i].rev].cap -= 1;
        }
        else return true;
    }
    return false;
}

int sendFlow(int s, int t)
{
    int flow = 0;
    memset(mark, false, sizeof(mark));
    while (flowBfs(s, t))
    {
        flow++;
        memset(mark, false, sizeof(mark));
    }
    return flow;
}

void printFlowGraph(int cnt)
{
    for (int i = 0; i < cnt; i++)
    {
        cout << "Node #" << i << "(" << flowEdgeType[i] << "): ";
        for (int j = 0; j < flowList[i].size(); j++)
            cout << "(" << flowList[i][j].x << ", cap: " << flowList[i][j].cap << ", type: " << flowEdgeType[flowList[i][j].x]  <<") ";
        cout << endl;
    }
}

int main()
{
    int k;
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = mp(0, 0);

    for (int i = 0; i < n; i++)
    {
        int x; cin >> x;
        int m; cin >> m;
        edges.pb(Edge(i, x-1));
        findCList[i].pb(mp(x-1, i));
        findCList[x-1].pb(mp(i, i));
        for (int j = 0; j < m; j++)
        {
            cin >> x;
            edges[edges.size()-1].types.pb(x);
        }
    }

    int inCycles = 0;

    //cerr << "Start finding cycle " << endl;

    for (int i = 0; i < n; i++)
    {
        memset(mark, false, sizeof(mark));
        edges[i].removed = 1;
        if (dfsMat(0) == n)
        {
            edges[i].inCycle = true;
            inCycles++;    
        }
        edges[i].removed = 0;
    }

    //cerr << "End finding cycle" << endl;

    set<int> allWorkers;
    map<int, int> internalMap;

    for (int i = 0; i < k; i++)
    {
        int x;
        cin >> x;
        workers[i] = x;
        workerMap[x].pb(i+1);
        allWorkers.insert(x);
    }

    pair<int, int> ans_edge[3*MAXN];

    flowEdgeType[0] = 's'; // Node 0 --> Source
    flowEdgeType[1] = 't'; // Node 1 --> Target
    flowEdgeType[2] = 'c'; // Node 2 --> Cycle
    // Other types: w -> worker, e -> edge

    int nodeIndex = 3;

    map<int, int> reverse_map;

    //cerr << "Here1" << endl;

    for (auto it = allWorkers.begin(); it != allWorkers.end(); it++, nodeIndex++)
    {
        flowEdgeType[nodeIndex] = 'w';
        flowList[0].pb(FlowEdge(nodeIndex, workerMap[*it].size()));
        flowList[nodeIndex].pb(FlowEdge(0, 0));
        flowList[nodeIndex][flowList[nodeIndex].size()-1].rev = flowList[0].size() - 1;
        flowList[0][flowList[0].size()-1].rev = flowList[nodeIndex].size() - 1;
        internalMap[*it] = nodeIndex;
        reverse_map[nodeIndex] = *it;
    }

    for (int i = 0; i < edges.size(); i++, nodeIndex++)
    {
        flowEdgeType[nodeIndex] = 'e';
        ans_edge[nodeIndex] = mp(edges[i].u + 1, edges[i].v + 1);
        for (int j = 0; j < edges[i].types.size(); j++)
        {
            int type = edges[i].types[j];
            if (internalMap.find(type) == internalMap.end()) continue;
            int index = internalMap[type];
            flowList[index].pb(FlowEdge(nodeIndex, 1));
            flowList[nodeIndex].pb(FlowEdge(index, 0));
            flowList[nodeIndex][flowList[nodeIndex].size()-1].rev = flowList[index].size() - 1;
            flowList[index][flowList[index].size()-1].rev = flowList[nodeIndex].size()-1;
        }
        if (edges[i].inCycle)
        {
            flowList[nodeIndex].pb(FlowEdge(2, 1));
            flowList[2].pb(FlowEdge(nodeIndex, 0));
            flowList[2][flowList[2].size()-1].rev = flowList[nodeIndex].size()-1;
            flowList[nodeIndex][flowList[nodeIndex].size()-1].rev = flowList[2].size()-1;
        }
        else
        {
            flowList[nodeIndex].pb(FlowEdge(1, 1));
            flowList[1].pb(FlowEdge(nodeIndex, 0));
            flowList[1][flowList[1].size()-1].rev = flowList[nodeIndex].size() - 1;
            flowList[nodeIndex][flowList[nodeIndex].size()-1].rev = flowList[1].size() - 1;
        }
    }

    flowList[1].pb(FlowEdge(2, 0));
    flowList[2].pb(FlowEdge(1, inCycles-1));
    flowList[2][flowList[2].size()-1].rev = flowList[1].size()-1;
    flowList[1][flowList[1].size()-1].rev = flowList[2].size()-1;

//    cerr << "Here2 " << endl;

    //cout << "before flow:\n"; printFlowGraph(nodeIndex);

    //cerr << "Here" << endl;

    int flow = sendFlow(0, 1);

    //cerr << "End of flow" << endl;

    //cout << "flow: " << flow << endl; // 000000000000000000000000
    //cout << "in cycles: " << inCycles << endl; // -----------------

    //cout << "after flow:\n"; printFlowGraph(nodeIndex); // ------------------

    if (flow < n-1)
    {
        cout << -1 << endl;
        return 0;
    }

    memset(mark, false, sizeof(mark));

    vector<pair<int, pair<int, int> > > answers;

    queue<int> q;
    q.push(0);
    mark[0] = 1;
    while (!q.empty())
    {
        int front = q.front();
        q.pop();
        for (int i = 0; i < flowList[front].size(); i++)
        {
            if (!mark[flowList[front][i].x])
            {
                q.push(flowList[front][i].x);
                mark[flowList[front][i].x] = 1;
            }
            if ((flowEdgeType[front] != 'w') 
            ||  (flowEdgeType[flowList[front][i].x] != 'e') 
            || flowList[front][i].cap != 0) continue;
            
            int ww;
            pair<int, int> ee;
            if (flowEdgeType[front] == 'w')
            {
                int color = reverse_map[front];
                ww = workerMap[color][workerMap[color].size()-1];
                workerMap[color].pop_back();
            }
            else
            {
                ee = ans_edge[front];
            }

            if (flowEdgeType[flowList[front][i].x] == 'w')
            {
                int color = reverse_map[flowList[front][i].x];
                ww = workerMap[color][workerMap[color].size()-1];
                workerMap[color].pop_back();
            }
            else
            {
                ee = ans_edge[flowList[front][i].x];
            }

            answers.pb(mp(ww, ee));
        }
    }
    
    sort(answers.begin(), answers.end());
    for (int i = 1; i < answers[0].first; i++)
        cout << "0 0\n";
    for (int i = 0; i < answers.size(); i++)
    {
        if (i != 0)
        {
            for (int j = answers[i-1].first + 1; j < answers[i].first; j++)
                cout << "0 0\n";
        }
        cout << answers[i].second.first << ' ' << answers[i].second.second << endl;
    }
    for (int j = answers[answers.size()-1].first + 1; j <= k; j++)
        cout << "0 0\n";
}
