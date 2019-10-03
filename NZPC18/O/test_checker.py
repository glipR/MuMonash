n = input()
x = list(map(int, input().split()))

for i in range(len(x)):
    if x[i] == 0:
        continue
    if x[x[i]-1] != 0:
        print("Invalid: {}".format(i))

