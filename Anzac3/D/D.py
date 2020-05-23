from math import sqrt

def read_coord():
    return list(map(int, input().split()))

def d(ax, ay, bx, by):
    return sqrt((ax-bx)**2 + (ay-by)**2)

ball = read_coord()
bx, by = ball

offense = [read_coord() for _ in range(11)]
defense = [read_coord() for _ in range(11)]

oet = False

for i in range(11):
    #print('looking at offense player', i)
    px, py = offense[i]

    in_opponent_side = px > 0
    if not in_opponent_side:
        continue

    dist_to_goal_line = abs(50-px)
    dist_to_ball = abs(50-bx)
    #d(px, py, bx, by)
    dist_to_players = [abs(50-ox) for ox, oy in defense]
    closer_than_goal_line = [a < dist_to_goal_line for a in dist_to_players]

    #print('dist_to_goal_line', dist_to_goal_line)
    #print('dist_to_ball', dist_to_ball)

    #print(dist_to_players)
    #print(closer_than_goal_line)
    #print(sum(closer_than_goal_line))

    if (dist_to_goal_line < dist_to_ball) and sum(closer_than_goal_line) <= 1:
        oet = True
        break

if oet:
    print(1)
else:
    print(0)
