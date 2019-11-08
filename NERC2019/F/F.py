n = int(input())

# factoring algorithm
factors_of_n = [1, n]
for x in range(2, n):
    if n % x == 0:
        factors_of_n.append(x)

# minimal perimeter
perimeter = 4 * n

for factor in factors_of_n:
    perimeter = min(perimeter, 2 * factor + 2 * (n // factor))

print(perimeter)
