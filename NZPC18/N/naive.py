# MuMonash
# Naive Solution, try everything
# Takes about a minute in worst case.

def read_ints():
    return list(map(int, input().split()))

n, m = read_ints()

workers = [-1] * n
multipliers = [-1] * m
for i in range(n):
    workers[i] = int(input())
for i in range(m):
    multipliers[i] = int(input())

tot = 0
cumulative = [-1] * n
for x in range(n):
    tot += workers[x]
    cumulative[x] = tot
TOTAL_TIME = tot

# m1 = 3, m2= 1
# w = 1 1 2
# |---| |---| |------|
# -----x----- |-| |-| |--|
# x + m2*w1 = m1*w2
# x = m1*w2 - m2*w1

total = 0
for m1, m2 in zip(multipliers[:-1], multipliers[1:]):
    # worker 1 waits for noone but himself.
    wait = workers[0] * m1
    for w1, w2 in zip(range(len(workers) - 1), range(1, len(workers))):
        # How long between w2 finishing on m1 and w2 starting on m2
        wait = max(cumulative[w2] * m1 - cumulative[w1] * m2, wait)
    total += wait
# To get the total wait time, add the time taken to complete the final piece.
total += TOTAL_TIME * multipliers[-1]

print(total)
