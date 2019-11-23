import functools, sys
(n, b), values, foo = map(int, input().split()), sorted(list(map(int, input().split()))), sys.setrecursionlimit(10000000)
solve = functools.lru_cache(maxsize=10000000)(lambda i, j: 1e24 if j == 0 else (min(pow((values[-1] - values[i]),2),*tuple(pow(values[i] - values[x-1], 2) + solve(x, j-1) for x in range(i+1, n))) if i+1 != n else pow((values[-1] - values[i]),2)))
print(solve(0, b))
