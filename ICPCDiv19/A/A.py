# MuMonash

from collections import defaultdict

arrays = defaultdict(lambda: defaultdict(lambda: 0))

while True:
    try:
        line = input()
    except Exception:
        break

    l = line[0]
    index = int(float(line[2:].split(']')[0]) - 0.5)
    increment = int(line.split('=')[1])
    arrays[l][index] += increment

for key in sorted(arrays.keys()):
    print(key)
    for index in sorted(arrays[key].keys()):
        if arrays[key][index] != 0:
            print(arrays[key][index])
