n = int(input())

positions = [[] for _ in range(n)]

for x in range(n):
    print(2*x+1, 2*x+2)
    result = input().strip()
    if result == "MATCH":
        continue
    a, b = map(int, result.split())
    positions[a-1].append(2*x+1)
    positions[b-1].append(2*x+2)

for x in range(n):
    for y in range(len(positions[x])//2):
        print(min(positions[x][2*y], positions[x][2*y+1]), max(positions[x][2*y], positions[x][2*y+1]))

print(-1)
