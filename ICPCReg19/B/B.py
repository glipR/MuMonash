import functools,sys
(n,b),v,_,s=(
    map(int,input().split()),
    sorted(list(map(int,input().split()))),
    sys.setrecursionlimit(10000000),functools.lru_cache(maxsize=1000000)(lambda i,j:(min((v[-1]-v[i])**2,*tuple((v[i]-v[x-1])**2+s(x,j-1) for x in range(i+1, n))) if i+1!=n else (v[-1]-v[i])**2) if j else 1e24)
)
print(s(0,b))
