# MuMonash

added, subtracted = map(int, input().split())

items = {}

for x in range(added):
    num, name = input().split()
    num = int(num)
    if num != 1:
        name = name[:-1]
    if name not in items:
        items[name] = 0
    items[name] += num

bad = False

for y in range(subtracted):
    num, name = input().split()
    num = int(num)
    if num != 1:
        name = name[:-1]
    if name not in items:
        bad = True
    else:
        items[name] -= num
        if items[name] < 0:
            bad = True

if bad:
    print('error')
else:
    amount = 0
    for key in items.keys():
        amount += items[key]
    if amount == 0:
        print('null')
    elif amount == 1:
        print('item')
    else:
        print('items')
