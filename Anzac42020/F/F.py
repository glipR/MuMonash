n, k, r = list(map(int, input().split()))

cameras = [False]*n

for x in range(k):
    cameras[int(input())-1] = True


introduced = 0

# sliding window
num_cameras = sum(cameras[:r])
for x in range(n-r+1):
    # Check sum from cameras[x:r+x]
    if num_cameras == 0:
        cameras[r+x-1] = True
        cameras[r+x-2] = True
        introduced += 2
        num_cameras += 2
    elif num_cameras < 2:
        if cameras[r+x-1]:
            cameras[r+x-2] = True
            num_cameras += 1
            introduced += 1
        else:
            cameras[r+x-1] = True
            num_cameras += 1
            introduced += 1
    if x == n - r:
        continue
    if cameras[x]:
        num_cameras -= 1
    if cameras[x+r]:
        num_cameras += 1
    
print(introduced)