n, a, b = map(int, input().split())

ans = -1
for i in range(1, 100001):
    if i * a <= n <= i * b:
        ans = i
        break

if ans == -1:
    print("NO")
else:
    print("YES")
    res = [a] * ans
    current = a * ans
    for i in range(len(res)):
        index = len(res) - 1 - i
        if current == n:
            break
        needed = min(n-current, b-a)
        res[index] += needed
        current += needed

    print(' '.join(map(str, res)))
