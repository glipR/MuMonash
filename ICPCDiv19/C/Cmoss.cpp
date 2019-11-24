// MuMonash

#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

const int n_states = (1<<17);
int n_hints;
// most significant bit is false if it is alice's turn
int dp_state[n_states];

int assassin_mask;
int blue_mask;
int red_mask;

string board_hint[16];
vector<vector<int>> hints;

bool is_alice_turn(int s) {
    return (s & (1<<16)) == 0;
}

bool mask_met(int s, int mask) {
    return (s & mask) == mask;
}

// returns 1 if alice wins, 0 if bob wins
int solve(int s) {
    std::bitset<17> y(s);
    if (dp_state[s] != -1) { return dp_state[s]; }

    bool player_can_win = false;
    for (int i=0; i<n_hints; ++i) {
        vector<int> this_hints = hints[i];

        int next_s = s;

        // play out this hint
        for (int j=0; j<this_hints.size(); ++j) {
            int guess = this_hints[j];
            int guess_bit = 1 << guess;

            if (mask_met(next_s, guess_bit)) {
                continue; // cant play the same card twice
            }

            next_s |= guess_bit; // mark card as used

            if (is_alice_turn(s) && !mask_met(blue_mask, guess_bit)) {
                break;
            } else if (!is_alice_turn(s) && !mask_met(red_mask, guess_bit)) {
                break;
            }

            if (mask_met(next_s, blue_mask)) {
                if (is_alice_turn(s)) { player_can_win = true; }
                break;
            }

            if (mask_met(next_s, red_mask)) {
                if (!is_alice_turn(s)) { player_can_win = true; }
                break;
            }
        }

        if (player_can_win) { break; }

        bool stumped = s == next_s; // player is stumped if no guesses were made
        if (stumped) continue;

        if (mask_met(next_s, assassin_mask)) continue;

        next_s ^= 1<<16; // swap turns

        int winner_from_here = solve(next_s);

        if (is_alice_turn(s)) {
            if (winner_from_here==1) { player_can_win = true; }
        } else {
            if (winner_from_here==0) { player_can_win = true; }
        }

        if (player_can_win) { break; }
    }

    if (player_can_win) {
        if (is_alice_turn(s)) {
            dp_state[s] = 1;
        } else {
            dp_state[s] = 0;
        }
    } else {
        if (is_alice_turn(s)) {
            dp_state[s] = 0;
        } else {
            dp_state[s] = 1;
        }
    }

    return dp_state[s];
}

int main() {
    // Read in board words
    for (int i=0; i<16; ++i) {
        cin >> board_hint[i];
    }

    // Read in the masks
    for (int i=0; i<16; ++i) {
        char x;
        cin >> x;

        int this_bit = 1 << i;
        if (x == 'B') {
            blue_mask |= this_bit;
        } else if (x == 'R') {
            red_mask |= this_bit;
        } else if (x == 'A') {
            assassin_mask |= this_bit;
        }
    }

    // Read in the hints
    cin >> n_hints;
    for (int i=0; i<n_hints; ++i) {
        string hint_word;
        cin >> hint_word;

        int n_guesses;
        cin >> n_guesses;

        vector<string> guesses;
        for (int j=0; j<n_guesses; ++j) {
            string x;
            cin >> x;
            guesses.push_back(x);
        }

        sort(guesses.begin(), guesses.end());

        // convert to numbers
        vector<int> num_hints;
        for (auto w : guesses) {
            for (int j=0; j<16; ++j) {
                if (w==board_hint[j]) {
                    num_hints.push_back(j);
                }
            }
        }

        hints.push_back(num_hints);
    }

    // Mark DP as unsolved
    for (int i=0; i<n_states; ++i) {
        dp_state[i] = -1;
    }

    // Solve
    int winner = solve(0);

    if (winner == 1) {
        cout << "Alice" << endl;
    } else if (winner == 0) {
        cout << "Bob" << endl;
    }


    return 0;
}
