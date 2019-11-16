import random

n, k = map(int, input().split())

print(n, k)

for i in range(n):
    print(max(1, int(random.random() * 10)), 10, 10000000000)

