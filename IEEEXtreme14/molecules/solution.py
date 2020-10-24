import math

t = int(input())
for case in range(t):
    c, h, o = list(map(int, input().split()))
    best = c + h + o
    # Loop over possible h values.
    for glucose in range(int(math.ceil(max(c/6, h/12, o/6)))):
        po, pc, ph = 6*glucose, 6*glucose, 12*glucose
        current = 0
        if h < ph:
            diff1 = 0
            diff2 = 0
        else:
            diff1 = abs(ph - h) // 2
            diff2 = abs(ph - h) // 2 + 1
        ph1 = ph + diff1 * 2
        ph2 = ph + diff2 * 2
        del ph
        po1 = po + diff1
        po2 = po + diff2
        del po
        current1 = current
        current2 = current
        # 1 state
        current1 += abs(ph1 - h)
        if o < po1:
            diff1 = 0
            diff2 = 0
        else:
            diff1 = abs(po1 - o) // 2
            diff2 = abs(po1 - o) // 2 + 1
        po11 = po1 + diff1 * 2
        po12 = po1 + diff2 * 2
        del po1
        pc11 = pc + diff1
        pc12 = pc + diff2
        current11 = current1
        current11 += abs(po11 - o)
        current11 += abs(pc11 - c)
        current12 = current1
        current12 += abs(po12 - o)
        current12 += abs(pc12 - c)
        best = min(current11, current12, best)
        # 2 state
        current2 += abs(ph2 - h)
        if o < po2:
            diff1 = 0
            diff2 = 0
        else:
            diff1 = abs(po2 - o) // 2
            diff2 = abs(po2 - o) // 2 + 1
        diff1 = abs(po2 - o) // 2
        diff2 = abs(po2 - o) // 2 + 1
        po21 = po2 + diff1 * 2
        po22 = po2 + diff2 * 2
        del po2
        pc21 = pc + diff1
        pc22 = pc + diff2
        current21 = current2
        current21 += abs(po21 - o)
        current21 += abs(pc21 - c)
        current22 = current2
        current22 += abs(po22 - o)
        current22 += abs(pc22 - c)
        best = min(current21, current22, best)
    print(best)

