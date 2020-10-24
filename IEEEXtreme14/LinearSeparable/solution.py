EPS = 1e-8
import sys
sys.setrecursionlimit(20000)
import math

T = int(input())

for case in range(1, T+1):
    n = int(input())
    p0 = [None]*n
    p1 = [None]*n
    p0_index = 0
    p1_index = 0
    for i in range(n):
        res = input().split()
        x1, x2, y = float(res[0]), float(res[1]), int(res[2])
        if y == -1:
            if x2 == x1 and x1 == 0:
                continue
            # Note the problem is the same if you invert all of the points, and on at least one of these cases the positive x axis will not intersect the section containing p0.
            p0[p0_index] = (math.atan2(x2, x1), math.atan2(x2, -x1))
            p0_index += 1
        else:
            if x2 == x1 and x1 == 0:
                continue
            p1[p1_index] = (math.atan2(x2, x1), math.atan2(x2, -x1))
            p1_index += 1
    # Now. We need to check that an interval of angles will cover just one of the sections.
    try:
        if p0_index == 0:
            mi10 = min(p1[x][0] for x in range(p1_index))
            ma10 = max(p1[x][0] for x in range(p1_index))
            mi11 = min(p1[x][1] for x in range(p1_index))
            ma11 = max(p1[x][1] for x in range(p1_index))
            if ma10 - mi10 < math.pi + EPS or ma11 - mi11 < math.pi + EPS:
                print("YES")
            else:
                print("NO")
            continue
        elif p1_index == 0:
            mi00 = min(p0[x][0] for x in range(p0_index))
            ma00 = max(p0[x][0] for x in range(p0_index))
            mi01 = min(p0[x][1] for x in range(p0_index))
            ma01 = max(p0[x][1] for x in range(p0_index))
            if ma00 - mi00 < math.pi + EPS or ma01 - mi01 < math.pi + EPS:
                print("YES")
            else:
                print("NO")
            continue
        mi00 = min(p0[x][0] for x in range(p0_index))
        ma00 = max(p0[x][0] for x in range(p0_index))
        mi01 = min(p0[x][1] for x in range(p0_index))
        ma01 = max(p0[x][1] for x in range(p0_index))
        mi10 = min(p1[x][0] for x in range(p1_index))
        ma10 = max(p1[x][0] for x in range(p1_index))
        mi11 = min(p1[x][1] for x in range(p1_index))
        ma11 = max(p1[x][1] for x in range(p1_index))
        bad = False
        if ma00 - mi00 < math.pi + EPS:
            for x in range(p1_index):
                if mi00 + EPS < p1[x][0] < ma00 - EPS:
                    # All over
                    bad = True
                    break
            if bad:
                print("NO")
                continue
            # Possible. We need to check that p1 also sits on a hemidisk. 
            if ma10 - mi10 < math.pi + EPS or ma11 - mi11 < math.pi + EPS:
                print("YES")
            else:
                print("NO")
            continue
        elif ma01 - mi01 < math.pi + EPS:
            for x in range(p1_index):
                if mi01 + EPS < p1[x][1] < ma01 - EPS:
                    # All over
                    bad = True
                    break
            if bad:
                print("NO")
                continue
            # Possible. We need to check that p1 also sits on a hemidisk.
            if ma10 - mi10 < math.pi + EPS or ma11 - mi11 < math.pi + EPS:
                print("YES")
            else:
                print("NO")
            continue
        else:
            print("NO")
            continue
    except:
        print("YES")