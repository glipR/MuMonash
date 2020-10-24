import math

T = int(input())

for case in range(1, T+1):
    n = int(input())
    p0 = [None]*n
    p1 = [None]*n
    p0_index = 0
    p1_index = 0
    origin_0 = False
    origin_1 = False
    for i in range(n):
        res = input().split()
        x1, x2, y = float(res[0]), float(res[1]), int(res[2])
        if y == -1:
            if x2 == x1 and x1 == 0:
                origin_0 = True
                continue
            p0[p0_index] = (math.atan2(x2, x1), math.atan2(-x2, -x1))
            p0_index += 1
        else:
            if x2 == x1 and x1 == 0:
                origin_1 = True
                continue
            p1[p1_index] = (math.atan2(x2, x1), math.atan2(-x2, -x1))
            p1_index += 1
    # Now. We need to check that an interval of angles will cover just one of the sections.
    mi00 = min(p0[x][0] for x in range(p0_index))
    ma00 = max(p0[x][0] for x in range(p0_index))
    mi10 = min(p1[x][0] for x in range(p1_index))
    ma10 = max(p1[x][0] for x in range(p1_index))
    mi01 = min(p0[x][1] for x in range(p0_index))
    ma01 = max(p0[x][1] for x in range(p0_index))
    mi11 = min(p1[x][1] for x in range(p1_index))
    ma11 = max(p1[x][1] for x in range(p1_index))
    # Apparently the origin doesn't matter?
    # First of all, we need to ensure that p0 and p1 can sit within a pi radian hemidisk
    bad = False
    if ma00 - mi00 <= math.pi:
        for x in range(p1_index):
            if mi00 < p1[x][0] < ma00:
                # All over
                bad = True
                break
        if bad:
            print("NO")
            continue
        # Possible. We need to check that p1 also sits on a hemidisk. 
        if ma10 - mi10 <= math.pi or ma11 - mi11 <= math.pi:
            print("YES")
        else:
            print("NO")
        continue
    elif ma01 - mi01 <= math.pi:
        for x in range(p1_index):
            if mi01 < p1[x][1] < ma01:
                # All over
                bad = True
                break
        if bad:
            print("NO")
            continue
        # Possible. We need to check that p1 also sits on a hemidisk.
        if ma10 - mi10 <= math.pi or ma11 - mi11 <= math.pi:
            print("YES")
        else:
            print("NO")
        continue
    else:
        print("NO")
        continue
    