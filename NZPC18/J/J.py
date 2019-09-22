# Problem J: Compare
# AC

def edit_distance(str1, str2):
    """DP Approach to Edit Distance. O(str1 * str2)"""

    if not str1:
        return len(str2)
    if not str2:
        return len(str1)

    DP = [[-1 for __ in str2] for ___ in str1]
    DP[0][0] = 0 if str1[0] == str2[0] else 1


    for x, let1 in enumerate(str1):
        startat = 0
        if x == 0:
            startat = 1
        for y, let2 in enumerate(str2[startat:], startat):
            minimum = float('inf')
            if x != 0:
                minimum = min(DP[x-1][y] + 1, minimum)
                if y != 0:
                    minimum = min(DP[x-1][y-1] + (0 if let1 == let2 else 1), minimum)
            if y != 0:
                minimum = min(DP[x][y-1] + 1, minimum)

            DP[x][y] = minimum

    return DP[len(str1) - 1][len(str2) - 1]

n = int(input())

for case in range(n):
    replace = input()
    line1 = input()
    line2 = input()

    print('Differences {} and {}'.format(
        edit_distance(line1, line2),
        edit_distance(line1, line2.replace(replace, '@'))
    ))
