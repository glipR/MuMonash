// MuMonash

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long long ll;
typedef pair<pair<int, ll>, vector<pii> > rule1;             // Used for g values
typedef pair<pair<pair<int, ll>, pii>, vector<pii> > rule2;  // Used for f values

#define X first
#define Y second

#define rno1 X.X
#define smallest_dist1 X.Y

#define rno2 X.X.X
#define minimum_dist2 X.X.Y
#define minimum_change2 X.Y.X
#define terms_considered2 X.Y.Y

#define ISINF -2
#define INF 1000000000

struct RuleStorage {

    int n_rules;
    int t_counter;
    int r_counter;
    map<string, int> terminals;
    vector<ll> g;
    vector<ll> f;
    vector<vi> used_in;
    string identifier;
    vector<rule1> rule1s;
    vector<rule2> rule2s;
    vi generates;

    RuleStorage(int nrules, string clause, string ident): n_rules(nrules), r_counter(0), t_counter(0), rule1s(nrules), rule2s(nrules) {
        identifier = ident;
        add_terminal(clause);
    }

    void dbg_rule1(rule1 r) {
        cerr << "Rule #" << r.rno1 << " has min dist " << r.smallest_dist1 << " and " << r.Y.size() << " remaining terminals." << endl;
    }
    void dbg_rule2(rule2 r) {
        cerr << "Rule #" << r.rno2 << " has min dist " << r.minimum_dist2 << " and " << r.minimum_change2 << " minimum change with " << r.Y.size() << " remaining checks." << endl;
    }

    int add_terminal(string t1) {
        // cerr << t1 << " is " << t_counter << endl;
        terminals[t1] = t_counter;
        used_in.push_back(vi());
        g.push_back(-1);
        f.push_back(-1);
        return t_counter++;
    }

    int add_rule(string t1, vector<string> terms) {
        if (terminals.count(t1) == 0) add_terminal(t1);
        int non_term_count = 0;
        bool special_encountered = false;
        vector<pii> term_amounts;
        for (auto s: terms) {
            if (s[0] == '"') { non_term_count++; if (s == identifier) special_encountered = true; continue; }
            if (terminals.count(s) == 0) { add_terminal(s); }
            bool found = false;
            for (int j=0; j<term_amounts.size(); j++) {
                if (term_amounts[j].X == terminals[s]) {
                    found = true;
                    term_amounts[j].Y ++;
                    break;
                }
            }
            if (!found) {
                term_amounts.push_back(pii(terminals[s], 1));
                used_in[terminals[s]].push_back(r_counter);
            }
        }
        rule1s[r_counter] = rule1(pii(r_counter, non_term_count), term_amounts);
        rule2s[r_counter] = rule2(pair<pii, pii>(pii(r_counter, non_term_count), pii(special_encountered ? 0 : -1, 0)), term_amounts);
        generates.push_back(terminals[t1]);
        return r_counter++;
    }

    void solve() {
        auto cmp = [&](rule1 l, rule1 r) {
            // Is l more than r?
            if (g[generates[l.rno1]] != -1) return true;
            if (g[generates[r.rno1]] != -1) return false;
            if (generates[l.rno1] != generates[r.rno1]) {
                if (l.Y.size() > r.Y.size()) return true;
                else if (l.Y.size() < r.Y.size()) return false;
            }
            if (l.rno1 == r.rno1) {
                if (l.Y.size() > r.Y.size()) return true;
                else if (l.Y.size() < r.Y.size()) return false;
            }
            if (l.Y.size() > r.Y.size()) return true;
            if (l.Y.size() < r.Y.size()) return false;
            // Equal smallest distance, same generated.
            return (l.smallest_dist1 > r.smallest_dist1);
        };
        priority_queue<rule1, vector<rule1>, decltype(cmp)> pq(cmp);
        for (int i=0; i<r_counter; i++) {
            pq.push(rule1s[i]);
        }
        while (!pq.empty()) {
            rule1 r = pq.top();
            pq.pop();
            int term = generates[r.rno1];
            // dbg_rule1(r);
            if (g[term] != -1) { continue; }  // This isn't the best rule.
            if (r.Y.size() != 0) { break; }  // No further rules are ready. Break
            // Expand this rule.
            if (r.smallest_dist1 > INF) {
                g[term] = ISINF;
            }
            else {
                g[term] = r.smallest_dist1;
            }
            // cerr << "Got a rule for term #" << term << "! Set the g value to " << g[term] << endl;
            // Update every rule which uses this term.
            for (auto a: used_in[term]) {
                for (int b=0; b<rule1s[a].Y.size(); b++) {
                    if (rule1s[a].Y[b].X == term) {
                        if (g[term] == ISINF) {
                            rule1s[a].smallest_dist1 = INF + 1;
                        } else {
                            rule1s[a].smallest_dist1 += g[term] *  rule1s[a].Y[b].Y;
                        }
                        rule1s[a].Y.erase(rule1s[a].Y.begin() + b);
                        pq.push(rule1s[a]);
                        break;
                    }
                }
            }
        }
    }

    void solve2() {
        for (int i=0; i<n_rules; i++) {
            for (auto pa: rule2s[i].Y) {
                if (g[pa.X] == -1 || g[pa.X] == -2) {
                    rule2s[i].minimum_dist2 = -1;
                    break;
                }
                rule2s[i].minimum_dist2 += pa.Y * g[pa.X];
            }
        }
        auto cmp = [&](rule2 l, rule2 r) {
            // Is l worse than r?
            if (l.minimum_dist2 == -1) return true;
            if (r.minimum_dist2 == -1) return false;
            if (l.minimum_change2 == -1) return true;
            if (r.minimum_change2 == -1) return false;
            if (generates[l.rno2] != generates[r.rno2]) {
                if (l.Y.size() > r.Y.size()) return true;
                else if (l.Y.size() < r.Y.size()) return false;
            }
            if (l.rno2 == r.rno2) {
                if (l.Y.size() > r.Y.size()) return true;
                else if (l.Y.size() < r.Y.size()) return false;
            }
            if (l.minimum_dist2 + l.minimum_change2 < r.minimum_dist2 + r.minimum_change2) return false;
            if (l.minimum_dist2 + l.minimum_change2 > r.minimum_dist2 + r.minimum_change2) return true;
            // Equal smallest distance, same generated.
            return (l.Y.size() > r.Y.size());
        };
        priority_queue<rule2, vector<rule2>, decltype(cmp)> pq(cmp);
        for (int i=0; i<r_counter; i++) {
            pq.push(rule2s[i]);
        }
        while (!pq.empty()) {
            rule2 r = pq.top();
            pq.pop();
            int term = generates[r.rno2];
            // dbg_rule2(r);
            if (f[term] != -1) { continue; }; // This isn't the best rule.
            if (r.minimum_dist2 == -1) break; // No further rules are usable. Break
            if (r.minimum_change2 == -1) break;  // No further rules are ready. Break
            // Expand this rule
            f[term] = (r.minimum_dist2 + r.minimum_change2 > INF) ? ISINF : r.minimum_dist2 + r.minimum_change2;
            // cerr << "Got a rule for term #" << term << "! Set the f value to " << f[term] << endl;
            // Update every rule which uses this term.
            for (auto a: used_in[term]) {
                for (int b=0; b<rule2s[a].Y.size(); b++) {
                    if (rule2s[a].Y[b].X == term) {
                        if (rule2s[a].minimum_change2 == -1 || rule2s[a].minimum_change2 > ((f[term] == ISINF) ? INF : f[term] - g[term])) rule2s[a].minimum_change2 = ((f[term] == ISINF) ? INF : f[term] - g[term]);
                        rule2s[a].Y.erase(rule2s[a].Y.begin() + b);
                        pq.push(rule2s[a]);
                        break;
                    }
                }
            }
        }
    }

};

int main() {

    while (1) {
        int num_rules;
        cin >> num_rules >> ws;
        if (num_rules == 0) break;
        string clause, identifier;
        cin >> clause >> ws >> identifier >> ws;

        RuleStorage store(num_rules, clause, identifier);

        for (int i=0; i<num_rules; i++) {
            string t1;
            int num_parts;
            string eq;
            cin >> t1 >> ws >> eq >> ws;
            vector<string> parts (0);
            while (1) {
                string ans;
                cin >> ans >> ws;
                if (ans[0] == '.') break;
                parts.push_back(ans);
            }
            store.add_rule(t1, parts);
        }

        // Compute g, then f values.
        store.solve();
        store.solve2();

        cerr << store.f[store.terminals[clause]] << endl;

        if (store.f[store.terminals[clause]] == -2 || store.f[store.terminals[clause]] > INF) {
            cout << -1 << endl;
        }
        else {
            cout << store.f[store.terminals[clause]] << endl;
        }
    }

    return 0;
}
