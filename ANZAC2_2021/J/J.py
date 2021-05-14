import heapq

# Since we can turn around as soon as we find a new street, we just need to find all streets we can reach; this is the maximum number of interesting paths.

intersections, streets, lower, upper = list(map(int, input().split()))
# i = verts
# s = edges
# the lower bound doesn't matter, we can turn around as much as we want.

edges = [list(map(int, input().split())) for _ in range(streets)]

adj = [[] for _ in range(intersections)]

for i, j, l in edges:
    adj[i].append((j, l))
    adj[j].append((i, l))

dist = [upper + 1]*intersections
dist[0] = 0
expanded = [False]*intersections

expanding = []
heapq.heapify(expanding)
heapq.heappush(expanding, (0, 0))
# Djikstra to calculate shortest paths
while expanding:
    d, node = heapq.heappop(expanding)
    if expanded[node]:
        continue
    expanded[node] = True
    dist[node] = d
    for neighbour, length in adj[node]:
        if not expanded[neighbour]:
            heapq.heappush(expanding, (d + length, neighbour))

paths = 0

for i, j, l in edges:
    # Can we get here and back with some time spare?
    if 2*dist[i] < upper or 2*dist[j] < upper:
        paths += 1

print(paths)