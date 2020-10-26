from decimal import *
getcontext().prec = 64

n, m, r, c = list(map(int, input().split()))

scores = [[0 for _ in range(c)] for __ in range(r)]

for x in range(r):
    line = input().split()
    for y in range(c):
        scores[x][y] = int(line[y])

total_score = sum(sum(scores[x]) for x in range(r))

p = 18

full_h = n // r
full_v = m // c
cut_h = n % r
cut_v = m % c
total = Decimal(full_h)
total *= Decimal(full_v)
total *= Decimal(total_score)

best = Decimal(total_score) * Decimal(full_h+1) * Decimal(full_v+1)
# Calculate the overstep on each side.
for x in range(r):
    for y in range(c):
        # What if we started with this at the top left corner?
        # Figure out cuts.
        corner_cost = 0
        h_cost = 0
        v_cost = 0
        for a in range(cut_h):
            for b in range(cut_v):
                corner_cost += scores[(x+a) % r][(y+b) % c]
        for a in range(cut_h):
            for b in range(c):
                h_cost += scores[(x+a) % r][b]
        for a in range(r):
            for b in range(cut_v):
                v_cost += scores[a][(y+b) % c]
        corner_dec = Decimal(corner_cost)
        h_dec = Decimal(h_cost)
        v_dec = Decimal(v_cost)
        h_dec *= Decimal(full_v)
        v_dec *= Decimal(full_h)
        best = min(best, corner_dec + h_dec + v_dec)

res = best + total
print(str(res))
