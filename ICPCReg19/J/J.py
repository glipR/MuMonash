import functools
print(' '.join(map(lambda x: str(x[1]),sorted(functools.reduce(lambda x,y:[x[0]+max(x[1]+1,y[1]-y[2]),max(x[1]+1,y[1]-y[2]),x[2]+[[y[0], max(x[1]+1,y[1]-y[2])]]],sorted([tuple((x, *map(int,input().split()))) for x in range(int(input()))],key=lambda x:(x[1]-x[2])*1e10+x[1]+x[2]),[0,0,[]])[2],key=lambda x:x[0]))))
