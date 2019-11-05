n, k = map(int, input().split())

print(n, k)

for i in range(1, n+1):
    tar = i + 1 if i < n else 1
    print(tar, 1, 1)

print(' '.join(['1' for _ in range(k)]))

