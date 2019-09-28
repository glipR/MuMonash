# MuMonash
# In the middle of working.

h, w = map(int, input().split())

neighbours = [
    [[] for _ in range(w)]
    for __ in range(h)
]

for x in range(h+1):
    line = input()
    for y1 in range(w):
        if line[2*y1 + 1] != '_' and 0 < x <= h:
            # Above and below are connected.
            neighbours[x-1][y1].append((x, y1))
            neighbours[x][y1].append((x-1, y1))
    for y2 in range(w+1):
        if line[2*y2] != '|' and 0 < y2 < w:
            neighbours[x][y2-1].append((x, y2))
            neighbours[x][y2].append((x, y2-1))

m = int(input())
modules = [
    [0 for _ in range(w)]
    for __ in range(h)
]
first = True
start = None
end = None
for _ in range(m):
    x, y = int(input())
    x -= 1
    y -= 1
    modules[x][y] += 1
    if first:
        start = (x, y)
    end = (x, y)
    first = False

# Pathfind from start to end. BFS
points = [start]
marked = [
    [False for _ in range(w)]
    for _ in range(h)
]

def bfs(x, y):
    for newx, newy in neighbours[x][y]:
        if marked[newx][newy] is False:
            marked[newx][newy] = marked[x][y] + modules[newx][newy]
            bfs(newx, newy)

bfs(*start)

print(marked[end[0]][end[1]])
