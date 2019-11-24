from functools import *
n,(d, f),(e, g),v=int(input()),map(int,input().split()),map(int,input().split()),lru_cache()(lambda n:reduce(lambda a,z:(a[0]+z//2,a[1]+z%2),(int(input()) for _ in range(n)),[0,0]))
print("Yes" if(v(n)[0]<=min(f, g) and max(d-v(n)[0],0)+max(e-v(n)[0],0)<=v(n)[1] and 2*v(n)[0]+v(n)[1]<=f+g) else "No")
