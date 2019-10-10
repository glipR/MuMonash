#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstdio>
#include <queue>
#include <set>
#include <algorithm>

#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)

using namespace std;

typedef pair<long long, int> pii;
typedef long long ll;

const int MAX_NUM = 1e9;

struct Rule {
    vector<string> ids;
    string id;

    int terminals_cnt;
    ll literals;
    int unmatched_ids;
    bool has_target;

    ll backup_literals;
    ll backup_unmatched_ids;

    void restore_backup()
    {
        literals = backup_literals;
        unmatched_ids = backup_unmatched_ids;
    }

    void backup()
    {
        backup_literals = literals;
        backup_unmatched_ids = unmatched_ids;
    }

    Rule(){}
    Rule(string line, string target)
    {
        has_target = false;
        unmatched_ids = 0;
        terminals_cnt = 0;
        literals = 0;

        string res = "";
        int i = 0;
        while (line[i] != ' ')
            res += line[i++];
        id = res;
        res = "";
        i += 3;
        
        for (int j = i; j < line.length(); j++)
            if (line[j] == ' ')
                terminals_cnt++;
 
        for (int j = 0; j < terminals_cnt; j++)
        {
            res = "";
            while (line[i] != ' ')
                res += line[i++];
            i++;

            if (res[0] != '"')
            {
                unmatched_ids++;
                ids.pb(res);
            }
            else 
            {
                literals++;
                if (res == target)
                    has_target = true;
            }
        }
        backup();
    }
};

vector<Rule> rules;
map<string, ll> g;
map<string, ll> f;
map<string, set<int> > mapping;
set <pii> g_goods, f_goods; // pii.first = # literals, pii.second = index of the rule

void global_resets()
{
    rules.clear();
    g.clear();
    f.clear();
    mapping.clear();
    g_goods.clear();
    f_goods.clear();
}

void compute_gs()
{
    while (!g_goods.empty())
    {
        pii front = *g_goods.begin();
        g_goods.erase(g_goods.begin());
        if (g.find(rules[front.second].id) != g.end())
            continue;

        string id = rules[front.second].id;
        ll value = front.first;
        if (value > MAX_NUM) continue;

        g[id] = value;
        
        for (auto it = mapping[id].begin(); it != mapping[id].end(); it++)
        {
            int ruleIndex = *it;
            for (int j = 0; j < rules[ruleIndex].ids.size(); j++)
            {
                if (rules[ruleIndex].ids[j] == id)
                {
                    rules[ruleIndex].literals += value;
                    rules[ruleIndex].unmatched_ids--;
                }
            }
            if (rules[ruleIndex].unmatched_ids == 0)
                g_goods.insert(mp(rules[ruleIndex].literals, ruleIndex));
        }
    }
}

void compute_fs()
{
    while (!f_goods.empty())
    {
        pii front = *f_goods.begin();
        f_goods.erase(f_goods.begin());
        if (f.find(rules[front.second].id) != f.end())
            continue;

        string id = rules[front.second].id;
        ll value = front.first;
        if (value > MAX_NUM) continue;

        f[id] = value;

        for (auto it = mapping[id].begin(); it != mapping[id].end(); it++)
        {
            int ruleIndex = *it;
            ll inside_value = rules[ruleIndex].literals;
            for (int i = 0; i < rules[ruleIndex].ids.size(); i++)
                if (g.find(rules[ruleIndex].ids[i]) == g.end() || g[rules[ruleIndex].ids[i]] > MAX_NUM)
                {
                    inside_value = -1;
                    break;
                }
                else inside_value += g[rules[ruleIndex].ids[i]];
            if (inside_value == -1)
                continue;
            inside_value -= g[id]; inside_value += f[id];
            f_goods.insert(mp(inside_value, ruleIndex));
        }
    }
}

int main()
{
    int n; cin >> n;
    while (n != 0)
    {
        global_resets();
        string start, target;
        cin >> start >> target >> ws;

        for (int i = 0; i < n; i++)
        {
            string s;
            getline(cin, s);
            rules.pb(Rule(s, target));

            if (rules[i].unmatched_ids == 0)
                g_goods.insert(mp(rules[i].literals, i));
            
            for (int j = 0; j < rules[i].ids.size(); j++)
                mapping[rules[i].ids[j]].insert(i);
        }
        
        compute_gs();

        for (int i = 0; i < rules.size(); i++) rules[i].restore_backup();
        for (int i = 0; i < rules.size(); i++)
        {
            if (!rules[i].has_target) continue;
            ll value = rules[i].literals;
            for (int j = 0; j < rules[i].ids.size(); j++)
            {
                string id = rules[i].ids[j];
                if (g.find(id) == g.end())
                {
                    value = -1;
                    break;
                }
                value += g[id];
            }
            if (value != -1)
                f_goods.insert(mp(value, i));
        }

        compute_fs();
        
        if (f.find(start) == f.end() || f[start] > MAX_NUM)
            cout << -1 << endl;
        else cout << f[start] << endl;

        cin >> n;
    }

}
