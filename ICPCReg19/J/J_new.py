import bisect

x = int(input())
values = [tuple(map(int,input().split())) for y in range(x)]
s1 = sorted([(v1[0] - v1[1], v1[0] + v1[1], i) for i, v1 in enumerate(values)])
s2 = []
ptr = 0
current = 1
final = [-1]*x
while ptr < len(s1) or s2:
    while ptr < len(s1) and current >= s1[ptr][0]:
        bisect.insort(s2, [s1[ptr][1], s1[ptr][0], s1[ptr][2]])
        ptr += 1
    if len(s2) == 0:
        current = max(current, s1[ptr][0])
        continue
    final[s2[0][2]] = current
    del s2[0]
    current += 1
print(' '.join(map(str, final)))

