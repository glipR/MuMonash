import sys
sys.setrecursionlimit(1000000)

MAX_NUM = 1000100000

while True:
    n = int(input())
    if n == 0:
        break

    starting_id, target = list(input().split())
    
    rules = dict()

    for i in range(n):
        tokens = list(input().split())
        if tokens[0] not in rules:
            rules[tokens[0]] = []
        rules[tokens[0]].append(tokens[2:-1])

    input()


    mem_g = dict()
    def g(x):
        res = MAX_NUM
        if x not in mem_g:
            mem_g[x] = 'init'

        if mem_g[x] == 'working':
            return MAX_NUM
        if mem_g[x] != 'init':
            return mem_g[x]
        
        mem_g[x] = 'working'

        for rule in rules[x]:
            current = 0
            for term in rule:
                if term[0] == '"':
                    current += 1
                else:
                    current += g(term)
            res = min(res, current)

        mem_g[x] = res
        return res


    mem_f = dict()
    def f(x):
        res = MAX_NUM
        if x not in mem_f:
            mem_f[x] = 'init'

        if mem_f[x] == 'working':
            return MAX_NUM
        if mem_f[x] != 'init':
            return mem_f[x]

        mem_f[x] = 'working'

        for rule in rules[x]:
            current = 0
            found = target in rule
            
            for term in rule:
                if term[0] == '"':
                    current += 1
                else:
                    current += g(term)
            
            if not found:
                minimum = MAX_NUM
                for term in rule:
                    if term[0] == '"':
                        continue
                    minimum = min(minimum, current - g(term) + f(term))

                current = minimum

            res = min(res, current)

        mem_f[x] = res
        return res
 
        
    answer = f(starting_id)
    print(-1 if answer > 1000000000 else answer)
