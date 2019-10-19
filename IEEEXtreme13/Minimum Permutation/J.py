n, m = map(int, input().split())

n_array = list(map(int, input().split()))
selection = list(map(int, input().split()))

solution = [None] * (n+m)
for i, x in enumerate(n_array):
    solution[x-1] = (True, i)

selection.sort()
for i, x in enumerate(selection):
    solution[x-1] = (False, i)

placed = [None] * len(selection)
location = [[] for _ in range(len(n_array) + 1)]

for i, x in enumerate(selection):
    loc = x
    while loc < len(solution):
        if solution[loc][0] or solution[loc][1] < i:
            break
        loc += 1
    if solution[loc][0]:
        location[solution[loc][1]].append(x)
        placed[i] = solution[loc][1]
    else:
        location[placed[solution[loc][1]]].append(x)
        placed[i] = placed[solution[loc][1]]

result = []
for x in range(len(n_array)):
    result.extend(location[x])
    result.append(n_array[x])
result.extend(location[-1])

print(' '.join(map(str, result)))


