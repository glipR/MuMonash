class Chunk:
    def __init__(self, a, b=1e10 + 20000, single_char=False):
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
        if self.single_char or other.single_char:
            return False
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


merged_chunks = [[chunks1[0]], [chunks2[0]]]

for i, working_chunks in enumerate([chunks1, chunks2]):
    pointer = 1
    while pointer < len(working_chunks):
        if not merged_chunks[i][-1].merge(working_chunks[pointer]):
            merged_chunks[i].append(working_chunks[pointer])
        pointer += 1


#print(list(map(str,merged_chunks[0])), list(map(str, merged_chunks[1])))

if len(merged_chunks[0]) != len(merged_chunks[1]):
    print(1)
else:
    for i in range(len(merged_chunks[0])):
        if not merged_chunks[0][i].equals(merged_chunks[1][i]):
            print(1)
            break
    else:
        print(0)

