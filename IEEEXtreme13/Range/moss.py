from functools import lru_cache
import sys

sys.setrecursionlimit(1000000)

@lru_cache(maxsize=1000000)
def foo(b):
    if b == 0 or b == 1:
        return 1

    i = 1
    ans = 0

    # add the sequence 1 + 2 + 4 + ... = 2^i - 1
    while ((2**i) - 1) <= b:
        ans += foo(b - ((2**i) - 1))
        ans = ans % (1000000007)
        i += 1
    return ans

def final_foo(b):
    if b != 0:
        res = foo(b)
        return ((res*2) % (1000000007))
    else:
        return 1

n = int(input())
all_ans = [final_foo(0)]
for b in range(1, 1000001):
    x = (all_ans[-1] + final_foo(b)) % 1000000007
    all_ans.append(x)

for _ in range(n):
    # multiply by two to account for prepending X
    a, b = map(int, input().split())
    ans = all_ans[b] - (all_ans[a-1] if a != 0 else 0)
    ans = ans % 1000000007
    print(ans)
