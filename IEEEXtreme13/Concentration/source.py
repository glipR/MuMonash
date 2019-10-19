n = int(input())

positions = [[] for i in range(n+5)]

for i in range(n):
    print(2*i + 1, 2*i + 2)
    
    s = input().strip()
    
    if s == "MATCH":
        continue
    
    a, b = map(int, s.split())
    
    positions[a].append(2*i + 1)
    positions[b].append(2*i + 2)
    
for i in range(1, n+1):
    for j in range(0, len(positions[i])-1, 2):
        print(positions[i][j], positions[i][j+1])

print(-1)
