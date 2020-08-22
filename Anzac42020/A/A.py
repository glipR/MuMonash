v = int(input())
favourites = [0 for x in range(1000)]
max_votes = 0
for x in range(v):
    num = int(input()) - 1
    favourites[num] += 1
    max_votes = max(max_votes, favourites[num])

for num in range(1000):
    if favourites[num] == max_votes:
        print(num+1)
        break
