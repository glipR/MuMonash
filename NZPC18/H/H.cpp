#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Player {
    int wins, dif;
    string name;
    int id;

    Player() { wins = 0; dif = 0; }

    bool const operator < (const Player &other) const
    {
        if (wins != other.wins) return wins < other.wins;
        if (dif != other.dif) return dif < other.dif;
        return id > other.id;
    }
};

bool equal(Player a, Player b)
{
    return a.wins == b.wins && a.dif == b.dif;
}

Player players[20];

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        players[i].id = i;
        cin >> players[i].name;
        for (int j = 0; j < n; j++)
        {
            if (j == i) { string s; cin >> s; continue; }
            int x; cin >> x;
            players[i].wins += (x == 7 ? 1 : 0);
            players[i].dif += x;
            players[j].dif -= x;
        }
    }

    sort(players, players+n);
    reverse(players, players+n);
    
    cout << players[0].name;
    for (int i = 1; i < n; i++)
        if (equal(players[0], players[i]))
            cout << ' ' << players[i].name;
    cout << " won with " << players[0].wins << " wins and " << (players[0].dif > 0 ? "+" : (players[0].dif == 0 ? "" : "-")) << players[0].dif << " points difference." << endl;
}
