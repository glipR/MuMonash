# MuMonash

MOD = 1000000007
string = input()

# f: answer to problem
# g: 01..01 (At least 2 characters)
# h: answer to problem OR just 1.

f = [-1] * len(string)
g = [-1] * len(string)
h = [-1] * len(string)

def solve_f(x):
    if f[x] != -1:
        return f[x]
    if x == len(string) - 1 or x == len(string) - 2:
        f[x] = 0
        return f[x]
    if string[x] == '0':
        f[x] = solve_f(x+1)
        return f[x]
    f[x] = (solve_g(x+1) + solve_f(x+1)) % MOD
    return f[x]

def solve_g(x):
    if g[x] != -1:
        return g[x]
    if x == len(string) - 1:
        g[x] = 0
        return g[x]
    if string[x] == '1':
        g[x] = solve_g(x+1)
        return g[x]
    # Keep the 0 or remove it.
    g[x] = (solve_h(x+1) + solve_g(x+1)) % MOD
    return g[x]

def solve_h(x):
    if h[x] != -1:
        return h[x]
    if x == len(string) - 1:
        h[x] = 0 if string[x] == '0' else 1
        return h[x]
    if string[x] == '0':
        h[x] = solve_h(x+1)
        return h[x]
    # Keep the 1 or remove it.
    h[x] = (1 + solve_g(x+1) + solve_h(x+1)) % MOD
    return h[x]

# To avoid recursion limit, iterate backwards and solve.
for x in range(len(string)-1, -1, -1):
    solve_f(x)
    solve_g(x)
    solve_h(x)
print(solve_f(0))
