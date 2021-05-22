import sys

i, j = list(map(int, input().split()))

# Everything is mod j
seen = set()
seen.add(i)

lower = j // 3
higher = (2 * j + 2) // 3

while True:
    if lower < i < higher:
        print("Triangle wins.")
        break
    else:
        i = (3 * i) % j
        if i in seen:
            print("Particle wins.")
            break
        seen.add(i)
