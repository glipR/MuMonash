import math
import sys

sys.setrecursionlimit(1000000000)

n = int(input())
for x in range(n):
    w, g, h, r = list(map(int, input().split()))
    if g == r or h == r:
        mindist = math.sqrt(math.pow(abs(g-h), 2) + math.pow(w, 2))
        print("{0:.8f} {1:.8f}".format(mindist, mindist))
    else:
        # Binary search for the 0 derivative point.
        lo = -1
        hi = w + 1
        h_r = math.pow(h-r, 2)
        g_r = math.pow(g-r, 2)
        while True:
            mid = (hi + lo) / 2
            derivative = mid / (math.sqrt(g_r + math.pow(mid, 2))) - (w-mid) / (math.sqrt(h_r + math.pow(w-mid, 2)))
            if derivative < 0:
                lo = mid
            else:
                hi = mid
            md1 = math.sqrt(g_r + math.pow(hi, 2)) + math.sqrt(h_r + math.pow(w-hi, 2))
            md2 = math.sqrt(g_r + math.pow(lo, 2)) + math.sqrt(h_r + math.pow(w-lo, 2))
            if abs(md1 - md2) < 0.000000001:
                break
        mindist = math.sqrt(math.pow(abs(g-h), 2) + math.pow(w, 2))
        dist = math.sqrt(g_r + math.pow(lo, 2)) + math.sqrt(h_r + math.pow(w-lo, 2))
        print("{0:.8f} {1:.8f}".format(mindist, dist))