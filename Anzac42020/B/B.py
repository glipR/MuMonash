import math

triple1 = list(map(int, input().split()))
triple1.sort()
triple2 = list(map(int, input().split()))
triple2.sort()

if triple1 != triple2:
    print("NO")
else:
    if math.pow(triple1[2], 2) == math.pow(triple1[1], 2) + math.pow(triple1[0], 2):
        print("YES")
    else:
        print("NO")