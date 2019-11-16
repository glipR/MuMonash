n = int(input())

for x in range(n):
    res = input().split()
    index = 0
    while len(res) != 1:
        if res[index] == '*':
            res = res[:index-2] + [res[index-2] * res[index-1]] + res[index+1:]
            index -= 2
        elif res[index] == '/':
            res = res[:index-2] + [res[index-2] // res[index-1]] + res[index+1:]
            index -= 2
        elif res[index] == '+':
            res = res[:index-2] + [res[index-2] + res[index-1]] + res[index+1:]
            index -= 2
        elif res[index] == '-':
            res = res[:index-2] + [res[index-2] - res[index-1]] + res[index+1:]
            index -= 2
        else:
            res[index] = int(res[index])
            index += 1
    print(res[0])
