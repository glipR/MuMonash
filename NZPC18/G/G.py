while True:
    line = input()
    if line == '#':
        break
    start_index = None
    numeric = False
    for index in range(len(line)):
        if numeric:
            try:
                float(line[start_index: index+1])
                assert line[start_index: index+1] == line[start_index: index+1].strip(), "Don't count spaces"
            except:
                numeric = False
                if line[index-1] == '.':
                    line = line[:start_index] + line[start_index:index-1][::-1] + line[index-1:]
                else:
                    line = line[:start_index] + line[start_index:index][::-1] + line[index:]
        else:
            if line[index] in '-+0123456789':
                if not numeric:
                    numeric = True
                    start_index = index
    if numeric:
        if line[-1] == '.':
            line = line[:start_index] + line[start_index:-1][::-1] + '.'
        else:
            line = line[:start_index] + line[start_index:][::-1]

    print(line[::-1])
