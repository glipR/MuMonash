# Superhot - Recursive
# AC

e, l, r = map(int, input().split())
if e:
    enemies = list(map(int, input().split()))
if l:
    left_stack = list(map(int, input().split()))
if r:
    right_stack = list(map(int, input().split()))

import sys
sys.setrecursionlimit(l + r + 10)

DP = [[-1 for __ in range(r+1)] for ___ in range(l+1)]

# Arguments:
    # x: How many are left on left stack
    # y: How many are left on right stack
    # e: How many enemies remain
    # hp: Enemy hp
def can_solve(x, y, e, hp):
    if DP[x][y] != -1:
        return DP[x][y]
    if e == 0:
        DP[x][y] = True
        return True
    if x > 0:
        if hp == left_stack[len(left_stack) - x]:
            if e == 1:
                DP[x][y] = True
                return True
            if can_solve(x-1, y, e-1, enemies[len(enemies) - e + 1]):
                DP[x][y] = True
                return True
        elif hp > left_stack[len(left_stack) - x]:
            if can_solve(x-1, y, e, hp-left_stack[len(left_stack) - x]):
                DP[x][y] = True
                return True
    if y > 0:
        if hp == right_stack[len(right_stack) - y]:
            if e == 1:
                DP[x][y] = True
                return True
            if can_solve(x, y-1, e-1, enemies[len(enemies) - e + 1]):
                DP[x][y] = True
                return True
        elif hp > right_stack[len(right_stack) - y]:
            if can_solve(x, y-1, e, hp-right_stack[len(right_stack) - y]):
                DP[x][y] = True
                return True
    DP[x][y] = False
    return False

# Fuck edge cases.
if e == 0:
    print("YES")
else:
    print("YES" if can_solve(l, r, e, enemies[0]) else "NO")


