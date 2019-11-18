def convert(z):
    return int(''.join(z.split('.')))
    #return int(float(z) * 100)

x = list(map(convert, input().split()))

M1 = min(x)
M2 = max(x)
S = sum(x)

target = int(''.join(input().split('.'))) * 3

if S - M1 <= target:
    print("infinite")
elif S - M2 > target:
    print("impossible")
else:
    ans = str(target - (S - M1 - M2))
    print("{}{}{}".format(ans[:-2], '.', ans[-2:]))
    #print("%.2f"%((target - (S - M1 - M2))/100))
