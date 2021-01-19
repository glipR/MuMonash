t = int(input())

for _ in range(t):
    n, m, a, b = list(map(int, input().split()))
    firecrackers = list(sorted(list(map(int, input().split()))))

    # Figure out the distance between the hooligan and guard x, we can plant (x-1) firecrackers.
    distance = abs(b-a)
    # How many ticks of firecracker do we have after waiting?
    running_time = a if b > a else n - a + 1

    # We will always use the fastest firecrackers optimally.
    current_wait_index = 1
    firecracker_index = 0
    while firecracker_index < len(firecrackers) and current_wait_index < distance:
        if current_wait_index + running_time - 1 < firecrackers[firecracker_index]:
            # It won't blow up in time, go to the next time when it will.
            current_wait_index += firecrackers[firecracker_index] - (current_wait_index + running_time - 1)
        else:
            # It will blow up in time.
            current_wait_index += 1
            firecracker_index += 1
    print(firecracker_index)
