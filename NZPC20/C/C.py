line = input().split()
new_res = [word[::-1] for word in line]
print(" ".join(new_res))