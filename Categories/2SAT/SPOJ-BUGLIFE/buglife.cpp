// MuMonash

#include <bits/stdc++.h>

using namespace std;

void generate_stack(stack<int> &st, vector<int> &marked, vector<vector<int>> &adj, int v) {
  if (marked[v]) {
    return;
  }

  marked[v] = true;
  for (int u : adj[v]) {
    generate_stack(st, marked, adj, u);
  }

  st.push(v);
}

void create_component(vector<int> &component, vector<int> &marked, vector<vector<int>> &adj, int v, int comp_num) {
  if (marked[v]) {
    return;
  }

  marked[v] = true;

  for (int u : adj[v]) {
    create_component(component, marked, adj, u, comp_num);
  }

  component[v] = comp_num;
}

int main() {
  int t;
  cin >> t;


  for (int test_num=1; test_num <= t; ++test_num) {
    int n_bugs, n_interactions;
    cin >> n_bugs >> n_interactions;

    vector<vector<int>> adj(2*n_bugs);

    for (int i=0; i<n_interactions; ++i) {
      int a, b;
      cin >> a >> b;
      a--;
      b--;
      int not_a = n_bugs + a;
      int not_b = n_bugs + b;

      adj[a].push_back(not_b);
      adj[not_a].push_back(b);
      adj[b].push_back(not_a);
      adj[not_b].push_back(a);
    }

    stack<int> L;
    vector<int> marked(2*n_bugs);

    for (int i=0; i<2*n_bugs; ++i) {
      generate_stack(L, marked, adj, i);
    }

    for (int i=0; i<2*n_bugs; ++i) {
      marked[i] = false;
    }

    int n_components = 0;
    vector<int> component(2*n_bugs);

    while (!L.empty()) {
      int v = L.top();
      L.pop();

      if (!marked[v]) {
        n_components++;
        create_component(component, marked, adj, v, n_components);
      }
    }

    bool satisfiable = true;

    for (int i=0; i<n_bugs; ++i) {
      if (component[i] == component[i + n_bugs]) {
        satisfiable = false;
        break;
      }
    }

    cout << "Scenario #" << test_num << ":" << endl;
    if (satisfiable) {
      cout << "No suspicious bugs found!" << endl;
    } else {
      cout << "Suspicious bugs found!" << endl;
    }

  }

  return 0;
}
