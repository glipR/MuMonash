#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int acnt[30];
int bcnt[30];

int main()
{
    string a, b;
    cin >> a >> b;
    if (a > b)
        swap(a, b);
    for (int i = 0; i < a.length(); i++)
        acnt[a[i] - 'a']++;
    for (int i = 0; i < b.length(); i++)
        bcnt[b[i] - 'a']++;
    if (a == b)
    {
        cout << a << " is identical to " << b << endl;
    }
    else if (a.length() == b.length())
    {
        int minus = 0, plus = 0, fail = 0;
        for (int i = 0; i < 26; i++)
        {
            acnt[i] -= bcnt[i];
            if (acnt[i] == -1)
                minus++;
            if (acnt[i] == 1)
                plus++;
            if (acnt[i] > 1 || acnt[i] < -1)
                fail++;
        }
        if (fail > 0)
            cout << a << " is nothing like " << b << endl;
        else if (minus == plus && minus == 1)
            cout << a << " is almost an anagram of " << b << endl;
        else if (minus == plus && minus == 0)
            cout << a << " is an anagram of " << b << endl;
        else cout << a << " is nothing like " << b << endl;
    }
    else if (a.length() - b.length() == 1 || b.length() - a.length() == 1)
    {
        int out = 0, fail = 0;
        for (int i = 0; i < 26; i++)
        {
            acnt[i] -= bcnt[i];
            if (acnt[i] == -1 || acnt[i] == 1)
                out++;
            else if (acnt[i] != 0)
                fail++;
        }
        if (fail > 0)
            cout << a << " is nothing like " << b << endl;
        else if (out == 1)
            cout << a << " is almost an anagram of " << b << endl;
        else cout << a << " is nothing like " << b << endl;
    }
    else cout << a << " is nothing like " << b << endl;
}

