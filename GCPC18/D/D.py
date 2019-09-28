# MuMonash
# AC

num = int(input())
tops = list(map(int, input().split()))

def solve():
    best = [0, tops[0]]
    for nxt in tops[1:]:
        best[1] = min(nxt, best[1])
        if best[1] < best[0]:
            return 0
        best[0], best[1] = nxt - best[1], nxt - best[0]
    for nxt in tops[:0:-1]:
        best[1] = min(nxt, best[1])
        if best[1] < best[0]:
            return 0
        best[0], best[1] = nxt - best[1], nxt - best[0]
    return best[1] - best[0] + 1

print(solve())
