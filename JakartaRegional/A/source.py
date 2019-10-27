n = int(input())
l = list(map(int, input().split()))

print(' '.join(map(str, [l[i] for i in range(-1, n-1)])))
