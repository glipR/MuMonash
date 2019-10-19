t = int(input())

def solve(b, x):
    extra = 1
    current = 0
    total = 0
    iterations = 0
    while total <= x:
        iterations += 1
        extra *= b
        current = b * current + extra
        total += current
    # Now binary search
    string = ''
    total_negative = 0
    for y in range(iterations):
        negative = 0
        for z in range(b):
            negative = int((z+1) * current / pow(b, y+1))
            if total - total_negative - negative <= x:
                total_negative += int((z) * current / pow(b, y+1))
                string = string + chr(ord('a') + (b-z-1))
                break
    return string[int(x - (total - total_negative))]

for case in range(t):
    print(solve(*map(int, input().split())))
