// MuMonash
// Cake Distribution

#include <iostream>
#include <vector>

#define INF 1000000000

using namespace std;

struct Choice {
    int amount;
    int split[3];

    Choice (int am, int sp[3]) {
        amount = am;
        for (int i=0; i<3; i++) split[i] = sp[i];
    }
};

int gcd(int a, int b) {
    if (b == 0) { return (a < 0) ? -a : a; }
    else { return gcd(b, a%b); }
}

int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int x, y, z;
    cin >> x >> ws >> y >> ws >> z;

    int top = lcm(lcm(x, y), z);

    int counts[3] = { top / x, top / y, top / z };
    int actual[3] = { top / x, top / y, top / z };
    int splits[3] = { 0, 0, 0 };

    vector<Choice> choices;

    int remaining = top;
    while (remaining) {
        int m = INF;
        for (int i=0; i<3; ++i) m = min(m, actual[i]);
        choices.push_back(Choice(m, splits));
        remaining -= m;
        for (int i=0; i<3; ++i) {
            actual[i] -= m;
            if (actual[i] == 0) {
                actual[i] = counts[i];
                splits[i]++;
            }
        }
        if (choices.size() > 5000) {
            break;
        }
    }

    if (remaining) {
        cout << -1 << endl;
    } else {
        cout << choices.size() << endl;
        for (Choice c: choices) {
            cout << c.amount << ' ' << c.split[0]+1 << ' ' << c.split[1]+1 << ' ' << c.split[2]+1 << endl;
        }
    }

    return 0;
}
