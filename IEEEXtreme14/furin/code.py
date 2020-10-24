from collections import defaultdict


def add(data, index, x):
    data[index] = (data[index] + x) % 256


def sub(data, index, x):
    data[index] = (data[index] - x) % 256


def putchar(data, index, x):
    for _ in range(x):
        print(chr(data[index]), end='')



def run():
    line = input()
    index = 0
    data = defaultdict(int)
    index += 1
    data[index] = ord(line[0])
    index -= 1
    index += 2
    data[index] = ord(line[1])
    index += 1
    data[index] = ord(line[2])
    index -= 1
    while data[index]:
        sub(data, index, 1)
        index += 1
        sub(data, index, 1)
        index += 1
        add(data, index, 1)
        index -= 1
        index += 1
        index -= 2
    add(data, index, 1)
    sub(data, index, 1)
    index += 2
    while data[index]:
        sub(data, index, 1)
        index -= 2
        add(data, index, 1)
        index += 2
    index -= 1
    add(data, index, 1)
    sub(data, index, 1)
    index += 1
    index -= 1
    index += 1
    index -= 3
    while data[index]:
        sub(data, index, 1)
        add(data, index, 1)
        sub(data, index, 1)
        index += 1
        sub(data, index, 1)
        index -= 1
        add(data, index, 1)
        sub(data, index, 1)
        index -= 1
        add(data, index, 1)
        index += 1
    index -= 1
    while data[index]:
        sub(data, index, 1)
        index += 1
        add(data, index, 1)
        index -= 1
    index += 1
    index -= 1
    index += 6
    index -= 1
    index += 1
    add(data, index, 2)
    sub(data, index, 1)
    index += 2
    add(data, index, 1)
    sub(data, index, 1)
    index += 2
    index += 3
    add(data, index, 1)
    while data[index]:
        index += 2
        index -= 1
        index += 3
        while data[index]:
            sub(data, index, 1)
        index -= 1
        while data[index]:
            sub(data, index, 1)
            index -= 1
            index += 1
            sub(data, index, 1)
            add(data, index, 1)
        index -= 2
        index += 1
        while data[index]:
            sub(data, index, 1)
            add(data, index, 1)
            sub(data, index, 1)
        sub(data, index, 1)
        add(data, index, 2)
        sub(data, index, 1)
        add(data, index, 1)
        sub(data, index, 1)
        index -= 1
        while data[index]:
            sub(data, index, 1)
        index -= 1
        index += 1
        index -= 2
        index += 1
        while data[index]:
            add(data, index, 1)
            sub(data, index, 3)
            add(data, index, 1)
        index -= 1
        index += 1
        index -= 2
        index -= 2
        add(data, index, 1)
        sub(data, index, 1)
        index -= 4
        index += 1
        sub(data, index, 1)
        add(data, index, 1)
        index -= 1
        index += 1
        index -= 3
        index += 1
        index -= 1
        add(data, index, 1)
        sub(data, index, 1)
        index -= 2
        while data[index]:
            sub(data, index, 1)
            index += 1
            index += 6
            add(data, index, 1)
            index += 5
            sub(data, index, 1)
            add(data, index, 1)
            index += 1
            add(data, index, 1)
            index -= 3
            index += 1
            index -= 1
            index -= 1
            index -= 1
            index += 1
            index -= 5
            index -= 4
        index += 1
        while data[index]:
            sub(data, index, 1)
            index += 2
            index += 3
            index -= 1
            index += 1
            index -= 1
            index += 1
            index += 1
            index -= 1
            index += 2
            add(data, index, 1)
            index += 2
            index += 4
            add(data, index, 1)
            index -= 5
            index += 1
            index -= 1
            index -= 4
            add(data, index, 1)
            sub(data, index, 1)
            index -= 1
            index -= 3
        index += 1
        while data[index]:
            sub(data, index, 1)
            index += 5
            index += 2
            index -= 1
            index += 1
            add(data, index, 1)
            index += 4
            sub(data, index, 1)
            add(data, index, 1)
            index += 1
            index -= 1
            index += 2
            add(data, index, 1)
            index -= 4
            index -= 2
            add(data, index, 1)
            sub(data, index, 1)
            index -= 1
            index -= 3
            index += 1
            index -= 4
            sub(data, index, 1)
            add(data, index, 1)
            index += 1
            index -= 1
        index += 2
        sub(data, index, 1)
        add(data, index, 2)
        sub(data, index, 1)
        add(data, index, 1)
        index += 1
        add(data, index, 1)
        sub(data, index, 1)
        add(data, index, 1)
        while data[index]:
            index -= 1
            sub(data, index, 1)
        index -= 1
        while data[index]:
            sub(data, index, 1)
            index += 2
            index -= 1
            index += 1
            add(data, index, 2)
            sub(data, index, 1)
            index -= 3
        index += 4
        while data[index]:
            sub(data, index, 1)
            index -= 3
            add(data, index, 1)
            sub(data, index, 2)
            add(data, index, 1)
            index -= 4
            add(data, index, 1)
            index += 2
            index -= 1
            index += 3
            index += 3
        index += 1
        while data[index]:
            sub(data, index, 1)
            index -= 2
            sub(data, index, 1)
            add(data, index, 1)
            index -= 5
            add(data, index, 1)
            index -= 1
            index += 2
            add(data, index, 1)
            sub(data, index, 1)
            index += 3
            index += 3
        index += 1
        while data[index]:
            sub(data, index, 1)
            index -= 4
            index += 1
            index -= 3
            index += 1
            index -= 2
            add(data, index, 1)
            index += 1
            index += 6
        index += 6
        index -= 1
        index += 2
        add(data, index, 1)
        while data[index]:
            sub(data, index, 1)
            index -= 3
            index -= 1
            add(data, index, 1)
            sub(data, index, 2)
            add(data, index, 1)
            index -= 1
            index += 1
            index -= 1
            add(data, index, 1)
            sub(data, index, 1)
            index -= 5
            index -= 1
            while data[index]:
                sub(data, index, 1)
                index += 2
                add(data, index, 1)
                index += 2
                add(data, index, 1)
                index -= 4
            add(data, index, 1)
            sub(data, index, 1)
            index += 1
            while data[index]:
                sub(data, index, 1)
                index += 2
                add(data, index, 1)
                index += 2
                add(data, index, 1)
                sub(data, index, 1)
                add(data, index, 1)
                index -= 2
                index -= 2
            index += 1
            while data[index]:
                sub(data, index, 1)
                index -= 2
                add(data, index, 1)
                index += 2
            index += 1
            while data[index]:
                sub(data, index, 1)
                index -= 2
                add(data, index, 1)
                index += 2
            add(data, index, 1)
            while data[index]:
                while data[index]:
                    index -= 1
                    index += 1
                    sub(data, index, 1)
                sub(data, index, 1)
                add(data, index, 2)
                index += 1
                while data[index]:
                    index -= 1
                    sub(data, index, 1)
                index -= 1
                add(data, index, 1)
                sub(data, index, 1)
                while data[index]:
                    add(data, index, 1)
                    sub(data, index, 2)
                    index += 1
                    index -= 1
                    index += 2
                    index -= 1
                    index += 1
                    sub(data, index, 1)
                    index -= 3
                index += 2
                sub(data, index, 1)
                add(data, index, 1)
                sub(data, index, 1)
                index += 1
                index += 2
                add(data, index, 1)
                index += 1
                while data[index]:
                    index -= 1
                    sub(data, index, 1)
                index -= 1
                add(data, index, 1)
                sub(data, index, 1)
                while data[index]:
                    sub(data, index, 1)
                    index += 1
                    add(data, index, 1)
                    index += 1
                    while data[index]:
                        sub(data, index, 1)
                        index -= 1
                        sub(data, index, 1)
                    index -= 1
                    while data[index]:
                        index += 2
                        while data[index]:
                            sub(data, index, 1)
                            index -= 1
                            index -= 1
                            sub(data, index, 1)
                            add(data, index, 1)
                            sub(data, index, 1)
                            index += 1
                        sub(data, index, 1)
                        index -= 2
                        while data[index]:
                            sub(data, index, 1)
                            index += 1
                            index += 1
                            index -= 1
                            sub(data, index, 1)
                            index += 1
                            add(data, index, 1)
                            sub(data, index, 1)
                            index += 1
                            sub(data, index, 1)
                            add(data, index, 1)
                            sub(data, index, 1)
                            index -= 3
                            index -= 1
                    index -= 1
                index += 2
                sub(data, index, 1)
                index -= 3
                index -= 1
                index -= 1
                add(data, index, 1)
                index += 1
                while data[index]:
                    index += 1
                    index -= 2
                    sub(data, index, 1)
                index -= 1
                while data[index]:
                    index += 1
                    add(data, index, 1)
                    sub(data, index, 1)
                    index += 1
                    while data[index]:
                        sub(data, index, 1)
                        add(data, index, 1)
                        index -= 2
                        sub(data, index, 1)
                        index += 1
                    index -= 2
                    while data[index]:
                        index -= 1
                index += 1
                sub(data, index, 1)
                add(data, index, 1)
                sub(data, index, 1)
            index += 2
            index += 3
            index -= 1
            index += 2
            index += 2
            index -= 1
            index += 1
            add(data, index, 1)
        sub(data, index, 1)
        index -= 3
        index += 1
        add(data, index, 1)
        sub(data, index, 1)
        index -= 2
        index -= 1
        index += 1
        add(data, index, 1)
        index += 1
        sub(data, index, 1)
        add(data, index, 2)
        while data[index]:
            index -= 1
            sub(data, index, 1)
        index -= 1
        while data[index]:
            sub(data, index, 1)
            add(data, index, 1)
            index += 2
            add(data, index, 1)
            while data[index]:
                index -= 1
                index -= 2
                index += 1
                sub(data, index, 1)
                index += 1
                sub(data, index, 1)
                add(data, index, 1)
            index -= 2
            while data[index]:
                index += 3
                add(data, index, 1)
                while data[index]:
                    index -= 1
                    sub(data, index, 1)
                    add(data, index, 1)
                    index -= 1
                    index -= 1
                    sub(data, index, 1)
                    index += 2
                index -= 3
                while data[index]:
                    index -= 1
        index += 1
        sub(data, index, 1)
    index += 4
    while data[index]:
        sub(data, index, 1)
    index -= 2
    index -= 5
    sub(data, index, 1)
    add(data, index, 1)
    index -= 1
    index += 1
    index -= 1
    index -= 5
    index -= 1
    while data[index]:
        sub(data, index, 1)
    index += 1
    index += 1
    add(data, index, 1)
    index += 1
    add(data, index, 1)
    while data[index]:
        index -= 1
        sub(data, index, 1)
    index -= 1
    while data[index]:
        sub(data, index, 1)
        index += 2
        add(data, index, 1)
        index -= 1
        index += 1
        index -= 3
    index += 1
    add(data, index, 1)
    index += 1
    while data[index]:
        index -= 1
        sub(data, index, 1)
    index -= 1
    while data[index]:
        index += 1
        index += 1
        while data[index]:
            index -= 2
            sub(data, index, 1)
            index += 1
        index -= 2
        while data[index]:
            index -= 1
    index += 1
    sub(data, index, 1)
    while data[index]:
        add(data, index, 1)
        index += 3
        index += 4
        index -= 1
        add(data, index, 2)
        sub(data, index, 1)
        add(data, index, 2)
        add(data, index, 5)
        add(data, index, 2)
        index -= 3
        index -= 3
        add(data, index, 1)
        index += 1
        add(data, index, 1)
        sub(data, index, 1)
        while data[index]:
            index -= 2
            index += 1
            sub(data, index, 1)
        index -= 1
        while data[index]:
            index += 1
            index += 1
            while data[index]:
                index -= 2
                sub(data, index, 1)
                index += 1
            index -= 2
            while data[index]:
                index -= 1
        index += 1
        sub(data, index, 1)
        while data[index]:
            add(data, index, 2)
            index += 1
            while data[index]:
                index -= 1
                sub(data, index, 1)
            index -= 1
            while data[index]:
                sub(data, index, 1)
                index += 2
                sub(data, index, 1)
                index -= 2
                index -= 1
            index += 2
            sub(data, index, 1)
            index += 1
            index += 1
            add(data, index, 1)
            index += 2
            add(data, index, 1)
            index += 1
            sub(data, index, 1)
            while data[index]:
                index -= 1
                sub(data, index, 1)
            index -= 1
            while data[index]:
                index -= 2
                while data[index]:
                    sub(data, index, 1)
                    index += 3
                    add(data, index, 1)
                    index -= 2
                    index += 1
                    index -= 2
                add(data, index, 1)
                sub(data, index, 1)
                index += 2
                index += 3
                add(data, index, 1)
                index += 1
                add(data, index, 1)
                while data[index]:
                    index -= 1
                    index += 1
                    index -= 1
                    sub(data, index, 1)
                index -= 1
                index += 1
                index -= 1
                while data[index]:
                    sub(data, index, 1)
                    index += 1
                    index += 1
                    add(data, index, 1)
                    index -= 3
                index -= 2
                sub(data, index, 1)
                index -= 1
            index -= 4
            add(data, index, 1)
            index += 1
            while data[index]:
                index -= 1
                sub(data, index, 1)
            index -= 1
            while data[index]:
                index += 2
                while data[index]:
                    index -= 2
                    sub(data, index, 1)
                    index += 1
                index -= 2
                while data[index]:
                    index -= 1
            index += 1
            sub(data, index, 1)
        index += 2
        add(data, index, 3)
        add(data, index, 5)
        while data[index]:
            sub(data, index, 1)
            index += 1
            add(data, index, 5)
            add(data, index, 1)
            index -= 1
        index += 1
        while data[index]:
            sub(data, index, 1)
            index -= 4
            add(data, index, 1)
            index += 4
        index += 3
        index += 2
        add(data, index, 1)
        index += 1
        index -= 1
        index += 1
        sub(data, index, 1)
        add(data, index, 1)
        while data[index]:
            index -= 1
            sub(data, index, 1)
        index -= 1
        while data[index]:
            index += 2
            while data[index]:
                index -= 2
                sub(data, index, 1)
                index += 1
            index -= 2
            while data[index]:
                index -= 1
        index += 1
        sub(data, index, 1)
        while data[index]:
            add(data, index, 2)
            index += 1
            while data[index]:
                index -= 1
                sub(data, index, 1)
            index -= 1
            while data[index]:
                sub(data, index, 1)
                index += 2
                sub(data, index, 1)
                index -= 3
            index += 2
            sub(data, index, 1)
            index -= 3
            index -= 5
            add(data, index, 1)
            index += 1
            add(data, index, 1)
            while data[index]:
                index -= 1
                sub(data, index, 1)
            index -= 1
            while data[index]:
                sub(data, index, 1)
                index += 2
                add(data, index, 1)
                index -= 2
                index -= 1
            index += 3
            index += 5
            add(data, index, 1)
            index += 1
            while data[index]:
                index -= 1
                sub(data, index, 1)
            index -= 1
            while data[index]:
                index += 2
                while data[index]:
                    index -= 2
                    sub(data, index, 1)
                    index += 1
                index -= 2
                while data[index]:
                    index -= 1
            index += 1
            sub(data, index, 1)
        index -= 2
        while data[index]:
            sub(data, index, 1)
        index -= 5
        add(data, index, 1)
        index += 1
        while data[index]:
            index -= 1
            sub(data, index, 1)
        index -= 1
        while data[index]:
            index += 2
            while data[index]:
                index -= 2
                sub(data, index, 1)
                index += 1
            index -= 2
            while data[index]:
                index -= 1
        index += 1
        sub(data, index, 1)
    index -= 2
    while data[index]:
        putchar(data, index, 1)
        index -= 1


cases = int(input())
for x in range(cases):
    run()
    if x != cases - 1:
        print()