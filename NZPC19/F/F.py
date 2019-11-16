n = int(input())

def diff(x, c1, c2):
    for key in ['RGB', 'DOS', '123', 'FSE'][x]:
        if key not in [c1, c2]:
            return key

for x in range(n):
    c1, c2 = input().split()
    card = ''
    for x in range(4):
        if (c1[x] == c2[x]): card = card + c1[x]
        else: card = card + diff(x, c1[x], c2[x])
    print(card)
