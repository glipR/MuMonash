while True:
    street_num = int(input())
    if street_num == 0:
        break
    res = 2 + len(str(street_num)) - 1
    for char in str(street_num):
        if char == "0":
            res += 4
        elif char == "1":
            res += 2
        else:
            res += 3
    print(res)