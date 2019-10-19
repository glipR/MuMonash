n = int(input())

ans = ""

import random

for i in range(n):
    if random.random() > 0.5:
        ans += 'y'
    else:
        ans += 'Y'

print(ans)
