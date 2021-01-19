import heapq
from collections import defaultdict

t = int(input())

for _ in range(t):
    n, m, k = list(map(int, input().split()))
    edges = []
    old_weights = []
    adj = defaultdict(list)
    for __ in range(m):
        x, y, s = list(map(int, input().split()))
        valid = s >= k
        old_weights.append(s)
        s = max(s-k, 0)
        edges.append((s, (x-1, y-1), valid))
        adj[x-1].append((s, y-1, valid))
        adj[y-1].append((s, x-1, valid))

    # First, just find the MST.
    solidified = [False] * n
    c_vert = 0
    c_edges = []
    valid = False
    heapq.heapify(c_edges)
    for x in range(n-1):
        solidified[c_vert] = True
        for weight, end, v in adj[c_vert]:
            if not solidified[end]:
                heapq.heappush(c_edges, (weight, end, v))
        while True:
            r = heapq.heappop(c_edges)
            w, loc, v = r
            if not solidified[loc]: break

        valid |= v
        c_vert = loc
    
    if valid:
        print(0)
        continue
    
    # Otherwise, just start with the smallest valid edge.
    best = (-1, 1e10)
    for x, (s, (p1, p2), v) in enumerate(edges):
        if not v: continue
        if s < best[1]:
            best = (x, s)
    
    # If best == -1, there are no roads >= k. Just add the largest one.
    if best[0] == -1:
        largest = -1
        for s in old_weights:
            largest = max(largest, s)
        print(k - largest)
        continue

    # Find the MST.
    solidified = [False] * n
    solidified[edges[best[0]][1][0]] = True
    c_vert = edges[best[0]][1][1]
    c_edges = adj[edges[best[0]][1][0]]
    heapq.heapify(c_edges)
    total_expended = best[1]
    valid = False
    heapq.heapify(c_edges)
    for x in range(n-2):
        solidified[c_vert] = True
        for weight, end, v in adj[c_vert]:
            if not solidified[end]:
                heapq.heappush(c_edges, (weight, end, v))
        while True:
            w, loc, v = heapq.heappop(c_edges)
            if not solidified[loc]: break
        total_expended += w
        valid |= v
        c_vert = loc
    print(total_expended)    