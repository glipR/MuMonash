import sys
from collections import defaultdict
sys.setrecursionlimit(100000)

n, m = list(map(int, input().split()))
mines = []
for x in range(n):
    mines.append(list(map(int, input().split())))

edges = defaultdict(list)

for y in range(m):
    a, b, t = list(map(int, input().split()))
    edges[a-1].append((b-1, t))
    edges[b-1].append((a-1, t))

DP = [
    [-1 for x in range(n)]
    for d in range(1001)
]

def solve(day, mine):
    if day > 1000:
        return 0
    if DP[day][mine] != -1:
        return DP[day][mine]
    cur = max(0, mines[mine][0] - mines[mine][1] * day)
    m = 0
    for n, t in edges[mine]:
        m = max(m, solve(day + t, n))
    DP[day][mine] = cur + m
    return DP[day][mine]

print(solve(0, 0))
