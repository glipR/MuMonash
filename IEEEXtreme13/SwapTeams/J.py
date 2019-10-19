t = int(input())

for _ in range(t):

    string = input()

    counts = [
        string.count(x)
        for x in 'ABCD'
    ]

    best_points = [[] for _ in range(len('ABCD'))]
    all_points = []

    for i, key in enumerate('ABCD'):
        start = 0
        end = counts[i] - 1
        best = string[start:end+1].count(key)
        current = best
        all_points.append([current])
        for x in range(len(string)):
            end += 1
            end %= len(string)
            current += string[end] == key
            current -= string[start] == key
            best = max(current, best)
            start += 1
            start %= len(string)
            all_points[-1].append(current)
        best_points[i] = [a for a, e in enumerate(all_points[-1]) if e == best]

    i = 0
    key = 'A'
    best = len(string)
    for point in range(len(string)):
        current = counts[i] - all_points[i][point]
        best2 = len(string)
        for j, key2 in enumerate('ABCD'):
            if j == i: continue
            point2 = (point + counts[i]) % len(string)
            current2 = counts[j] - all_points[j][point2]
            best3 = len(string)
            for k, key3 in enumerate('ABCD'):
                if k == j or k == i: continue
                point3 = (point2 + counts[j]) % len(string)
                current3 = counts[k] - all_points[k][point3]
                best4 = len(string)
                for l, key4 in enumerate('ABCD'):
                    if l == k or l == j or l == i: continue
                    point4 = (point3 + counts[k]) % len(string)
                    current4 = counts[l] - all_points[l][point4]
                    best4 = min(best4, current4)
                current3 = current3 + best4
                best3 = min(best3, current3)
            current2 = current2 + best3
            best2 = min(best2, current2)
        current = current + best2
        best = min(best, current)
    print(best)


