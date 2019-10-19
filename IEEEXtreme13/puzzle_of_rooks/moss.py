moves = []

def add_move(m):
    print(m)
    moves.append(m)

bw = 25
bh = 25

def print_board(pos, targets):
    print('\n'+'='*15)
    board = [['.' for _ in range(bw+1)] for _ in range(bh+1)]

    for p in pos:
        x, y = p
        board[y][x] = 'R'

    for t in targets:
        x, y = t
        if board[y][x] == 'R':
            board[y][x] = 'X'
        else:
            board[y][x] = 'T'

    for row in board:
        print(''.join(map(str, row)).replace('0', '.'))

n = int(input())

pos = []
targets = []

# Read rooks
for i in range(1, n+1):
    x, y = map(int, input().split())
    #x -= 1
    #y -= 1
    pos.append([-y, x])

# Read targets
for i in range(1, n+1):
    x, y = map(int, input().split())
    #x -= 1
    #y -= 1
    targets.append([-y, x])

# Sort targets by -y
targets = sorted(targets)
targets = [[x, -y] for y, x in targets]

# Sort rooks by -y
pos = sorted(pos)
pos = [[x, -y] for y, x in pos]

print_board(pos, targets)

# Move the rook of the leftmost target to be aligned along y

prev_tx = -1
ordered_x_targets = sorted(targets)
for tx, ty in ordered_x_targets:
    print_board(pos, targets)

    rook_idx = -1
    for i in range(n):
        if [tx, ty] == targets[i]:
            rook_idx = i

    # Move rook left until we're aligned
    while pos[rook_idx][0] > tx:
        # If we can move immediately left, do it
        can_move_left = -1
        for i in range(n):
            if pos[i][0] == pos[rook_idx][0] - 1:
                can_move_left = i

        if can_move_left == -1:
            # we can move left
            add_move(f'L {pos[rook_idx][0]} {pos[rook_idx][1]}')
            pos[rook_idx][0] -= 1
            continue

        # we need to pick up the rook with id 'can_move_left'
        add_move(f'T {pos[can_move_left][0]} {pos[can_move_left][1]}')

        # then move left
        add_move(f'L {pos[rook_idx][0]} {pos[rook_idx][1]}')
        pos[rook_idx][0] -= 1

        # then check we can move left again
        can_move_left_again = -1
        for i in range(n):
            if pos[i][0] == pos[rook_idx][0] - 1:
                can_move_left_again = i

        if can_move_left_again == -1:
            # if we can, lets get out of the way of the piece we picked up
            add_move(f'L {pos[rook_idx][0]} {pos[rook_idx][1]}')
            pos[rook_idx][0] -= 1

            # and put that piece back down
            add_move(f'P {pos[can_move_left][0]} {pos[can_move_left][1]}')

        else:
            # if we cant, move everything else left, in order from leftmost
            # to rightmost
            need_to_move = []
            for j, (rx, ry) in enumerate(pos):
                if rx < pos[can_move_left][0]:
                    need_to_move.append([rx, ry, j])
            need_to_move = list(sorted(need_to_move))
            for rx, ry, j in need_to_move:
                add_move(f'L {pos[j][0]} {pos[j][1]}')
                pos[j][0] -= 1

            # move our current rook left again
            add_move(f'L {pos[rook_idx][0]} {pos[rook_idx][1]}')
            pos[rook_idx][0] -= 1

            # and put that piece back down
            add_move(f'P {pos[can_move_left][0]} {pos[can_move_left][1]}')

    # Check that we are right of the previous target
    if rook_idx == 0:
        continue

    while pos[rook_idx][0] <= prev_tx:
        # move it right

        # check i can move right
        look_ahead = -1
        for i in range(n):
            if pos[i][0] == pos[rook_idx][0] + 1:
                look_ahead = i

        if look_ahead == -1:
            add_move(f'R {pos[rook_idx][0]} {pos[rook_idx][1]}')
            pos[rook_idx][0] += 1
        else:
            # move anything thats right of what is blocking me right twice
            need_to_move = []
            for j, (rx, ry) in enumerate(pos):
                if rx > pos[rook_idx][0] + 1:
                    need_to_move.append([rx, ry, j])
            need_to_move = list(sorted(need_to_move, key=lambda x: -x[0]))
            for rx, ry, j in need_to_move:
                add_move(f'R {pos[j][0]} {pos[j][1]}')
                pos[j][0] += 1
                add_move(f'R {pos[j][0]} {pos[j][1]}')
                pos[j][0] += 1

            # pick up that thing that blocks me
            add_move(f'T {pos[look_ahead][0]} {pos[look_ahead][1]}')

            # move me right twice
            add_move(f'R {pos[rook_idx][0]} {pos[rook_idx][1]}')
            pos[rook_idx][0] += 1
            add_move(f'R {pos[rook_idx][0]} {pos[rook_idx][1]}')
            pos[rook_idx][0] += 1

            # and put that piece back down
            add_move(f'P {pos[look_ahead][0]} {pos[look_ahead][1]}')
            # move it left once
            add_move(f'L {pos[look_ahead][0]} {pos[look_ahead][1]}')
            pos[look_ahead][0] -= 1

            # and finally move me left once
            add_move(f'L {pos[rook_idx][0]} {pos[rook_idx][1]}')
            pos[rook_idx][0] -= 1


    prev_tx = tx

for tx, ty in ordered_x_targets[::-1]:
    print_board(pos, targets)

    rook_idx = -1
    for i in range(n):
        if [tx, ty] == targets[i]:
            rook_idx = i

    while pos[rook_idx][0] < tx:
        add_move(f'R {pos[rook_idx][0]} {pos[rook_idx][1]}')
        pos[rook_idx][0] += 1

print_board(pos, targets)

ordered_y_targets = sorted(targets, key=lambda x: x[1])
for tx, ty in ordered_y_targets:
    rook_idx = -1
    for i in range(n):
        if [tx, ty] == targets[i]:
            rook_idx = i
    while pos[rook_idx][1] > ty:
        add_move(f'U {pos[rook_idx][0]} {pos[rook_idx][1]}')
        pos[rook_idx][1] -= 1

print_board(pos, targets)

ordered_y_targets = sorted(targets, key=lambda x: -x[1])
for tx, ty in ordered_y_targets:
    rook_idx = -1
    for i in range(n):
        if [tx, ty] == targets[i]:
            rook_idx = i
    while pos[rook_idx][1] < ty:
        add_move(f'D {pos[rook_idx][0]} {pos[rook_idx][1]}')
        pos[rook_idx][1] += 1

print_board(pos, targets)

print(len(moves))
for m in moves:
    op, x, y = m.split(' ')
    print(x, y, op)
