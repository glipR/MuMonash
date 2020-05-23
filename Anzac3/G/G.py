letters = input()

b_counts = [0]

cur = 0
for let in letters:
    if let == 'B':
        cur += 1
    else:
        cur -= 1
    b_counts.append(cur)

# Find max/min.

cmin = None
cmax = None

for i, amount in enumerate(b_counts):
    if cmin is None or amount < cmin[0]:
        cmin = (amount, i)
    if cmax is None or amount > cmax[0]:
        cmax = (amount, i)

s = min(cmax[1], cmin[1])
e = max(cmax[1], cmin[1])

print(s + 1, e)
