n = int(input())

ans = "y"

for i in range(n-1):
    addedY = 0
    addedy = 0

    for j in range(len(ans)):
        new_str = ans[j:] + 'Y'
        addedY += 1 if len(new_str) % 2 == 0 and new_str[:len(new_str)//2] == new_str[len(new_str)//2:] else 0

    for j in range(len(ans)):
        new_str = ans[j:] + 'y'
        addedy += 1 if len(new_str) % 2 == 0 and new_str[:len(new_str)//2] == new_str[len(new_str)//2:] else 0

    if addedY > addedy:
        ans += 'y'
    else:
        ans += 'Y'

print(ans)
