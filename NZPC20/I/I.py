import itertools

def get_indicies(d, indicies):
    index = 0
    for val in indicies:
        index *= 3
        index += val
    return index

while True:
    dim = int(input())
    if dim == 0:
        break

    index = 0
    points = ""
    while index < pow(3, dim):
        line = input()
        points = points + line
        index += len(line)

    o_score = 0
    x_score = 0
    # calculate scores
    # straight lines - choose a dimension to vary
    for x in range(dim):
        indicies = [0] * dim
        for y in range(pow(3, dim-1)):
            indicies[x] = 0
            a = get_indicies(dim, indicies)
            indicies[x] = 1
            b = get_indicies(dim, indicies)
            indicies[x] = 2
            c = get_indicies(dim, indicies)
            if points[a] == points[b] and points[b] == points[c]:
                if points[a] == "X":
                    x_score += 1
                elif points[a] == "O":
                    o_score += 1
            
            for z in range(dim):
                if z == x: continue
                indicies[z] += 1
                if indicies[z] == 3:
                    indicies[z] = 0
                    continue
                break
    # diagonal lines - choose a dimensions to vary
    for a in range(2, dim+1):
        for comb in itertools.combinations(range(dim), a):
            varying = [False]*dim
            for c in comb:
                varying[c] = True
            indicies = [0]*dim
            for _ in range(pow(3, dim-a)):
                for direction in range(pow(2, a-1)):
                    for i, v in enumerate(comb):
                        indicies[v] = 0 if ((1 << i) & direction) else 2
                    d = get_indicies(dim, indicies)
                    for i, v in enumerate(comb):
                        indicies[v] = 1
                    e = get_indicies(dim, indicies)
                    for i, v in enumerate(comb):
                        indicies[v] = 2 if ((1 << i) & direction) else 0
                    f = get_indicies(dim, indicies)
                    if points[d] == points[e] and points[e] == points[f]:
                        if points[d] == "X":
                            x_score += 1
                        elif points[d] == "O":
                            o_score += 1
                for i in range(dim):
                    if varying[i]: continue
                    indicies[i] += 1
                    if indicies[i] == 3:
                        indicies[i] = 0
                        continue
                    break
                
    
    print("X scores " + str(x_score) + " and O scores " + str(o_score))

        


