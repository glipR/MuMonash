ints = list(map(int, input().split()))

found1 = False

firstv, secondv = None, None
firsti, secondi = None, None

for i in range(10):
    if ints[i] == 0:
        continue
    if found1:
        secondv = ints[i]
        secondi = i
    else:
        found1 = True
        firstv = ints[i]
        firsti = i

diffv = secondv - firstv
difft = secondi - firsti
if (diffv / difft == diffv // difft):
    # Good
    nums = []
    for i in range(10):
        nums.append(firstv + (diffv // difft) * (i - firsti))
    print(' '.join(list(map(str, nums))))
else:
    print(-1)
