# MuMonash
# AC

import sys

h, w = map(int, input().split())

marked = [
    [-1 for _ in range(w)]
    for __ in range(h)
]

def valid_points(x, y):
    return [
        (a, b)
        for a in range(max(x-2, 0), min(x+1, h))
        for b in range(max(y-2, 0), min(y+1, w))
    ]

for x in range(h+2):
    for y, count in enumerate(list(map(int, input().split()))):
        points = valid_points(x, y)
        untouched = []
        num_marked = 0
        for a, b in points:
            if marked[a][b] is True:
                num_marked += 1
            elif marked[a][b] == -1:
                untouched.append((a, b))
        assert len(untouched) in [0, 1], "More than one new point."
        if num_marked == count:
            if untouched:
                marked[untouched[0][0]][untouched[0][1]] = False
        elif num_marked == count - 1 and untouched:
            marked[untouched[0][0]][untouched[0][1]] = True
        else:
            print('impossible')
            sys.exit()

print('\n'.join(''.join(('X' if x else '.') for x in row) for row in marked))
