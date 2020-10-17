P = int(input())
problems = []
for x in range(P):
    info = input().split()
    problems.append((info[0], (int(info[1]), int(info[2]), int(info[3]))))

best_problem_index = 0
for x in range(1, P):
    if sum(problems[best_problem_index][1]) > sum(problems[x][1]):
        best_problem_index = x
    elif sum(problems[best_problem_index][1]) == sum(problems[x][1]):
        if problems[x][1][0] < problems[best_problem_index][1][0]:
            best_problem_index = x

print(problems[best_problem_index][0])