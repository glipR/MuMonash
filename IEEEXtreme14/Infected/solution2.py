n, m = list(map(int, input().split()))

adjacency = [[] for _ in range(n)]

edges = []

for i in range(m):
    a, b = list(map(int, input().split()))
    a -= 1
    b -= 1
    adjacency[a].append(b)
    adjacency[b].append(a)
    edges.append((a, b))

# Create a DFS tree from vertex 0
parent = [-1] * n
children = [[] for _ in range(n)]
q = [0]
while q.qsize():
    v = q[-1]
    del q[-1]
    for adj in adjacency[v]:
        if parent[adj] == -1:
            parent[adj] = v
            children[v].append(adj)
            q.append(adj)

lvl = [-1] * n
elements = [0]
l = 0
while elements:
    new_elements = []
    for e in elements:
        lvl[e] = l
        for child in children[e]:
            new_elements.append(child)
    l += 1
    elements = new_elements

red_lvl = [lvl[x] for x in range(n)]
for a, b in edges:
    if abs(lvl[a] - lvl[b]) == 1:
        continue
    if lvl[a] < lvl[b]:
        red_lvl[b] = min(red_lvl[b], lvl[a])
    else:
        red_lvl[a] = min(red_lvl[a], lvl[b])

def recursive_red_lvl(root):
    for child in children[root]:
        recursive_red_lvl(child)
        red_lvl[root] = min(red_lvl[root], red_lvl[child])

blue = [red_lvl[x] >= lvl[x] for x in range(n)]





