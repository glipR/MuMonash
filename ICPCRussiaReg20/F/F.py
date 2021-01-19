from collections import defaultdict

def gcd(a, b):
    if a == 0: return b
    return gcd(b % a, a)

t = int(input())

for _ in range(t):
    n = int(input())
    people = []
    vec_dicts = defaultdict(list)

    for x in range(n):
        x, y, u, v = list(map(int, input().split()))
        # Normalise the vector.
        v1, v2 = u - x, v - y
        if v1 == 0:
            v2 = 1 if v2 > 0 else -1
        elif v2 == 0:
            v1 = 1 if v1 > 0 else -1
        else:
            g = gcd(abs(v1), abs(v2))
            v1 //= g
            v2 //= g
        people.append((x, y, v1, v2))

        vec_dicts[(v1, v2)].append(x)

    # Now people can only make eye contact if the v1 and v2 are negatives.
    line_ups = 0
    for v1, v2 in vec_dicts:
        if (-v1, -v2) not in vec_dicts: continue
        line_ups += len(vec_dicts[(v1, v2)]) * len(vec_dicts[(-v1, -v2)])
    print(line_ups // 2)


