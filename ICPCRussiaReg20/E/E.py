t = int(input())

for _ in range(t):
    a, b, c, d = list(sorted(list(map(int, input().split()))))
    print(a * c)
