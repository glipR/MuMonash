import math
c, n, p, w = list(map(int, input().split()))

lo = 0
hi = n+1
while hi - lo > 1:
    mid = (hi + lo) // 2
    # Can we fit mid tables in the slot.
    if mid * c > w:
        hi = mid
    elif mid + math.ceil((w - mid * c) / p) <= n:
        lo = mid
    else:
        hi = mid
print(lo)
