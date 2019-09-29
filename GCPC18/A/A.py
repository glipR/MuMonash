# MuMonash
# In the middle of working.

h, w = map(int, input().split())

neighbours = [
    [[] for _ in range(w)]
    for __ in range(h)
]

random = input()
# We don't care about the top row.
for x in range(h):
    line = input()
    for y1 in range(w):
        if line[2*y1 + 1] != '_':
            # Above and below are connected.
            neighbours[x+1][y1].append((x, y1))
            neighbours[x][y1].append((x+1, y1))
    for y2 in range(1, w):
        if line[2*y2] != '|':
            neighbours[x][y2-1].append((x, y2))
            neighbours[x][y2].append((x, y2-1))

m = int(input())
modules = [
    [[] for _ in range(w)]
    for __ in range(h)
]
first = True
start = None
end = None
for i in range(m):
    x, y = list(map(int, input().split()))
    x -= 1
    y -= 1
    modules[x][y].append(i)
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

marked[start[0]][start[1]] = True
indicies = [-1] * m

class Tree:
    # A tree is a node
    def __init__(self, distance, point):
        self.point = point
        self.distance = distance
        self.children = []
        self.level = 0
        self.parent = self

    def add_child(self, child):
        child.parent = self
        child.level = self.level + 1
        self.children.append(child)

    def enumerate_nodes(self):
        nodes = [self]
        for child in self.children:
            nodes.extend(child.enumerate_nodes())
        for i in range(len(nodes)):
            nodes[i].index = i
        return nodes

    def __str__(self):
        TAB = '  '
        children = [TAB + str(child).replace('\n', '\n'+TAB) for child in self.children]
        return f'{self.point}({self.index}) : {self.distance}' + (
            '\n' + '\n'.join(children)
            if children else ''
        )

class LCA:

    LOGN = 20 # Good for n <= 10^6

    def __init__(self, n, enumerated):
        self.n = n
        self.nodes = enumerated
        self.ancestors = [[-1 for _ in range(self.LOGN)] for __ in range(self.n)]
        # do build
        for i in range(self.n):
            self.ancestors[i][0] = self.nodes[i].parent.index
        self.ancestors[0][0] = -1
        # No parent.
        for k in range(1, self.LOGN):
            for i in range(self.n):
                if self.ancestors[i][k-1] != -1:
                    self.ancestors[i][k] = self.ancestors[self.ancestors[i][k-1]][k-1]

    def query(self, idx, idy):
        if self.nodes[idx].level > self.nodes[idy].level:
            idx, idy = idy, idx
        for k in range(self.LOGN-1, -1, -1):
            if (self.nodes[idy].level - (1 << k)) >= self.nodes[idx].level:
                idy = self.ancestors[idy][k]
        if (idx == idy):
            return idx
        for k in range(self.LOGN-1, -1, -1):
            if self.ancestors[idx][k] == self.ancestors[idy][k]:
                continue
            idx = self.ancestors[idx][k]
            idy = self.ancestors[idy][k]
        return self.nodes[idx].parent.index


def bfs(x, y, parent, dist=0):
    new_points = []
    for newx, newy in neighbours[x][y]:
        if marked[newx][newy] is False:
            marked[newx][newy] = True
            new_points.append((newx, newy))
    if len(neighbours[x][y]) > 2 or modules[x][y]:
        child = Tree(dist, (x, y))
        parent.add_child(child)
        for module in modules[x][y]:
            indicies[module] = child
        for newx, newy in new_points:
            bfs(newx, newy, child, dist+1)
    else:
        for newx, newy in new_points:
            bfs(newx, newy, parent, dist+1)

root = Tree(0, start)
bfs(*start, root)
nodes = root.enumerate_nodes()
lca = LCA(len(nodes), nodes)

# print(root)
# print(nodes[lca.query(indicies[1].index, indicies[2].index)].point)

total = 0
for i in range(1, m):
    parent = nodes[lca.query(indicies[i-1].index, indicies[i].index)]
    addition = indicies[i-1].distance + indicies[i].distance - 2 * parent.distance
    # print(indicies[i-1].distance, indicies[i].distance, parent.distance, parent.point, addition)
    total += addition

print(total)
