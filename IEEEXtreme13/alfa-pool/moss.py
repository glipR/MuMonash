from functools import lru_cache
import sys

sys.setrecursionlimit(1000000)

@lru_cache(maxsize=100000)
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
    
n = int(input())
for _ in range(n):
    # multiply by two to account for prepending X
    b = int(input())
    res = foo(b)
    if b > 0:
        print((res*2) % (1000000007))
    else:
        print(res)
