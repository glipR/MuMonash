from collections import deque
from copy import deepcopy

r, c = map(int, input().split())

# -1 in grid denotes unoccupied

while r != 0 and c != 0:
    grid = [[-1 for _ in range(c)] for _ in range(r)]

    solved_positions = []
    lines = []
    pos_to_lines = {}
    lines_unused = set()

    # r*c lines to process
    for _ in range(r*c):
        r1, c1, r2, c2 = map(int, input().split())

        r1 -= 1
        c1 -= 1
        r2 -= 1
        c2 -= 1

        if r1 < 0 or c1 < 0 or r1 >= r or c1 >= c:
            # 1st point out of grid

            if r1 == r2:
                # went left or right, data is abs(c1-c2)
                grid[r2][c2] = abs(c1-c2)
            else:
                # went up or down, data is abs(r1-r2)
                grid[r2][c2] = abs(r1-r2)

            solved_positions.append((r2, c2))
        elif r2 < 0 or c2 < 0 or r2 >= r or c2 >= c:
            # 2nd point out of grid

            if r1 == r2:
                # went left or right, data is abs(c1-c2)
                grid[r1][c1] = abs(c1-c2)
            else:
                # went up or down, data is abs(r1-r2)
                grid[r1][c1] = abs(r1-r2)

            solved_positions.append((r1, c1))
        else:
            # regular line
            line_id = len(lines)
            lines.append((r1, c1, r2, c2))
            lines_unused.add(line_id)

            pos_1 = (r1, c1)
            pos_2 = (r2, c2)

            if pos_1 not in pos_to_lines:
                pos_to_lines[pos_1] = []

            if pos_2 not in pos_to_lines:
                pos_to_lines[pos_2] = []

            pos_to_lines[pos_1].append(line_id)
            pos_to_lines[pos_2].append(line_id)

    # finished with input

    # solve any lines that now lie on a position that is already solved
    invalid = False
    while len(solved_positions) > 0:
        solved_pos = solved_positions.pop()
        y, x = solved_pos

        if solved_pos not in pos_to_lines:
            continue

        associated_lines = pos_to_lines[solved_pos]
        for line_id in associated_lines:
            # check if we have already stood this line up
            if line_id not in lines_unused:
                continue

            r1, c1, r2, c2 = lines[line_id]

            if r2 == y and c2 == x:
                r1, r2 = r2, r1
                c1, c2 = c2, c1

            # 1st point is now the solved pos
            # we want to stand it up on the 2nd pos

            if grid[r2][c2] != -1:
                # grid position expected to be empty but not
                invalid = True
                break

            if r1 == r2:
                # went left or right, data is abs(c1-c2)
                grid[r2][c2] = abs(c1-c2)
            else:
                # went up or down, data is abs(r1-r2)
                grid[r2][c2] = abs(r1-r2)

            solved_positions.append((r2, c2))

            # this line has now been used
            lines_unused.remove(line_id)

        if invalid:
            break

    if invalid:
        print("No solution")
        r, c = map(int, input().split())
        continue

    # finished solving tautological positions

    def solve(_grid, _lines_unused):
        if len(_lines_unused) == 0:
            return [deepcopy(_grid)]

        # take snapshot of available lines so we dont
        # screw with the iteration
        lu = [x for x in _lines_unused]

        answers = []

        for line_id in lu:
            _lines_unused.remove(line_id)

            # take one line and try to stand it up both ways
            r1, c1, r2, c2 = lines[line_id]

            # check if its ok to stand up on 1st pos
            first_pos_clear = _grid[r1][c1] == -1
            second_pos_clear = _grid[r2][c2] == -1

            if first_pos_clear:
                if r1 == r2:
                    _grid[r1][c1] = abs(c1-c2)
                else:
                    _grid[r1][c1] = abs(r1-r2)

                """
                # stand other lines up that originate from (r1,c1)
                stood_up_lines = []
                stood_up_poss = []
                for line_id in pos_to_lines[(r1, c1)]:
                    if line_id not in _lines_unused:
                        continue

                    if r1 == r2:
                        _grid[r1][c1] = abs(c1-c2)
                    else:
                        _grid[r1][c1] = abs(r1-r2)
                """

                # recurse
                answers.extend(solve(_grid, _lines_unused))

                # reset state
                _grid[r1][c1] = -1

                """
                for line_id in stood_up_lines:
                    _lines_unused.add(line_id)
                for y, x in stood_up_poss:
                    _grid[y][x] = -1
                """

            if second_pos_clear:
                if r1 == r2:
                    _grid[r2][c2] = abs(c1-c2)
                else:
                    _grid[r2][c2] = abs(r1-r2)

                # stand other lines up that originate from (r1,c1)

                # recurse
                answers.extend(solve(_grid, _lines_unused))

                # reset state
                _grid[r2][c2] = -1

            _lines_unused.add(line_id)

        return answers

    # do backtracking

    answers = solve(grid, lines_unused)
    if len(answers) != 1:
        print("No solution")
    else:
        solved_grid = answers[0]
        for r in solved_grid:
            print(''.join(map(str, r)))

    # read dimensions for next problem
    r, c = map(int, input().split())
