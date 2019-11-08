n = 400000
k = 8000

each_team = 50

print(n, k)

for i in range(k):
    for j in range(each_team):
        print(i + 1, end=' ')

print()
