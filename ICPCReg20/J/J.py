denom = 30240

n, C = list(map(int, input().split()))

coins = []
for _ in range(C):
    x, d = list(map(int, input().split()))
    x *= denom // d
    coins.append(x)

DP = [-2] * (denom * n + 5)

def solve(v):
    if v < 0:
        return -1
    if v == 0:
        return 0
    if DP[v] != -2:
        return DP[v]
    # Try every coin
    best = denom * n + 1
    for x in range(C):
        s = solve(v - coins[x])
        if s == -1:
            continue
        best = min(best, s+1)
    if best == denom * n + 1:
        DP[v] = -1
    else:
        DP[v] = best
    return DP[v]

print(solve(denom * n))