from math import sqrt
a, b, c, d = map(int, input().split())

top = a*c
bottom = b*d*2

if top % bottom == 0:
    print(1)
else:
    print(0)
