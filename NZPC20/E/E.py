n, d = list(map(int, input().split()))

bec = int(input())
cas = int(input())

for x in range(d):
    l, r = list(map(int, input().split()))
    if l >= bec and bec != 0:
        l += 1
    if r >= cas and cas != 0:
        r += 1
    if l + r == n + 1:
        print("Day " + str(x+1) + " ALERT")
    else:
        print("Day " + str(x+1) + " OK")
