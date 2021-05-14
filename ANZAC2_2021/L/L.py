# idea: start with everything sorted on the left
# then move every element from the right to left, to minimise the cost of movement.

n, k = list(map(int, input().split()))
# [0] = position (0-indexed), [1] = weight
statues = list(sorted([(lambda a, b: (int(a)-1, int(b)))(*input().split()) for _ in range(k)], key=lambda p: p[1]))
# everything to the left
current = list(range(k)) + [-1]*(n-k)
for i in range(k-1, -1, -1):
    # try moving statue i
    cur = i
    while cur < n - k + i:
        cost = 0
        cur2 = cur
        while current[cur2] != -1:
            if statues[current[cur2]][0] <= cur2:
                # We will be shifted further away
                cost += statues[current[cur2]][1]
            else:
                # We are shifting towards
                cost -= statues[current[cur2]][1]
            cur2 += 1
        if cost >= 0:
            break
        # Optimal shift, do it.
        cur2 = cur
        storing = -1
        while cur2 == cur or storing != -1:
            storing, current[cur2] = current[cur2], storing
        cur += 1

actual_cost = 0
# Now in optimal position. Calculation distances
for i in range(n):
    if current[i] != -1:
        actual_cost += abs(i - statues[current[i]][0]) * statues[current[i]][1]
print(actual_cost)
