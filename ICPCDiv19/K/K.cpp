
// MuMonash
#include <bits/stdc++.h>
using namespace std;

#define me (*this)
#define debug(a) cerr << #a << " = " << (a) << endl;
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
typedef long long ll;
typedef pair<int, int> pii;

#define MAX_LEN 20

class Node {
    public:
        int start_index;
        int end_index;

        Node* children[10];

        Node () {
            start_index = 0;
            end_index = 0;

            for (int i=0; i<10; i++) {
                children[i] = NULL;
            }
        }

        Node (const string s, const int str_index, const int num_index) {
            start_index = num_index;
            end_index = num_index;

            for (int i=0; i<10; i++) {
                children[i] = NULL;
            }

            if (str_index != s.length()) {
                int n_index = (int)s[str_index] - (int)'0';
                children[n_index] = new Node(s, str_index + 1, num_index);
            }
        }

        void prop_string(const string s, const int str_index, const int num_index) {
            end_index = num_index;

            if (str_index != s.length()) {
                int n_index = (int)s[str_index] - (int)'0';
                if (children[n_index] == NULL) {
                    children[n_index] = new Node(s, str_index + 1, num_index);
                } else {
                    children[n_index] -> prop_string(s, str_index+1, num_index);
                }
            }
        }

        bool leaf() {
            for (int i=0; i<10; i++) {
                if (children[i] != NULL) {
                    return false;
                }
            }
            return true;
        }

};

long long solve(Node* n1, Node* n2, int mult) {
    if (n1 -> leaf() && n2 -> leaf()) {
        if (n1 -> start_index == n2 -> start_index) {
            return -1;
        }
        return 0;
    }
    for (int sum=9; sum>=0; sum--) {
        vector<long long> solutions;
        for (int i=0; i<10; i++) {
            for (int j=0; j<10; j++) {
                if ((i + j) % 10 == sum) {
                    if ((n1 -> children[i] != NULL) && (n2 -> children[j] != NULL)) {
                        solutions.push_back(solve(n1 -> children[i], n2 -> children[j], mult - 1));
                    }
                }
            }
        }
        solutions.erase(remove(solutions.begin(), solutions.end(), -1), solutions.end());
        if (solutions.size() != 0) {
            long long _max = -1;
            for (auto sub: solutions) {
                _max = max((long long)(sub + sum * pow(10, mult)), _max);
            }
            if (_max != -1) {
                return _max;
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int num_strings;
    cin >> num_strings;

    string numbers[num_strings];
    Node root = Node();

    for (int i=0; i<num_strings; i++) {
        cin >> numbers[i];
        for (int j=numbers[i].length(); j<MAX_LEN; j++) {
            numbers[i].insert(0, 1, '0');
        }
        root.prop_string(numbers[i], 0, i);
    }

    cout << solve(&root, &root, MAX_LEN - 1) << endl;

    return 0;
}
