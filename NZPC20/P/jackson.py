import math

test_no = 1
while True:
    n = int(input())
    if n == 0: break
    arms = []
    arm_parent = [None]*n
    num_weights = 0
    for x in range(n):
        dl, dr, tl, tr, nl, nr = input().split()
        arms.append((
            (int(dl), int(dr)),
            (tl, tr),
            (int(nl)-1, int(nr)-1),
        ))
        if tl == "A":
            arm_parent[arms[-1][2][0]] = x
        else:
            num_weights += 1
        if tr == "A":
            arm_parent[arms[-1][2][1]] = x
        else:
            num_weights += 1
    min_weight = [1]*num_weights
    total_weight = [-1]*n

    def recurse_calc(arm_index):
        # This calculates the total weight required for everything to be integer.
        # It doesn't go back down the tree and correct the values though.
        if arms[arm_index][1][0] == "A":
            recurse_calc(arms[arm_index][2][0])
            left_weight = total_weight[arms[arm_index][2][0]]
        else:
            left_weight = 1
        if arms[arm_index][1][1] == "A":
            recurse_calc(arms[arm_index][2][1])
            right_weight = total_weight[arms[arm_index][2][1]]
        else:
            right_weight = 1
        # Least common multiple of left strain and right strain.
        total_strain = (
            left_weight * arms[arm_index][0][0] * 
            right_weight * arms[arm_index][0][1] //
            math.gcd(left_weight * arms[arm_index][0][0], right_weight * arms[arm_index][0][1])
        )
        left_mult = total_strain // (left_weight * arms[arm_index][0][0])
        right_mult = total_strain // (right_weight * arms[arm_index][0][1])
        total_weight[arm_index] = left_mult * left_weight + right_mult * right_weight
        # print(arm_index, left_weight, right_weight, left_mult, right_mult, total_strain, total_weight[arm_index])

    def recurse_weights(arm_index):
        # Given the above function has run we can intuit the remaining results on total_weight.
        total = total_weight[arm_index]
        if arms[arm_index][1][0] == "A":
            total_weight[arms[arm_index][2][0]] = arms[arm_index][0][1] * total // (arms[arm_index][0][0] + arms[arm_index][0][1])
            recurse_weights(arms[arm_index][2][0])
        else:
            min_weight[arms[arm_index][2][0]] = arms[arm_index][0][1] * total // (arms[arm_index][0][0] + arms[arm_index][0][1])
        if arms[arm_index][1][1] == "A":
            total_weight[arms[arm_index][2][1]] = arms[arm_index][0][0] * total // (arms[arm_index][0][0] + arms[arm_index][0][1])
            recurse_weights(arms[arm_index][2][1])
        else:
            min_weight[arms[arm_index][2][1]] = arms[arm_index][0][0] * total // (arms[arm_index][0][0] + arms[arm_index][0][1])

    # Find the root
    for x in range(n):
        if arm_parent[x] is None:
            recurse_calc(x)
            recurse_weights(x)
    
            # print(min_weight, total_weight)
            idx, w = list(map(int, input().split()))
            idx -= 1
            mult = math.ceil(w / min_weight[idx])
            print("Case " + str(test_no) + ": " + str(mult * total_weight[x]))
    test_no += 1
