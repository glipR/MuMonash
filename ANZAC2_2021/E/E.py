# TLE on python, should be fine in cpp

# Let G be the graph presented, and D be the maximum distance between two vertices in G

# First off, if we can connect everything, then it will take ceil(log_2(D)) steps
# And, for any vertex u in G, if the largest distance from u is L, then L <= D <= 2L

# So:
# If disconnected, -1
# Else, pick a vertex and compute L
# output ceil(log_2(L))+1 (since this is either log_2(D) or log_2(D) + 1)
import sys
import heapq

n, m = list(map(int, input().split()))
adj = [[] for _ in range(n)]

for _ in range(m):
    i, j = list(map(int, input().split()))
    i -= 1
    j -= 1
    adj[i].append(j)
    adj[j].append(i)

# Now, compute connectivity.
found = [False]*n

looking = [0]
while looking:
    l = looking.pop()
    found[l] = True
    for child in adj[l]:
        if found[child]: continue
        looking.append(child)

if sum(found) != n:
    print(-1)
    sys.exit(0)

# Compute distance
distances = [2 * n for _ in range(n)]

expanded = [False]*n
search = []
heapq.heapify(search)
heapq.heappush(search, (0, 0))

while search:
    distance, node = heapq.heappop(search)
    if expanded[node]: continue
    distances[node] = distance
    expanded[node] = True
    for child in adj[node]:
        if not expanded[child]:
            heapq.heappush(search, (distance + 1, child))

m_dist = max(distances)

i = 0
while 1 << i < m_dist:
    i += 1

print(i+1)
