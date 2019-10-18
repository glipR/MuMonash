# MuMonash

def solve(string):
    # We should always start at left or right end.
    nums = []
    for x in range(len(string)):
        if string[x] == '1':
            nums.append(x)
    if nums == []:
        return len(string)
    dist1 = 2 * (len(string) - nums[0])
    dist2 = 2 * (nums[-1] + 1)
    return max(dist1, dist2)

t = int(input())
for case in range(t):
    n = int(input())
    string = input()
    print(solve(string))
