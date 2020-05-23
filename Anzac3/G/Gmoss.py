a = [1 if x=='B' else -1 for x in input()]
b = [x * -1 for x in a]

def solve(arr):
    best = -100
    best_range = None
    cur = -100

    left = 0
    right = 0

    for i, x in enumerate(arr):
        cur += x

        if cur > 0:
            right += 1
        else:
            left = i
            right = i
            cur = x

        if cur > best:
            best = cur
            best_range = (left, right)

        #print(f'\ni: {i}')
        #print(f'x: {x}')
        #print(f'cur: {cur}')
        #print(f'best: {best}')
        #print(f'best_range: {best_range}')

    return (best, best_range)

a1, ar1 = solve(a)
b1, br1 = solve(b)

#print(f'a1: {a1}')
#print(f'ar1: {ar1}')
#print(f'b1: {b1}')
#print(f'br1: {br1}')

if a1 == b1:
    if ar1[0] < br1[0]:
        l, r = ar1
        l += 1
        r += 1
        print(l, r)
    else:
        l, r = br1
        l += 1
        r += 1
        print(l, r)
else:
    if a1 > b1:
        l, r = ar1
        l += 1
        r += 1
        print(l, r)
    else:
        l, r = br1
        l += 1
        r += 1
        print(l, r)
