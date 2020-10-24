t = int(input())
for case in range(1, t+1):
    m, n, k = list(map(int, input().split()))
    correct = sorted([int(input()) for _ in range(m)])
    # we will flip the floors with least wired correctly.
    power = sum(correct[k:]) + n*k - sum(correct[:k])
    print(power)
