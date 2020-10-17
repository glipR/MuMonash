import math
m, n = list(map(int, input().split()))
total = 0
for _ in range(m):
    total += int(input())

print(int(math.ceil(total / n)))