#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)

using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;

struct Chunk {
    ll a, b;
    bool is_single_char;
    char c;
    bool deleted;

    Chunk (ll x, ll y) : a(x), b(y), is_single_char(false), deleted(false) {};
    Chunk (char character) : c(character), is_single_char(true), deleted(false) {};

    ll size()
    {
        if (is_single_char) return 1;
        return b - a  + 1;
    }

    bool merge(Chunk other)
    {
        if (is_single_char || other.is_single_char) return false;
        if (b + 1 == other.a)
        {
            b = other.b;
            return true;
        }
        return false;
    }

    bool equals(Chunk other)
    {
        if (is_single_char != other.is_single_char) return 0;
        if (is_single_char) return c == other.c;
        return a == other.a && b == other.b;
    }
};

vector<Chunk> text[2];
const ll MAXN = 1e11;

pli find_pos_in_chunk(int index, ll pos)
{
    ll skipped = 0;
    for (int i = 0; i < text[index].size(); i++)
    {
        if (text[index][i].deleted) continue;
        if (skipped + text[index][i].size() >= pos)
            return mp(skipped, i);
        skipped += text[index][i].size();
    }
    // Shouldn't reach here
    int FAIL1 = 1;
    int FAIL2 = 2;
    return mp(0, FAIL1 / ((FAIL2 / 2) - 1));
}

void perform_delete(int index, ll pos)
{
    pli selected_chunk = find_pos_in_chunk(index, pos);
    ll skipped = selected_chunk.first;
    int chunk_id = selected_chunk.second;

    if (text[index][chunk_id].size() == 1)
        text[index][chunk_id].deleted = 1;
    else 
    {
        ll remaining = pos - skipped;
        ll a = text[index][chunk_id].a, b = text[index][chunk_id].b;
        
        Chunk left = Chunk(a, a + remaining - 2);
        Chunk right = Chunk(a + remaining, b);

        if (right.size() <= 0)
            text[index][chunk_id] = left;
        else if (left.size() <= 0)
            text[index][chunk_id] = right;
        else {
            text[index][chunk_id] = right;
            text[index].insert(text[index].begin() + chunk_id, left);
        }
    }
}

void perform_insert(int index, ll pos, char c)
{
    pli selected_chunk = find_pos_in_chunk(index, pos);
    ll remaining = pos - selected_chunk.first;
    int chunk_id = selected_chunk.second;

    Chunk new_chunk = Chunk(c);

    if (remaining == 1)
    {
        text[index].insert(text[index].begin() + chunk_id, new_chunk);
        return;
    }

    ll a = text[index][chunk_id].a, b = text[index][chunk_id].b;

    Chunk left = Chunk(a, a + remaining - 2);
    Chunk right = Chunk(a + remaining - 1, b);

    text[index][chunk_id].deleted = 1;

    if (right.size() >= 0)
        text[index].insert(text[index].begin() + chunk_id, right);
    text[index].insert(text[index].begin() + chunk_id, new_chunk);
    if (left.size() >= 0)
        text[index].insert(text[index].begin() + chunk_id, left);
}

void print(vector<Chunk> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        Chunk chunk = v[i];
        if (chunk.deleted) continue;
        if (chunk.is_single_char) cout << chunk.c << ", ";
        else cout << "[" << chunk.a << ", " << chunk.b << "], ";
    }
    cout << endl;
}

void read_input(int index)
{
    char c;
    cin >> c;
    while (c != 'E')
    {
        if (c == 'D')
        {
            ll pos; cin >> pos;
            perform_delete(index, pos);
        }
        if (c == 'I')
        {
            ll pos; cin >> pos;
            char new_char; cin >> new_char;
            perform_insert(index, pos, new_char);
        }
        cin >> c;
    }
}

int main()
{
    text[0].pb(Chunk(1, MAXN));
    text[1].pb(Chunk(1, MAXN));

    read_input(0);
    read_input(1);

    vector<Chunk> merged[2];

    for (int text_id = 0; text_id < 2; text_id++)
    {
        for (int merging = 0; merging < text[text_id].size(); merging++)
        {
            if (text[text_id][merging].deleted) continue;
            if (merged[text_id].size() == 0 || !merged[text_id][merged[text_id].size()-1].merge(text[text_id][merging]))
                merged[text_id].pb(text[text_id][merging]);
        }
    }

    bool failed = merged[0].size() != merged[1].size();
    for (int i = 0; i < merged[0].size() && !failed; i++)
        failed |= !merged[0][i].equals(merged[1][i]);

    //print(merged[0]);
    //print(merged[1]);

    cout << (int) failed << endl;

}
