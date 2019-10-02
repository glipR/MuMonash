import re

numbers = re.compile('[-+]?[0-9]+(?:,[0-9][0-9][0-9])*(?:.[0-9]+)?')

s = input()
while s != '#':
    matches = numbers.findall(s)
    pointer = 0
    s = list(s)
    for match in matches:
        l = len(match)
        while not( pointer + l <= len(s) and match == ''.join(s[pointer:pointer+l])):
            pointer += 1

        s[pointer:pointer+l] = reversed(s[pointer:pointer+l])
        pointer += l
        
    print(''.join(reversed(s)))

    s = input()
