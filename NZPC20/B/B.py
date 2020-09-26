while True:
    x, y, z = input().split()
    start = int(x)
    diff = int(z)
    if start == diff and diff == 0:
        break
    if y == "W":
        if start - diff < -200:
            print("Not allowed")
        else:
            print(start - diff)
    else:
        print(start + diff)
