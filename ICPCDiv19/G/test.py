red = int(input())
scalex, scaley, scalew, scaleh = map(int, input().split())
bluex, bluey, bluew, blueh = map(int, input().split())
red_rects = []
for x in range(red):
    red_rects.append(list(map(int, input().split())))

def in_rect(x, y, rect):
    return (rect[0] <= x <= rect[0] + rect[2]) and (rect[1] <= y <= rect[1] + rect[3])

while True:
    startx = int(input("Lower bound on x? "))
    starty = int(input("Lower bound on y? "))
    lenx = int(input("Width of search? "))
    leny = int(input("Height of search? "))
    points = []
    for y in range(starty, starty + leny + 1):
        points.insert(0, [])
        for x in range(startx, startx + lenx + 1):
            points[0].append([])
            for idx, rect in enumerate(red_rects, start=4):
                if in_rect(x, y, rect):
                    points[0][-1].append(idx)
            if in_rect(x, y, [scalex, scaley, scalew, scaleh]):
                points[0][-1].append(2)
    print('\n'.join(''.join(str(x) for x in row) for row in points))
