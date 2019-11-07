import sys

n, k = 0, 0
nodes = []
workers = []
with open(sys.argv[1], 'r') as f:
    n, k = map(int, f.readline().strip().split())
    for x in range(n):
        parent, *materials = map(int, f.readline().strip().split())
        nodes.append([parent, materials])
    workers = list(map(int, f.readline().strip().split()))

with open(sys.argv[2], 'r') as f:
    r1 = f.readline().strip()
    if r1 == "-1":
        print("GOOD")
    else:
        bad = False
        assignments = [tuple(map(int, r1.split()))]
        for x in range(k-1):
            assignments.append(tuple(map(int, f.readline().strip().split())))
        matched = [False]*n
        for x in range(k):
            a, b = assignments[x]
            if a == 0 and b == 0: continue
            if nodes[a-1][0] != b:
                a, b = b, a
            if nodes[a-1][0] != b:
                bad = True
                break
            matched[a-1] = True
            if workers[x] not in nodes[a-1][1]:
                bad = True
                break
        if not bad and sum(matched) >= n - 1:
            print("GOOD")
        else:
            print("BAD")

