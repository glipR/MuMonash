// MuMonash

#include <cstdio>
#include <string>
#include <iostream>
#include <list>
#include <map>

using namespace std;
typedef long long ll;

const ll MAXN = 300001;
pair<bool, int> DP[MAXN];
map<string, string> dictionary;
string nvwl;

int solve(int index) {
    if (DP[index].first) {
        return DP[index].second;
    }
    // Go through all possible lengths that match.
}

int main() {

    int n;
    cin >> n >> ws;
    for (int i=0; i<n; i++) {
        string dic;
        cin >> dic >> ws;
        string novowel = "";
        for (auto c : dic) {
            if ((c == 'A') || (c == 'E') || (c == 'I') || (c == 'O') || (c == 'U')) {
                continue;
            }
            novowel = novowel + c;
        }
        dictionary[dic] = novowel;
    }
    cin >> nvwl >> ws;

    // Now do the DP
    for (int i=0; i<MAXN; i++) {
        DP[i] = pair<bool, int>(false, -1);
    }



    return 0;
}
