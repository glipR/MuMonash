import sys

n, a, b = 0, 0, 0
with open(sys.argv[1], 'r') as f:
    n, a, b = map(int, f.readline().strip().split())

with open(sys.argv[2], 'r') as f:
    result = f.readline().strip()
    if result == "NO":
        print("GOOD")
    elif result == "YES":
        ints = list(map(int, f.readline().strip().split()))
        if sum(ints) != n:
            print("BAD")
        else:
            print("GOOD")
    else:
        print("BAD")
