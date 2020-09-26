TOTAL = 20000
# First precompute amicability from 0 to 200000
result = [1 for _ in range(TOTAL + 1)]

for x in range(2, TOTAL + 1):
    start = x
    while True:
        start += x
        if start > TOTAL:
            break
        result[start] += x

amicable = [False for _ in range(TOTAL + 1)]
for x in range(1, TOTAL + 1):
    if 1 <= result[x] <= TOTAL and result[x] != x:
        if result[result[x]] == x:
            amicable[x] = True

partial_sum = [0 for _ in range(TOTAL + 1)]
for x in range(1, TOTAL + 1):
    partial_sum[x] = partial_sum[x-1] + amicable[x]

n = int(input())
for x in range(n):
    l, u = list(map(int, input().split()))
    print("Amicable numbers between " + str(l) + " and " + str(u))
    pairs = []
    for x in range(l, u+1):
        if amicable[x] and result[x] > x and l <= result[x] <= u:
            pairs.append((x, result[x]))
    if pairs:
        print("\n".join([' '.join((str(x[0]), str(x[1]))) for x in pairs]))
    else:
        print("None")

 