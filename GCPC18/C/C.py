# MuMonash
# AC

from collections import defaultdict

n, m = map(int,input().split())
lines = defaultdict(lambda: [])
for _ in range(m):
    s, t, c = map(int, input().split())
    lines[s].append((t, c))

DP = [-1 for _ in range(n+1)]

def solve(x):
    if DP[x] != -1:
        return DP[x]
    best = 0
    for nxt, dist in lines[x]:
        best = max(best, dist + solve(nxt))
    DP[x] = best
    return DP[x]

print(max(solve(x) for x in range(1, n+1)))
