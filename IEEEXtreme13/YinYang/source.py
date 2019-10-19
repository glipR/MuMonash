n = int(input())

def alternate(string):
    res = ""
    for c in string:
        res += 'Y' if c == 'y' else 'y'
    return res

optimal = ["y"]
current = 1
alt = 1
while current < n:
    optimal.append("{}{}".format(
        optimal[len(optimal)-1] if alt == 1 else alternate(optimal[len(optimal)-1]),
        alternate(optimal[len(optimal)-1]) if alt == 1 else optimal[len(optimal)-1]
    ))
    alt = 1 - alt
    current *= 2

#ans = ""
#i = len(optimal) - 1
#while n > 0:
#    if len(optimal[i]) > n:
#        i -= 1
#        continue
#    ans += optimal[i]
#    n -= len(optimal[i])
#    i -= 1

#print(ans)

print(optimal[len(optimal)-1][:n])

