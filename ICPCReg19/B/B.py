# MuMonash
n, b = map(int, input().split())
values = sorted(list(map(int, input().split())))
DP = [[-1 for _ in range(b+1)] for __ in range(n+1)]
def solve(i, j):
    # print(i, j)
    if DP[i][j] != -1: return DP[i][j]
    # Try assigning a bucket across all remaining prefixes of this substring
    if j == 0: return 1e18
    best = pow((values[-1] - values[i]),2)
    for x in range(i+1, n):
        best = min(best, pow(values[i] - values[x-1], 2) + solve(x, j-1))
    DP[i][j] = best
    return DP[i][j]
print(solve(0, b))
