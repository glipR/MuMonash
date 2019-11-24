import functools
print(' '.join(map(str, functools.reduce(lambda x,y:[x[0]+max(x[1]+1,y[0]-y[1]),max(x[1]+1,y[0]-y[1]),x[2]+[max(x[1]+1,y[0]-y[1])]],sorted([tuple(map(int,input().split())) for x in range(int(input()))],key=lambda x:(x[0]-x[1])*1e10+x[0]+x[1]),[0,0,[]])[2])))
