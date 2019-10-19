t = int(input())

for _ in range(t):
    spend = int(input())
    n_components = int(input())
    num_n_components = list(map(int, input().split()))
    comp_prices = [None for __ in range(n_components)]
    for x in range(n_components):
        comp_prices[x] = list(map(int, input().split()))

    possible_prices = set()
    possible_prices.add(-1)
    for x in range(n_components):
        new_possible = set()
        for p in list(possible_prices):
            for y in range(num_n_components[x]):
                if p + comp_prices[x][y] <= spend:
                    new_possible.add(p + comp_prices[x][y])
        possible_prices = new_possible
    if possible_prices:
        print(max(possible_prices))
    else:
        print(-1)
