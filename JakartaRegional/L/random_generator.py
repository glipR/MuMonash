import random
import itertools

n = random.randint(3, 2000)

# generate a random tree with n vertices rooted at vertex 0.
parent = [random.randint(1, n-1)] + [random.randint(0, i-1) for i in range(1, n)]
# shuffle the vertices
mapping = itertools.permutations(range(n)).__next__()

tree = [-1]*n
for i, x in enumerate(mapping):
    tree[x] = mapping[parent[i]]

# num workers, 4/5 chance valid amount.
workers = random.randint(max(0, int(n - (2000 - n) / 5)), 2000)

# Materials are exponentially more popular - hopefully more actual solutions.
materials = list(set([random.randint(1, 10^9) for _ in range(1000)]))

worker_materials = [-1]*workers
for x in range(workers):
    for i in range(len(materials)):
        if random.random() > 0.5:
            worker_materials[x] = materials[i]
            break
    else:
        worker_materials[x] = materials[-1]

node_materials = [[] for _ in range(n)]

for x in range(n):
    for i in range(len(materials)):
        if random.random() < pow(2, -i):
            node_materials[x].append(materials[i])

print(n, workers)
for x in range(n):
    print(tree[x] + 1, len(node_materials[x]), ' '.join(map(str, node_materials[x])))

print(' '.join(map(str, worker_materials)))

