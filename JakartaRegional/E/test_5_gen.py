n = 100000
l = 1
r = 1000000000
k = 1000000000

print(n,l,r,k)

ans = ""
for i in range(n):
    ans += str(r-i) + " "
print(ans)
