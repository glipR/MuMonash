q = int(input())

mapping = {
    '+': lambda x, y: x + y,
    '-': lambda x, y: x - y,
    '/': lambda x, y: x // y,
    '*': lambda x, y: x * y
}

while q > 0:
    s = input().split()

    stack = []

    for exp in s:
        if exp not in ['+', '-', '/', '*']:
            stack.append(int(exp))
        else:
            right = stack[-1]
            del stack[-1]
            stack[-1] = mapping[exp](stack[-1], right)

    if len(stack) > 1:
        while True:
            pass

    print(stack[0])

    q -= 1
