def centre_palindromes(string):
    if len(string) == 0:
        return []
    s2 = ["|"]*(2*len(string)+1)
    for x in range(len(string)):
        s2[2*x+1] = string[x]
    p = [0] * len(s2)
    c, r, m, n = 0, 0, 0, 0
    for i in range(1, len(s2)):
        if (i>r):
            p[i] = 0
            m = i-1
            n = i+1
        else:
            i2 = c*2-i
            if p[i2]<r-1-i:
                p[i] = p[i2]
                m = -1
            else:
                p[i] = r-i
                n = r+1
                m = i*2-n
        while m>=0 and n<len(s2) and s2[m] == s2[n]:
            p[i] += 1
            m -= 1
            n += 1
        if i+p[i] > r:
            c = i
            r = i+p[i]
    return p

def left_palindromes(centres):
    left_p = [0]*len(centres)
    for i, c in enumerate(centres):
        if (i - c) % 2 == 0:
            # We end on a '|', reduce.
            if c == 0:
                continue
            else:
                c -= 1
        left_p[i - c] = max(left_p[i - c], c+1)
    # Now, we need to find the largest at every point
    current = 0
    for i in range(len(centres) // 2):
        left_p[2*i+1] = max(left_p[2*i+1], current)
        current = left_p[2*i+1] - 2
    # Now, we want left_p to actually be a decreasing sequence.
    left_p[-1] = left_p[-2]
    for i in range(len(centres)-1, 0, -1):
        left_p[i-1] = max(left_p[i], left_p[i-1])
    return left_p

t = int(input())
for case in range(1, t+1):
    string = input()
    centres = centre_palindromes(string)
    lefts = left_palindromes(centres)
    best = -1
    for x in range(len(centres)):
        # Use x as the first centre.
        p1 = x
        if p1 % 2 == 0 and centres[p1] == 0:
            # We are on nothing.
            continue
        p2 = centres[x] + x + 1
        if p2 == len(centres):
            # We need to reduce size and add single char.
            best = max(best, centres[p1] - 1)
        else:
            if (p1 + centres[p1]) % 2 == 0:
                # Side is on a '|'
                best = max(best, centres[p1] + lefts[p2])
            else:
                best = max(best, 1 + centres[p1] + lefts[p2])
    print(best)
