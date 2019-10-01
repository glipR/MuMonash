// MuMonash

#include <cstdio>
#include <string>
#include <iostream>
#include <list>

using namespace std;

#define BLUE 0
#define RED 1
#define NEUTRAL 2
#define ASSASSIN 3

#define UNKNOWN -1
#define BOB 0
#define ALICE 1

#define UNUSED 0
#define USED 1

int one_d_value(int i, int j) {
    return i * 4 + j;
}

bool used(int value, int state) {
    return (state & (1 << value)) >> value == USED;
}

int player(int state) {
    return (state & (1 << 16)) >> 16;
}

bool blue_done(int state, int keyword_type[4][4]) {
    for (int k=0; k<16; k++) {
        if (((state & (1 << k)) == 0) && (keyword_type[k / 4][k % 4] == BLUE))
            return false;
    }
    return true;
}

bool red_done(int state, int keyword_type[4][4]) {
    for (int k=0; k<16; k++) {
        if (((state & (1 << k)) == 0) && (keyword_type[k / 4][k % 4] == RED))
            return false;
    }
    return true;
}

int solve(int* DP, int keyword_type[4][4], int hints[50][10], int num_hints, int state) {

    if (DP[state] != UNKNOWN) {
        return DP[state];
    }
    if (player(state) == ALICE) {
        //cerr << "Alice's Turn." << endl;
        bool ALICE_CAN_WIN = false;
        for (int k=0; k<num_hints; k++) {
            //cerr << "Using hint " << k << endl;
            bool used_keywords[16];
            for (int o=0; o<16; o++)
                used_keywords[o] = false;
            //memset(used_keywords, false, 16);
            for (int l=0; l<10; l++) {
                if (hints[k][l] == -1) {
                    //cerr << "I hit the end" << endl;
                    int new_state = state;
                    for (int i=0; i<16; i++)
                        if (used_keywords[i])
                            new_state += 1 << i;
                    // Else break
                    if (new_state == state) break;
                    // If used_keywords has a true in it, do the DP
                    new_state -= (1 << 16);
                    int solve_result = solve(DP, keyword_type, hints, num_hints, new_state);
                    if (solve_result == ALICE) ALICE_CAN_WIN = true;
                    break;
                }
                if (used(hints[k][l], state)) {
                    //cerr << "The " << l << "th word is used." << endl;
                    continue;
                }
                int i, j;
                i = hints[k][l] / 4;
                j = hints[k][l] % 4;
                if (keyword_type[i][j] == BLUE) {
                    //cerr << "The " << l << "th word is blue" << endl;
                    used_keywords[hints[k][l]] = true;
                    int new_state = state;
                    for (int p=0; p<16; p++)
                        if (used_keywords[p])
                            new_state += 1 << p;
                    if (blue_done(new_state, keyword_type)) {
                        //cerr << "Blue is done!" << endl;
                        ALICE_CAN_WIN = true;
                        break;
                    }
                    continue;
                }
                if (keyword_type[i][j] == ASSASSIN) {
                    // We lose.
                    break;
                }
                // Otherwise neutral or red. So include the keyword and stop there.
                used_keywords[hints[k][l]] = true;
                int new_state = state;
                // Bobs turn
                new_state -= (1 << 16);
                for (int p=0; p<16; p++)
                    if (used_keywords[p])
                        new_state += 1 << p;
                // If this was the last red, cancel.
                if (red_done(new_state, keyword_type)) break;
                int solve_result = solve(DP, keyword_type, hints, num_hints, new_state);
                if (solve_result == ALICE) ALICE_CAN_WIN = true;
                break;
            }
        }
        if (ALICE_CAN_WIN) {
            DP[state] = ALICE;
        } else {
            DP[state] = BOB;
        }
        return DP[state];
    }
    if (player(state) == BOB) {
        //cerr << "Bob's Turn." << endl;
        bool BOB_CAN_WIN = false;
        for (int k=0; k<num_hints; k++) {
            bool used_keywords[16];
            for (int o=0; o<16; o++)
                used_keywords[o] = false;
            //memset(used_keywords, false, 16);
            for (int l=0; l<10; l++) {
                if (hints[k][l] == -1) {
                    int new_state = state;
                    for (int i=0; i<16; i++)
                        if (used_keywords[i])
                            new_state += 1 << i;
                    // Else break
                    if (new_state == state) break;
                    // If used_keywords has a true in it, do the DP
                    new_state += (1 << 16);
                    int solve_result = solve(DP, keyword_type, hints, num_hints, new_state);
                    if (solve_result == BOB) BOB_CAN_WIN = true;
                    break;
                }
                if (used(hints[k][l], state)) continue;
                int i, j;
                i = hints[k][l] / 4;
                j = hints[k][l] % 4;
                if (keyword_type[i][j] == RED) {
                    used_keywords[hints[k][l]] = true;
                    int new_state = state;
                    for (int p=0; p<16; p++)
                        if (used_keywords[p])
                            new_state += 1 << p;
                    if (red_done(new_state, keyword_type)) {
                        BOB_CAN_WIN = true;
                        break;
                    }
                    continue;
                }
                if (keyword_type[i][j] == ASSASSIN) {
                    // We lose.
                    break;
                }
                // Otherwise neutral or blue. So include the keyword and stop there.
                used_keywords[hints[k][l]] = true;
                int new_state = state;
                // Alices turn
                new_state += (1 << 16);
                for (int p=0; p<16; p++)
                    if (used_keywords[p])
                        new_state += 1 << p;
                // If this was the last blue, cancel.
                if (blue_done(new_state, keyword_type)) break;
                int solve_result = solve(DP, keyword_type, hints, num_hints, new_state);
                if (solve_result == BOB) BOB_CAN_WIN = true;
                break;
            }
        }
        if (BOB_CAN_WIN) {
            DP[state] = BOB;
        } else {
            DP[state] = ALICE;
        }
        return DP[state];
    }

    //cerr << "BADBADBAD" << endl;
    return UNKNOWN;

}

int main() {

    string keywords[4][4];

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            cin >> keywords[i][j] >> ws;
        }
    }

    int keyword_type[4][4];

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            char c;
            cin >> c;
            if (c == 'B')
                keyword_type[i][j] = BLUE;
            if (c == 'R')
                keyword_type[i][j] = RED;
            if (c == '.')
                keyword_type[i][j] = NEUTRAL;
            if (c == 'A')
                keyword_type[i][j] = ASSASSIN;
        }
    }

    int hints[50][10];

    int num_hints;
    cin >> num_hints >> ws;

    for (int h=0; h<num_hints; h++) {
        string hint_name;
        int num_words;
        cin >> hint_name >> num_words;
        list<string> hint_words;
        for (int k=0; k<num_words; k++) {
            string word;
            cin >> word;
            hint_words.push_back(word);
        }
        // Sort lexicographically.
        hint_words.sort();
        int k=0;
        for (list<string>::iterator it = hint_words.begin(); it != hint_words.end(); it++) {
            for (int i=0; i<4; i++) {
                for (int j=0; j<4; j++) {
                    if (it->compare(keywords[i][j]) == 0) {
                        hints[h][k] = one_d_value(i, j);
                    }
                }
            }
            k++;
        }
        while (k<10) {
            hints[h][k] = -1;
            k++;
        }
        /*
        for (int d=0; d<10; d++) {
            cerr << hints[h][d] << ' ';
        }
        cerr << endl;
        */
    }

    // Input has been read. Time for DP.
    // 1: Alice Wins, 0: Bob Wins, -1: Current undefined.
    // A case in the DP is represented by:
    // Whether a string has been used up
    // Whose turn it is (This is bit shifted 16 times.)
    int DP[1 << 17];
    for (int o=0; o<1<<17; o++)
        DP[o] = UNKNOWN;
    //memset(DP, UNKNOWN, 1 << 17);

    int result = solve(DP, keyword_type, hints, num_hints, 1 << 16);
    if (result == ALICE) {
        cout << "Alice" << endl;
    } else {
        cout << "Bob" << endl;
    }

    return 0;
}
