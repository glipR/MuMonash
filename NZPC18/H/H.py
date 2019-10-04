# MuMonash

n = int(input())
names = []
wins = []
total = []
table_scores = []
for x in range(n):
    data = input().split()
    name = data[0]
    scores = data[1:]
    names.append(name)
    wins.append(scores.count('7'))
    table_scores.append(list(map(lambda x: int(x) if x != 'X' else 0, scores)))
    total.append(sum(table_scores[-1]))

for x in range(n):
    total[x] -= sum(table_scores[y][x] for y in range(n))

winners = []
bwins = -1
diff = 0

for x in range(n):
    if (
        (wins[x] > bwins) or
        (wins[x] == bwins and total[x] > diff)
    ):
        winners = [names[x]]
        bwins = wins[x]
        diff = total[x]
    elif wins[x] == bwins and total[x] == diff:
        winners.append(names[x])

diff_string = f'+{diff}' if diff > 0 else (f'{diff}' if diff < 0 else diff)
print(' '.join(winners), 'won with', bwins, 'wins and', diff_string, 'points difference.')
