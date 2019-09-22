# MuMonash
# BST Solution, Interpolate inbetween.
# Takes about 0.2 seconds in worst case :D

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

# Separate the boys from the men, do some sorting :)
# (index, (m1, m2))
pairs = list(enumerate(zip(multipliers[:-1], multipliers[1:])))
# Sort by m2 / m1
pairs.sort(key=lambda k: k[1][1]/k[1][0])

wait_time = [-1 for _ in range(len(pairs))]

def hard_compute(m1, m2):
    worst, wait = 0, workers[0] * m1
    for w1, w2 in zip(range(len(workers) - 1), range(1, len(workers))):
        if cumulative[w2] * m1 - cumulative[w1] * m2 > wait:
            wait = cumulative[w2] * m1 - cumulative[w1] * m2
            worst = w2
    return worst, wait

def easy_compute(m1, m2, worst):
    if worst == 0:
        return workers[0] * m1
    return cumulative[worst] * m1 - cumulative[worst - 1] * m2

def fill(bot, top, worst):
    for index in range(bot+1, top):
        wait_time[index] = easy_compute(*pairs[index][1], worst)

def binary_search(bottom_worst, top_worst, bottom_index, top_index):
    if bottom_index >= top_index - 1:
        return
    middle_index = (bottom_index + top_index) // 2
    # The icky compute
    mid, wait_time[middle_index] = hard_compute(*pairs[middle_index][1])
    if mid == bottom_worst:
        fill(bottom_index, middle_index, bottom_worst)
    else:
        binary_search(bottom_worst, mid, bottom_index, middle_index)
    if mid == top_worst:
        fill(middle_index, top_index, mid)
    else:
        binary_search(mid, top_worst, middle_index, top_index)

bot, wait_time[0] = hard_compute(*pairs[0][1])
top, wait_time[-1] = hard_compute(*pairs[-1][1])

binary_search(bot, top, 0, len(wait_time) - 1)

print(sum(wait_time) + TOTAL_TIME * multipliers[-1])
