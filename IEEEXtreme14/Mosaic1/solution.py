import math
n, cb, cp = list(map(int, input().split()))

b = 0
p = 0

for x in range(n):
    bi, pi = list(map(int, input().split()))
    b += bi
    p += pi

print(int(math.ceil(b / 10) * cb + math.ceil(p / 10) * cp))
