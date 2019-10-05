import sys
sys.setrecursionlimit(100000000)

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
    def g(x, memory):
        res = MAX_NUM
        if x not in memory:
            memory[x] = 'init'

        if memory[x] == 'working':
            return MAX_NUM
        if memory[x] != 'init':
            return memory[x]
        
        memory[x] = 'working'

        for rule in rules[x]:
            current = 0
            for term in rule:
                if term[0] == '"':
                    current += 1
                else:
                    current += g(term, memory)
            res = min(res, current)

        memory[x] = res
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
            mem = dict()

            for term in rule:
                if term[0] == '"':
                    current += 1
                else:
                    current += g(term, mem) if found else mem_g[term]
            
            if not found:
                minimum = MAX_NUM
                for term in rule:
                    if term[0] == '"':
                        continue
                    minimum = min(minimum, current - mem_g[term] + f(term))

                current = minimum

            res = min(res, current)

        mem_f[x] = res
        return res
 
        
    g(starting_id, mem_g)
    answer = f(starting_id)
    #print(mem_g)
    print(-1 if answer > 1000000000 else answer)
