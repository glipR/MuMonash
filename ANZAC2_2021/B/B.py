n, s = list(map(int, input().split()))
nums = [int(input()) for _ in range(n)]

# Check to the left and right at each iteration
# Do some precomp to make these checks
left_min = [-1]*n
right_min = [-1]*n
lm = max(nums) + 1
rm = max(nums) + 1
for i in range(n):
    lm = min(lm, nums[i])
    rm = min(rm, nums[n-i-1])
    left_min[i] = lm
    right_min[n-i-1] = rm
# left_min[i] = min(nums[:i+1])
# right_min[i] = min(nums[i:])

best = -1

given = (n-1) * s
for i in range(n):
    # i rounds have passed.
    taken = i * s
    smallest = nums[i] + given - taken
    if i > 0:
        # Everything to the left has also been given and taken the same amount.
        smallest = min(smallest, left_min[i-1] + given - taken)
    if i < n-1:
        # Everything to the right has just been taken, and one extra amount.
        smallest = min(smallest, right_min[i+1] - taken - s)
    best = max(best, smallest)

print(best)
