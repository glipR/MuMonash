n, m = map(int, input().split())
letters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'[:m]
amount = 0
for x in range(n):
    word = input()
    if len(set(word)) == len(word) and all(x in letters for x in word): amount += 1
print(amount)
