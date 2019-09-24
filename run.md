# Edit File: .bashrc
1. Move to bottom of file (`Alt` + `/` with `nano .bashrc`)
2. Copy the following contents:

```bash
ulimit -s 10000

# For C/CPP
function runc {
    clear;clear
    F=`ls -t *.c* | head -n1`
    g++ $F -g -std=c++14 -Wall -Wextra -Wconversion -Wshadow -Wfatal-errors -fsanitize=address,undefined -o sol || return

    for i in *.in; do
        echo ---$F $i
        { time (./sol <$i >o 2>error) >/dev/null; } 2>timing
        cat timing | grep real | awk '{print $2}'
        cat error
        # Not required
        rm timing
        rm error
        # Required
        diff -y o ${i%in}[ao]?? >t || cat t || cat o
        # Not required
        rm o
        rm t
    done
}

# For Python3
function runp {
    clear;clear
    F=`ls -t *.py | head -n1`
    for i in *.in; do
        echo ---$F $i
        { time (python3 $F <$i >o 2>error) >/dev/null; } 2>timing
        cat timing | grep real | awk '{print $2}'
        cat error
        # Not required
        rm timing
        rm error
        # Required
        diff -y o ${i%in}[ao]?? >t || cat t || cat o
        # Not required
        rm o
        rm t
    done
}

```
3. Save (in `nano`, `Ctl-X`, then `Y`)

# Template File - CPP

Call this `t.cpp` in the root directory for later use.

```cpp
// Team Name (Monash)
#include <bits/stdc++.h>
using namespace std;

#define me (*this)
#define debug(a) cerr << #a << " = " << (a) << endl;
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    return 0;
}
```

# Template File - Python

Call this `t.py` in the root directory for later use.

```python
# Team Name (Monash)

def read_ints():
    return list(map(int, input().split()))

cases = int(input())

for case in range(cases):
    # Do something.
```

# Generate folders and template files
Run this in terminal once:

```bash
for i in {A..R}; do
    # Create subdir
    mkdir $i
    # Copy templates
    cp t.cpp $i/$i.cpp
    cp t.py $i/$i.py
    # Provided samples are downloaded, extract them.

```
