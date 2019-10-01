n = int(input())
response = input()
answers = input()

def score(s1, s2):
    s = 0
    for x in range(len(s1)):
        if s1[x] == s2[x]:
            s += 1
    return s

max_score = 0
for key1 in 'ABCDE':
    for key2 in 'ABCDE':
        max_score = max(max_score, score(response.replace(key1, key2), answers))

print(max_score)
