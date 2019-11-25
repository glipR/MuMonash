from collections import defaultdict
names = int(input())
inp = [input().split() for x in range(names)]
choice = []
res = defaultdict(lambda: [])
for x, word in enumerate(inp):
    choice.append(False)
    res[word[0][:3]].append(x)

while True:
    changes = []
    for key in res.keys():
        if len(res[key]) > 1:
            # All choice = False options must be changed
            remove = []
            for i, index in enumerate(res[key]):
                if choice[index]: continue
                remove.append(i)
                choice[index] = True
                changes.append((inp[index][0][:2] + inp[index][1][0], index))
            for i in remove[::-1]:
                del res[key][i]
    if len(changes) == 0: break
    for word, i in changes:
        res[word].append(i)

bad = False
for key in res.keys():
    if len(res[key]) > 1: bad = True

if bad:
    print("NO")
else:
    print("YES")
    for i in range(names):
        if choice[i]:
            print(inp[i][0][:2] + inp[i][1][0])
        else:
            print(inp[i][0][:3])
