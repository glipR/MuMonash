n = int(input())

joe, jean, jane, james, unassigned = 0, 0, 0, 0, 0

for x in range(n):
    res = input()
    if res == 'X':
        unassigned += 1
    elif res in 'ML':
        joe += 1
    elif res == 'S':
        james += 1
    elif int(res) < 12:
        jane += 1
    elif int(res) >= 12:
        jean += 1
    else:
        raise ValueError("TF?")

print(joe, jean, jane, james, unassigned)
