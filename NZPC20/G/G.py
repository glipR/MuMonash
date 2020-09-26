while True:
    turn = input()
    if turn == "#":
        break
    moves = list(map(int, turn.split()[1:]))
    state = [[None, None, None], [None, None, None], [None, None, None]]
    X = turn[0] == "X"
    for move in moves:
        state[(move - 1) // 3][(move - 1) % 3] = X
        X = not X

    winner = None
    # Evaluate all triples
    for a in range(3):
        for vals in [True, False]:
            bad = False
            for b in range(3):
                if state[a][b] != vals:
                    bad = True
                    break
            if not bad:
                winner = vals
    for a in range(3):
        for vals in [True, False]:
            bad = False
            for b in range(3):
                if state[b][a] != vals:
                    bad = True
                    break
            if not bad:
                winner = vals
    if state[0][0] == state[1][1] and state[1][1] == state[2][2] and state[0][0] is not None:
        winner = state[0][0]
    if state[2][0] == state[1][1] and state[1][1] == state[0][2] and state[2][0] is not None:
        winner = state[2][0]
    if winner is None:
        print("Draw")
    elif winner is True:
        print("X")
    else:
        print("O")