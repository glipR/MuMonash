attempt_score = [10, 7, 4]

weights = list(map(int, input().split()))
num_students = int(input())

names = []
students = {}
for x in range(num_students):
    _id, n1, n2 = input().split()
    students[_id] = {"attempts": [0]*5, "score": 0, "names": [n1, n2]}
    names.append(_id)

while True:
    x, y, z = input().split()
    if x == "0": break
    index = ord(y) - ord('A')
    if z == "P":
        students[x]["score"] += weights[index] * attempt_score[min(students[x]["attempts"][index], 2)]
    students[x]["attempts"][index] += 1

pass_mark = sum(weights) * attempt_score[0] / 2

for key in names:
    print(" ".join(students[key]["names"]), "Pass" if students[key]["score"] >= pass_mark else "Fail")


