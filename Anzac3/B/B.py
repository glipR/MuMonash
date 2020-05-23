probs = list(map(float, input().split()))

min_change = None

for i in range(6):
    #print(f'looking at {i}')
    # 3.5 = r*p1 + 2*p2 + ...
    # 3.5 - 2*p2 - 3*p3 - ... = r*p1
    # r = (1/p1) * (3.5 - 2*p2 - ...)
    # min |r-i+1|

    r = 3.5
    for j in range(6):
        if i==j:
            continue
        r -= (j+1)*probs[j]

    r /= probs[i]
    #print(f'r: {r}')
    change = abs(r-i-1)
    #print(f'change: {change}')
    if min_change is None or change < min_change:
        min_change = change

rounded = round(min_change, 3)
print('{:.3f}'.format(rounded))
