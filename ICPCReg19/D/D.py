print((lambda n,m:sum(map(lambda w:len(set(w))==len(w) and all(x in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'[:m] for x in w),(input() for _ in range(n)))))(*map(int,input().split())))
