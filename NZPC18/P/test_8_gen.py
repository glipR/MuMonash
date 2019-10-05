import random
import string

def random_string(N=20):
    return ''.join(random.choices(string.ascii_uppercase + string.ascii_lowercase, k=N))

start = "start"
target = "\"target\""

mark = dict()
mark[start] = True

rules = list()

MAX_RULES = 100000
last = start
for i in range(MAX_RULES - 1):
    r = random_string()
    while r in mark:
        r = random_string()
    mark[r] = True
    rules.append((last, [r for _ in range(10)]))
    last = r

rules.append((last, ["a"]*10))

print(len(rules))
print("{} {}".format(start, target))
for rule in rules:
    print("{} = {} .".format(rule[0], ' '.join(rule[1])))
print("0")

