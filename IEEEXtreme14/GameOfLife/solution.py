rule_death, rule_life = input().split(";")
n, m = list(map(int, input().split()))
board = [input() for _ in range(n)]
for x in range(n):
    board[x] = list(board[x])
    for y in range(n):
        board[x][y] = board[x][y] == "1"

# Iterate M times
for t in range(m):
    new_board = [[False for _ in range(n)] for __ in range(n)]
    for x in range(n):
        for y in range(n):
            n_neighour = 0
            for a, b in [
                (x+1, y),
                (x-1, y),
                (x, y+1),
                (x, y-1),
            ]:
                if board[a%n][b%n]: n_neighour += 1
            if (
                (board[x][y] and rule_life[n_neighour] == '1') or 
                (not board[x][y] and rule_death[n_neighour] == '1')
            ):
                new_board[x][y] = True
            else:
                new_board[x][y] = False
    board = new_board

for x in range(n):
    for y in range(n):
        board[x][y] = "1" if board[x][y] else "0"
    board[x] = "".join(board[x][y] for y in range(n))
print("\n".join(board))