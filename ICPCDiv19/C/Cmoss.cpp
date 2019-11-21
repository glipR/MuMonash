// MuMonash

#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

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
    if (dp_state[s] != -1) { return dp_state[s]; }

    // check if assassin is marked
    if (mask_met(s, assassin_mask)) {
        // whoevers turn it is now wins since the last player chose the assassin
        if (is_alice_turn(s)) {
            dp_state[s] = 1;
        } else {
            dp_state[s] = 0;
        }

        return dp_state[s];
    }

    // check if blue mask is satisfied
    if (mask_met(s, blue_mask)) {
        // alice owns blue so she wins
        dp_state[s] = 1;
        return 1;
    }

    // check if red mask is satisfied
    if (mask_met(s, red_mask)) {
        // bob owns red so he wins
        dp_state[s] = 0;
        return 0;
    }

    bool player_can_win = false;
    for (int i=0; i<n_hints; ++i) {
        vector<int> this_hints = hints[i];

        for (int j=0; j<this_hints.size(); ++j) {
            int guess = this_hints[j];
            int guess_bit = 1 << guess;
            // has this card already been guessed?
            if (mask_met(s, guess_bit)) {
                // cant play again
                continue;
            }

            // can at least play this card
            int next_s = s;

            next_s |= guess_bit; // mark card as used

            if (is_alice_turn(s)) {
                if (mask_met(blue_mask, guess_bit)) {} else { next_s ^= 1<<16; }
            } else {
                if (mask_met(red_mask, guess_bit)) {} else { next_s ^= 1<<16; }
            }

            int winner_from_here = solve(next_s);

            if (is_alice_turn(s)) {
                if (winner_from_here==1) { player_can_win = true; }
            } else {
                if (winner_from_here==0) { player_can_win = true; }
            }

            // since we have tried to play a card now, we must stop
            break;
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

    /*
    // Print out the board
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            cout << board_hint[4*i + j] << " ";
        }
        cout << endl;
    }
    */

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
