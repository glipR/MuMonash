class Player:
    def __init__(self):
        self.wins = 0
        self.idd = 0
        self.dif = 0
        self.name = ""

    def __str__(self):
        return '{} - {} - {} - {}'.format(self.name, self.wins, self.dif, self.idd)

n = int(input())

players = [Player() for i in range(n)]

for j in range(n):
    l = input().split()
    index = 0
    wins = 0
    dif = 0
    for i in range(len(l)-1):
        if l[i+1] == 'X':
            index = i
        else:
            l[i+1] = int(l[i+1])
            wins += 1 if l[i+1] == 7 else 0
            dif += l[i+1]
            players[i].dif -= l[i+1]
    players[index].wins += wins
    players[index].dif += dif
    players[index].idd = n-j
    players[index].name = l[0]

players.sort(key=lambda x: 10000*x.wins + 100*x.dif + x.idd)
players.reverse()
#print(' | '.join(map(str, players)))

print(players[0].name, end='')
for i in range(1, n):
    if players[i].wins == players[0].wins and players[i].dif == players[0].dif:
        print(' {}'.format(players[i].name), end='')
    else:
        break

print(" won with {} wins and {}{} points difference.".format(players[0].wins, '+' if players[0].dif > 0 else ('' if players[0].dif < 0 else ''), players[0].dif))


