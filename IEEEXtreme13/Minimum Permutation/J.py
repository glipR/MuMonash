n, m = map(int, input().split())

n_array = list(map(int, input().split()))
selection = list(map(int, input().split()))

solution = [None] * (n+m)
for i, x in enumerate(n_array):
    solution[x-1] = (True, i)

current = -1
new_points = []
for i, x in enumerate(n_array):
    if x > current:
        current = x
        new_points.append((x, i))

selection.sort()
for i, x in enumerate(selection):
    solution[x-1] = (False, i)

location = [[] for _ in range(len(n_array) + 1)]

cur_index = 0

for x in selection:
    while cur_index < len(new_points) and new_points[cur_index][0] < x:
        cur_index += 1
    if cur_index == len(new_points):
        location[-1].append(x)
    else:
        location[new_points[cur_index][1]].append(x)

result = []
for x in range(len(n_array)):
    result.extend(location[x])
    result.append(n_array[x])
result.extend(location[-1])

print(' '.join(map(str, result)))


