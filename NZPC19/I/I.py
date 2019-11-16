n = int(input())

chars = 'ABCDEF'
options = []
for x1 in chars:
    for x2 in chars:
        for x3 in chars:
            for x4 in chars:
                options.append(x1+x2+x3+x4)
possible = [True] * len(options)

unique = -1

def score(truth, guess):
    black = 0
    white = 0
    used = [False, False, False, False]
    solved = [False, False, False, False]
    for x in range(4):
        if truth[x] == guess[x]:
            black += 1
            used[x] = True
            solved[x] = True
    for x in range(4):
        if not solved[x]:
            for y in range(4):
                if (not used[y]) and truth[y] == guess[x]:
                    used[y] = True
                    white += 1
    return black, white

num_possible = len(options)

for x in range(n):
    code, black, white = input().split()
    sol = (int(black), int(white))
    if unique != -1: continue
    for y in range(len(options)):
        if possible[y]:
            if score(options[y], code) != sol:
                num_possible -= 1
                possible[y] = False
    if (num_possible == 3):
        for y in range(len(options)):
            if possible[y]:
                print(options[y])
    if (num_possible == 1): unique = x

for y in range(len(options)):
    if possible[y]:
        print(options[y])

print(unique+1)


