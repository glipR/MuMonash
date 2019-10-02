# MuMonash
# Snakes and Ladders

MOD = 1000000007
EPS = 1/2 # Only integers here.

# a^b mod m
def expmod(a, b, m):
    # Multiply by a, a^2, a^4, ... wherever appropriate.
    res = 1 % m
    a %= m
    while b:
        if b % 2 == 1:
            res = (res * a) % m
        a = (a * a) % m
        b = b // 2
    return res

def modinv(x):
    # Since our m is prime, x^{m-2} = x^{-1}. I forget why.
    return expmod(x, MOD-2, MOD)

mod6 = modinv(6)

def read_ints():
    return list(map(int, input().split()))

n = int(input())
values = read_ints()

reachable = [False]*n
reachable[0] = True

for x in range(n):
    for y in range(n):
        if reachable[y]:
            for z in range(1, 7):
                if y + z < len(values) - 1:
                    if values[y+z] == 0:
                        reachable[y+z] = True
                    else:
                        reachable[values[y+z]-1] = True
                reachable[-1] = True

# Generate matrix of relationships
matrix = [
    # Everything = -1
    [0 for v in values] + [MOD - 1]
    for m in values
]
# We take 0 steps for the last step
matrix[-1][-1] = 0
for x in range(len(values)):
    if reachable[x]:
        for y in range(1, 7):
            if x + y < len(values) - 1:
                if values[x+y] == 0:
                    matrix[x][x+y] += mod6
                else:
                    matrix[x][values[x+y] - 1] += mod6
            # Otherwise, we reach the last tile.
        matrix[x][x] += MOD - 1 # Same as += -1
        # x = (x+1, x+2, x+3, x+4, x+5, x+6) / 6 + 1
        # mod6 * (x+1 + x+2 + x+3 + x+4 + x+5 + x+6) - x = -1
    else:
        matrix[x][-1] = 0

def gauss_jordan(matrix):
    rows = len(matrix)
    columns = len(matrix[0])
    r = 0
    good_rows = {}
    for c in range(columns):
        if r >= rows:
            break
        # Find the row with maximum value for column c.
        maxr = r
        for r2 in range(r+1, rows):
            if abs(matrix[r2][c]) > abs(matrix[maxr][c]):
                maxr = r2
        if abs(matrix[maxr][c]) < EPS:
            continue
        matrix[maxr], matrix[r] = matrix[r], matrix[maxr]
        good_rows[c] = r
        s = modinv(matrix[r][c])
        for j in range(columns):
            matrix[r][j] *= s
            matrix[r][j] %= MOD
        for i in range(rows):
            if i != r:
                t = matrix[i][c]
                for j in range(columns):
                    matrix[i][j] -= t * matrix[r][j]
                    matrix[i][j] %= MOD
        r += 1
    return good_rows

# print(matrix)
gauss_jordan(matrix)
# print(matrix)

print(matrix[0][-1])
