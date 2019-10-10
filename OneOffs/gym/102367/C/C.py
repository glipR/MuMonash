# MuMonash
# THIS TLE?????

n = int(input())
board = [
    [x for x in input()]
    for _ in range(n)
]

king_location = None
bad_pieces = []
for x in range(n):
    for y in range(n):
        if board[x][y] == 'K':
            king_location = (x, y)
        elif board[x][y] == '*':
            bad_pieces.append((x, y))

num_pawns = 0
bad = False

for x, y in bad_pieces:
    if abs(x-king_location[0]) <= 1 and abs(y-king_location[1]) <= 1:
        continue
    if board[x][y] == 'x':
        continue
    if 0 <= x+1 < n and 0 <= y+1 < n and board[x+1][y+1] == '-':
        # Always place it on the right side when possible.
        board[x][y] = 'x'
        board[x+1][y+1] = 'p'
        num_pawns += 1
        if y+2 < n and board[x][y+2] == '*':
            board[x][y+2] = 'x'
    elif 0 <= x+1 < n and 0 <= y-1 < n and board[x+1][y-1] == '-':
        # Otherwise the left will do.
        board[x][y] = 'x'
        board[x+1][y-1] = 'p'
        num_pawns += 1
    else:
        bad = True

if bad:
    print(-1)
else:
    print(num_pawns)
