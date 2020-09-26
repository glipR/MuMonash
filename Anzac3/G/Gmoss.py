DEBUG = True
DEBUG = False

a = []
for c in input():
    if c == 'B':
        a.append(1)
    elif c == 'R':
        a.append(-1)
#a = [1 if x=='B' else -1 for x in input()]
b = [x * -1 for x in a]

if DEBUG:
    print(f'a: {a}')
    print(f'b: {b}')

def solve(arr):
    best = -100
    best_range = None
    cur = 0
    left = 0

    for right, x in enumerate(arr):
        if cur >= 0:
            cur += x
        else:
            left = right
            cur = x

        if cur > best:
            best = cur
            best_range = (left, right)

        if DEBUG:
            print(f'\ni: {i}')
            print(f'x: {x}')
            print(f'cur: {cur}')
            print(f'range: {(left, right)}')
            print(f'best: {best}')
            print(f'best_range: {best_range}')

    return (best, best_range)

a1, ar1 = solve(a)
b1, br1 = solve(b)

if DEBUG:
    print(f'a1: {a1}')
    print(f'ar1: {ar1}')
    print(f'b1: {b1}')
    print(f'br1: {br1}')

if a1 == b1:
    if ar1[0] == br1[0]:
        assert False
    elif ar1[0] < br1[0]:
        l, r = ar1
        l += 1
        r += 1
        print(l, r)
    else:
        l, r = br1
        l += 1
        r += 1
        print(l, r)
elif a1 > b1:
    l, r = ar1
    l += 1
    r += 1
    print(l, r)
elif b1 > a1:
    l, r = br1
    l += 1
    r += 1
    print(l, r)
else:
    assert False
