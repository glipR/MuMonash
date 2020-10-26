n, t = list(map(int, input().split()))
lights = list(map(int, input().split()))
distances = [t - lights[-1] + lights[0]]
for x in range(n-1):
    distances.append(lights[x+1] - lights[x])

def z_array(s):
    z = [len(s)-1]*len(s)
    L = 0
    R = 0
    for i in range(1, len(s)):
        j = max(min(z[i-L], R-i), 0)
        while i+j<len(s) and s[i+j] == s[j]:
            j += 1
        z[i] = j
        if (i + z[i] > R):
            R  = i + z[i]
            L = i
    return z

same_as = 1

z = z_array(distances + distances)
for x in range(len(distances)-1):
    if z[x+1] == 2*len(distances) - x - 1:
        # suffix is prefix.
        same_as += 1

# Every rotation is the same as same_as rotations. Total rotations is n
print(t // same_as - 1)