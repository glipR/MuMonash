from collections import defaultdict

n = int(input())

lines = [None]*n

for x in range(n):
    line = input()
    lines[x] = line[:4] + line[5:9] + line[10:14]

# Create sets
dicts = [
    defaultdict(lambda: 0) for _ in range(12)
]

for x in range(12):
    for y in range(n):
        inp = lines[y][:x] + "?" + lines[y][x+1:]
        dicts[x][inp] += 1

# Count coverings.
total = 0
for x in range(12):
    for k in dicts[x].values():
        total += int(k * (k-1) / 2)

print(total)