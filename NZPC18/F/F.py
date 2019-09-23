# MuMonash

def read_ints():
    return list(map(int, input().split()))

n = int(input())

COST, WAIT = range(2)

products = {}

for x in range(n):
    name = input()
    cost, wait = read_ints()
    products[name] = (cost, wait)

c = int(input())
num_stopped = 0
for x in range(c):
    cid, p, d = input().split(' ')
    p = int(p)
    d = int(d)
    stopped = False
    purchased = 0
    for y in range(p):
        product = input()
        if products[product][WAIT] <= d:
            purchased += products[product][COST]
        else:
            stopped = True
    if stopped:
        num_stopped += 1
    add_to = ' *' if stopped else ''
    print(f'{cid} {purchased}{add_to}')

print(f'Number of discontented customers is: {num_stopped}')
