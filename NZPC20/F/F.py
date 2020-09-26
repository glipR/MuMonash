from collections import deque

DEBUG = False

SEEKING = 0
IN_TAG = 1

line = input().strip()
while line != '#':
    s = deque()
    idx = 0

    illegal = False

    while idx < len(line):
        if line[idx] != '<':
            idx += 1
            continue

        # We are at the start of a tag, parse the tag name by taking whitespace until
        # a space or \ or >

        inside_tag = ""
        idx += 1

        while idx < len(line) and line[idx] != '>':
            inside_tag += line[idx]
            idx += 1

        if idx == len(line):
            # At end of line with no closing >
            if DEBUG:
                print('no closing >, parsed {inside_tag}')

            illegal = True
            break
        else:
            assert line[idx] == '>'
            idx += 1

        tag_name = inside_tag.split(' ')[0]
        if tag_name.startswith('/'):
            # closing tag
            tag_name = tag_name[1:]
            if len(s) == 0:
                if DEBUG:
                    print(f'closing tag {tag_name} with empty tag')
                illegal = True
                break

            pairing_tag_name = s.pop()
            if tag_name != pairing_tag_name:
                if DEBUG:
                    print(f'mismatch of tags, opened with {pairing_tag_name} closed with {tag_name}')
                illegal = True
                break
        elif inside_tag.endswith('/'):
            # self closing tag
            pass

        else:
            # new tag
            s.append(tag_name)

    if len(s) != 0:
        if DEBUG:
            print(f'stack not empty: {str(s)}')
        illegal = True

    if illegal:
        print('illegal')
    else:
        print('legal')

    line = input().strip()
