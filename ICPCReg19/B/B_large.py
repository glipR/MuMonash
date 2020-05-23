# MuMonash
import sys
sys.setrecursionlimit(10000000)
n, b = map(int, input().split())
values = list(sorted(list(map(int, input().split()))))
b = min(b, n)
DP = [[-1 for _ in range(b+1)] for __ in range(n)]
def solve(i, j):
    # print(i, j)
    try:
        if DP[i][j] != -1:
            return DP[i][j]
        # Try assigning a bucket across all remaining prefixes of this substring
        if j == 0:
            return -2
    except:
        sys.exit(0)
    best = pow((values[-1] - values[i]),2)
    for x in range(i+1, n):
        if solve(x, j-1) != -2:
            res1 = solve(x, j-1)
            res = pow(values[i] - values[x-1], 2) + res1
            best = min(best, res)
    DP[i][j] = best
    return DP[i][j]
print(solve(0, b))
