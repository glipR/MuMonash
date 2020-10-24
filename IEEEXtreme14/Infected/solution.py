from queue import Queue

n, m = list(map(int, input().split()))

adjacency = [[] for _ in range(n)]

for _ in range(m):
    a, b = list(map(int, input().split()))
    a -= 1
    b -= 1
    adjacency[a].append(b)
    adjacency[b].append(a)

components = [[-1 for _ in range(n)] for __ in range(n)]

for v in range(n):
    # Remove v from the graph.
    comp = 0
    cur_vertex = 0
    while cur_vertex < n:
        # BFS from cur_vertex.
        if components[v][cur_vertex] != -1 or cur_vertex == v:
            cur_vertex += 1
            continue
        components[v][cur_vertex] = comp
        found = [False] * n
        q = Queue()
        q.put(cur_vertex)
        while q.qsize():
            res = q.get()
            for adj in adjacency[res]:
                if adj == v:
                    continue
                if components[v][adj] == -1:
                    components[v][adj] = comp
                    q.put(adj)
        comp += 1
        cur_vertex += 1

q = int(input())
for x in range(q):
    f, s = list(map(int, input().split()))
    total = 2
    for v in range(n):
        if v in [f-1, s-1]: continue
        if components[v][f-1] != components[v][s-1]:
            total += 1
    print(total)
