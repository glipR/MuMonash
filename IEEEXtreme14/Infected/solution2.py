import sys
sys.setrecursionlimit(10000000)

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
size = []
unlabel = []
relabel = [-1]*n
c = 0
comp = [-1] * n
size = []
parent = [-1] * n
children = [[] for _ in range(n)]
clabel = 0
def dfs(root, actual_root):
    global clabel
    comp[root] = c
    relabel[root] = clabel
    unlabel[c].append(root)
    clabel += 1
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
    clabel = 0
    unlabel.append([])
    dfs(cv, cv)
    roots.append(cv)
    size.append(clabel)
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
    
    def __init__(self, number, component):
        self.c = component
        self.n = number
        self.anc = [[-1 for x in range(self.LOGN)] for y in range(self.n)]
        self.anc_b = [[-1 for x in range(self.LOGN)] for y in range(self.n)]

    def build(self):
        for i in range(self.n):
            self.anc[i][0] = relabel[parent[unlabel[self.c][i]]]
            self.anc_b[i][0] = 0
            if parent[unlabel[self.c][i]] != -1:
                if red_lvl[unlabel[self.c][i]] >= lvl[parent[unlabel[self.c][i]]]:
                    self.anc_b[i][0] += 1
        for k in range(1, self.LOGN):
            for i in range(self.n):
                if self.anc[i][k-1] != -1:
                    self.anc[i][k] = self.anc[self.anc[i][k-1]][k-1]
                    if (1 << k) <= lvl[unlabel[self.c][i]]:
                        self.anc_b[i][k] = self.anc_b[i][k-1] + self.anc_b[self.anc[i][k-1]][k-1]
    
    def query(self, u, v):
        total_b = 2
        if (lvl[unlabel[self.c][u]] > lvl[unlabel[self.c][v]]):
            u, v = v, u
        last = -1
        previous = v
        for k in range(self.LOGN-1, -1, -1):
            if (lvl[unlabel[self.c][v]] - (1 << k) >= lvl[unlabel[self.c][u]]):
                previous = v
                total_b += self.anc_b[v][k]
                last = k
                v = self.anc[v][k]
        # Now, check if, from last, root is required.
        unneccessary = 0
        if last != -1:
            for k in range(last):
                previous = self.anc[previous][k]
            # previous is now directly below u.
            if red_lvl[unlabel[self.c][previous]] >= lvl[parent[unlabel[self.c][previous]]]:
                unneccessary = 1
        if u == v:
            return u, total_b - unneccessary
        for k in range(self.LOGN-1, -1, -1):
            if (self.anc[u][k] == self.anc[v][k]): continue
            total_b += self.anc_b[u][k] + self.anc_b[v][k]
            u = self.anc[u][k]
            v = self.anc[v][k]
        total_b += 1
        if red_lvl[unlabel[self.c][u]] < lvl[parent[unlabel[self.c][u]]] and red_lvl[unlabel[self.c][v]] < lvl[parent[unlabel[self.c][v]]]:
            total_b -= 1

        return parent[unlabel[self.c][u]], total_b

lcas = []
for root in roots:

    obj = LCA(size[comp[root]], comp[root])
    obj.build()
    lcas.append(obj)

q = int(input())
for x in range(q):
    f, s = list(map(int, input().split()))
    f -= 1
    s -= 1
    _, blues = lcas[comp[f]].query(relabel[f], relabel[s])
    print(blues)
