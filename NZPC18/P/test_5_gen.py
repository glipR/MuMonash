import random
from collections import deque
import string

def random_string(N=20):
    return ''.join(random.choices(string.ascii_uppercase + string.ascii_lowercase, k=N))

start = "start"
target = "\"target\""

mark = dict()
mark[start] = True

all_ids = list()

rules = list()

q = deque([start])

MAX_RULES = 100000

last = start

while len(rules) + len(q) + 9 < MAX_RULES:
    front = q.popleft()
    l = []
    for i in range(10):
        r = random_string()
        while r in mark:
            r = random_string()
        mark[r] = True
        l.append(r)
        q.append(r)
        last = r
    rules.append((front, l))



while len(q) > 0:
    item = q.popleft()
    rules.append((item, ['"a"']))

rules.append((last, [target]))

print(len(rules))
print("{} {}".format(start, target))
for rule in rules:
    print("{} = {} .".format(rule[0], ' '.join(rule[1])))
print("0")

