n = int(input())
print(n+1)
q = [1]
index = 0
while n > 0:
    front = q[index]
    index += 1
    print(front, 2*front)
    if n > 1:
        print(front, 2*front + 1)
    q.append(front*2)
    q.append(2*front + 1)
    n -= 2


