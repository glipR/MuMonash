class Chunk:
    def __init__(self, a, b=1e10, single_char=False):
        if not single_char:
            self.a = int(a) # Inclusive
            self.b = int(b) # Inclusive
        if single_char:
            self.char = a
        self.single_char = single_char

    def __len__(self):
        return self.b - self.a + 1 if not self.single_char else 1

    def offset(self, val):
        return Chunk(self.a + val, self.b)

    def covering(self, other):
        if self.a != other.a:
            return 0
        return min(len(self), len(other))

    def __str__(self):
        if self.single_char:
            return self.char
        return "[{}:{}]".format(self.a, self.b)

    def merge(self, other):
        if self.b in [other.a, other.a - 1]:
            self.b = other.b
            return True
        return False

    def equals(self, other):
        if self.single_char:
            return other.single_char and self.char == other.char
        if other.single_char:
            return False
        return self.a == other.a and self.b == other.b


def perform_delete(chunks, pos):
    skipped = 0
    selected_chunk = 0
    while skipped + len(chunks[selected_chunk]) < pos:
        skipped += len(chunks[selected_chunk])
        selected_chunk += 1
    pos -= skipped

    if len(chunks[selected_chunk]) == 1:
        del chunks[selected_chunk]
        return

    offset = chunks[selected_chunk].a
    chunks[selected_chunk].a = offset + pos
    chunks.insert(selected_chunk, Chunk(offset, offset + pos - 2))
    
    for i in range(2):
        if len(chunks[selected_chunk + (1 - i)]) <= 0:
            del chunks[selected_chunk + (1 - i)]


def perform_insert(chunks, pos, char):
    skipped = 0
    selected_chunk = 0
    while skipped + len(chunks[selected_chunk]) < pos:
        skipped += len(chunks[selected_chunk])
        selected_chunk += 1
    pos -= skipped

    if len(chunks[selected_chunk]) == 1:
        chunks.insert(selected_chunk, Chunk(char, None, True))
        return

    offset = chunks[selected_chunk].a
    new_chunk = Chunk(offset + pos - 1, chunks[selected_chunk].b)
    chunks[selected_chunk].b = offset + pos - 2
    chunks.insert(selected_chunk + 1, new_chunk)
    chunks.insert(selected_chunk + 1, Chunk(char, None, True))
        
    for i in range(3):
        if len(chunks[selected_chunk + (2 - i)]) <= 0:
            del chunks[selected_chunk + (2 - i)]

chunks1 = [Chunk(1)]
chunks2 = [Chunk(1)]

for i, working_chunk in enumerate([chunks1, chunks2]):
    while True:
        command = input().split()
        if command[0] == 'E':
#            print("==============")
            break
        if command[0] == 'D':
            pos = int(command[1])
            perform_delete(working_chunk, pos)
        if command[0] == 'I':
            pos = int(command[1])
            char = command[2]
            perform_insert(working_chunk, pos, char)
#        print(list(map(str, working_chunk)))


for working_chunks in [chunks1, chunks2]:
    pointer = 0
    while pointer + 1 < len(working_chunks):
        if working_chunks[pointer].single_char or working_chunks[pointer + 1].single_char:
            pointer += 1
            continue
        if working_chunks[pointer].merge(working_chunks[pointer + 1]):
            del working_chunks[pointer + 1]
            pointer -= 1
        pointer += 1

#print(list(map(str,chunks1)), list(map(str, chunks2)))

if len(chunks1) != len(chunks2):
    print(1)
else:
    for i in range(len(chunks1)):
        if not chunks1[i].equals(chunks2[i]):
            print(1)
            break
    else:
        print(0)

"""
if lens[0] != lens[1]:
    print(1)
else:
    partial_matched = [0, 0]
    p = [0, 0]
    while p[0] < len(chunks1) and p[1] < len(chunks2):
        if chunks1[p[0]].single_char and chunks2[p[1]].single_char:
            if chunks1[p[0]].char == chunks2[p[1]].char:
                for i in range(2):
                    p[i] += 1
                continue
            else:
                break

        if chunks1[p[0]].single_char or chunks2[p[1]].single_char:
            break

        covering = chunks1[p[0]].offset(partial_matched[0]).covering(chunks2[p[0]].offset(partial_matched[1]))

        if covering == 0:
            break

        for i in range(2):
            partial_matched[i] += covering
        if partial_matched[0] == len(chunks1[p[0]]):
            p[0] += 1
            partial_matched[0] = 0
        if partial_matched[1] == len(chunks2[p[1]]):
            p[1] += 1
            partial_matched[1] = 0

    # print(list(map(str,chunks1)), list(map(str, chunks2)))

    if p[0] < len(chunks1) or p[1] < len(chunks2):
        print(1)
    else:
        print(0)
"""

        

