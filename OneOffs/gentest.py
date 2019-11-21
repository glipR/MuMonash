import random

b = random.randint(0, 1e1)
n = random.randint(0, b)

print(n, b)

# Generate arrows.
data = [
    [False for _ in range(b+1)] for __ in range(b+1)
]

a = 0
while a < n:
    bo = random.randint(0, 1)
    y = random.randint(0, b)
    if bo:
        if sum(data[y]) > b: continue
    else:
        if sum([data[z][y] for z in range(b+1)]): continue
    loc1 = random.choice([x for x in range(b+1) if not (data[y][x] if bo else data[x][y])])
    loc2 = loc1
    while loc2 == loc1:
        loc2 = random.randint(0, b)
    if loc2 > loc1:
        ans = None
        if data[y][loc1+1] if bo else data[loc1+1][y]: continue
        for x in range(2, loc2 - loc1 + 1):
            if data[y][loc1 + x] if bo else data[loc1 + x][y]:
                ans = loc1 + x - 1
                break
        else:
            ans = loc2
        if bo:
            print(y, loc1, y, loc2)
            for x in range(loc1, loc2+1):
                data[y][x] = True
        else:
            print(loc1, y, loc2, y)
            for x in range(loc1, loc2+1):
                data[x][y] = True
    else:
        ans = None
        if data[y][loc1-1] if bo else data[loc1-1][y]: continue
        for x in range(2, loc1 - loc2 + 1):
            if data[y][loc1 - x] if bo else data[loc1 - x][y]:
                ans = loc1 - x + 1
                break
        else:
            ans = loc2
        if bo:
            print(y, loc1, y, loc2)
            for x in range(loc2, loc1+1):
                data[y][x] = True
        else:
            print(loc1, y, loc2, y)
            for x in range(loc2, loc1+1):
                data[x][y] = True
    a += 1

q = int(10)

print(q)
for x in range(q):
    print(random.randint(0, b), random.randint(0, b), 'LRUD'[random.randint(0, 3)], random.randint(0, 1e2))

