# MuMonash

num_c = int(input())
names = [
    input().strip()
    for __ in range(num_c)
]

scores = {
    name: [None, None, None]
    for name in names
}

def map_el(el):
    if el == 'E':
        return 0
    if el == 'M':
        return 1
    if el == 'D':
        return 2

for __ in range(3 * num_c):
    name, el, score = input().split()
    scores[name][map_el(el)] = int(score)

bonus = map_el(input().strip())

max_score_on_bonus = max(
    scores[name][bonus]
    for name in names
)

worst = None
best = None

for name in names:
    score = 0
    if scores[name][bonus] == max_score_on_bonus:
        score += 5
    score += sum(scores[name])
    scores[name] = score

    if worst is None or scores[worst] > score:
        worst = name
    if best is None or scores[best] < score:
        best = name

print(f'{best} gets immunity.')
print(f'{worst} goes home.')
