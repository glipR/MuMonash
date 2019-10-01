n = int(input())

l1 = list(map(int, input().split()))
l2 = list(map(int, input().split()))

if sorted(l1) == sorted(l2):
    print('marvelous')
else:
    print('error')
