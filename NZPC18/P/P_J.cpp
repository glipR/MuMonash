// MuMonash

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <queue>

#define X first
#define Y second

using namespace std;

typedef pair<int, int> pii;

struct RuleStorage {
    typedef pair<pii, vector<pii> > rule;

    int n_rules;
    int counter;
    int r_counter;
    string identifier;
    map<string, int> terminals;
    vector<vector<int> > used_in;  // What rules do I affect?
    vector<vector<int> > generated_by;  // What rules have me as an end result?
    vector<int> best_rule;  // What is the best rule (Smallest evaluated.)
    vector<rule> rules;  // What are the rules?
    vector<int> g;  // Shortest length?
    queue<int> expanding;  // What clauses are needing to be expanded?

    RuleStorage(int n, string clause, string ident) : n_rules(n), counter(0), r_counter(0), used_in(0), best_rule(0), rules(n) {
        identifier = ident;
        add_terminal(clause);
    }

    void add_terminal(string t) {
        cerr << t << " is " << counter << endl;
        terminals[t] = counter++;
        best_rule.push_back(-1);
        used_in.push_back(vector<int>());
        g.push_back(-1);
        generated_by.push_back(vector<int>());
    }

    void add_rule(string t1, vector<string> result) {
        if (terminals.count(t1) == 0) add_terminal(t1);
        int non_terms = 0;
        vector<pii> rule_amounts;
        for (auto s: result) {
            if (s[0] == '"') { non_terms++; continue; }
            if (terminals.count(s) == 0) { add_terminal(s); }
            bool found = false;
            for (int j=0; j<rule_amounts.size(); j++) {
                if (rule_amounts[j].X == terminals[s]) {
                    found = true;
                    rule_amounts[j].Y ++;
                    break;
                }
            }
            if (!found) {
                rule_amounts.push_back(pii(terminals[s], 1));
                used_in[terminals[s]].push_back(r_counter);
            }
        }
        generated_by[terminals[t1]].push_back(r_counter);
        rules[r_counter++] = rule(pii(terminals[t1], non_terms), rule_amounts);
        consider(r_counter-1);
    }

    void consider(int rno) {
        int term = rules[rno].X.X;
        if (best_rule[term] == rno) {
            // If we incremented the length of rno. It may no longer be the minimum.
            // As such we need to check for the minimum again.
            best_rule[term] = -1;
            for (auto rn: generated_by[term]) {
                consider(rn);
            }
            return;
        }
        if (
            (best_rule[term] == -1) ||
            (
                (rules[best_rule[term]].X.Y > rules[rno].X.Y) ||
                (rules[best_rule[term]].X.Y == rules[rno].X.Y && rules[best_rule[term]].Y.size() > rules[rno].Y.size())
            ) ||
            (best_rule[term] == rno)
        ) {
            best_rule[term] = rno;
            if (rules[rno].Y.size() == 0) {
                expanding.push(term);
            }
        }
    }

    void solve() {
        while (expanding.size()) {
            int term = expanding.front();
            expanding.pop();
            if (g[term] != -1) continue;
            rule applied_rule = rules[best_rule[term]];
            g[term] = applied_rule.X.Y;
            cerr << "Expanding " << term << " with g value " << g[term] << endl;
            for (auto rno: used_in[term]) {
                if (g[rules[rno].X.X] == -1) {
                    cerr << "  Used in rule " << rno << endl;
                    for (int i=0; i<rules[rno].Y.size(); i++) {
                        if (rules[rno].Y[i].X == term) {
                            rules[rno].X.Y += g[term] * rules[rno].Y[i].Y;
                            rules[rno].Y.erase(rules[rno].Y.begin() + i);
                            consider(rno);
                            break;
                        }
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

        // Compute g values.
        store.solve();

        cout << store.g[store.terminals[clause]] << endl;
    }

    return 0;
}
