n = int(input())

for x in range(n):
    res = input().split()
    for index in range(len(res)):
        if res[index].isnumeric(): res[index] = int(res[index])
    stack = []
    for val in res:
        if val == '*':
            a = stack.pop()
            b = stack.pop()
            stack.append(b * a)
            continue
        if val == '/':
            a = stack.pop()
            b = stack.pop()
            stack.append(b // a)
            continue
        if val == '+':
            a = stack.pop()
            b = stack.pop()
            stack.append(b + a)
            continue
        if str(val) in '-–':
            a = stack.pop()
            b = stack.pop()
            stack.append(b - a)
            continue
        stack.append(val)
    print(stack[0])
