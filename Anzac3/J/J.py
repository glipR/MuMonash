n = int(input())

for fstart in range(2, n+1):
    for fend in [fstart-1, fstart]:
        # Try generating n from these two.
        total_rows = n // (fstart + fend)
        if total_rows < 1:
            continue
        if not(n - total_rows * (fstart + fend) == 0 or n - total_rows * (fstart + fend) == fstart):
            continue
        print(fstart, fend)
