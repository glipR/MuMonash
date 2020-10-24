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
roots = []
c = 0
comp = [-1] * n
parent = [-1] * n
children = [[] for _ in range(n)]
def dfs(root, actual_root):
    comp[root] = c
    for child in adjacency[root]:
        if parent[child] == -1 and child != actual_root:
            parent[child] = root
            children[root].append(child)
            dfs(child, actual_root)

cv = 0
while cv < n:
    if comp[cv] != -1:
        cv += 1
        continue
    dfs(cv, cv)
    roots.append(cv)
    cv += 1
    c += 1

lvl = [-1] * n
for root in roots:
    elements = [root]
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
for root in roots:
    recursive_red_lvl(root)

class LCA:

    LOGN = 20
    
    def __init__(self, number, parents, level):
        self.n = number
        self.par = parents
        self.lvl = level
        self.anc = [[-1 for x in range(self.LOGN)] for y in range(self.n)]
        self.anc_b = [[-1 for x in range(self.LOGN)] for y in range(self.n)]

    def build(self):
        for i in range(self.n):
            self.anc[i][0] = self.par[i]
            self.anc_b[i][0] = 0
            if self.par[i] != -1:
                if red_lvl[i] >= lvl[self.par[i]]:
                    self.anc_b[i][0] += 1
        for k in range(1, self.LOGN):
            for i in range(self.n):
                if self.anc[i][k-1] != -1:
                    self.anc[i][k] = self.anc[self.anc[i][k-1]][k-1]
                    if (1 << k) <= self.lvl[i]:
                        self.anc_b[i][k] = self.anc_b[i][k-1] + self.anc_b[self.anc[i][k-1]][k-1]
    
    def query(self, u, v):
        total_b = 2
        if (self.lvl[u] > self.lvl[v]):
            u, v = v, u
        inc_last = False
        for k in range(self.LOGN-1, -1, -1):
            if (self.lvl[v] - (1 << k) >= self.lvl[u]):
                total_b += self.anc_b[v][k]
                if k == 0 and self.anc_b[v][k] > 0:
                    inc_last = True
                v = self.anc[v][k]
        if u == v:
            return u, total_b - int(inc_last)
        for k in range(self.LOGN-1, -1, -1):
            if (self.anc[u][k] == self.anc[v][k]): continue
            total_b += self.anc_b[u][k] + self.anc_b[v][k]
            u = self.anc[u][k]
            v = self.anc[v][k]
        total_b += 1
        if red_lvl[u] < self.lvl[self.par[u]] and red_lvl[v] < self.lvl[self.par[v]]:
            total_b -= 1

        return self.par[u], total_b

lcas = []
for root in roots:

    obj = LCA(n, parent, lvl)
    obj.build()
    lcas.append(obj)

q = int(input())
for x in range(q):
    f, s = list(map(int, input().split()))
    f -= 1
    s -= 1
    top, blues = lcas[comp[f]].query(f, s)
    print(blues)
