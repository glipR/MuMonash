city1 = input()
m1, d1, hm1 = input().split()
h1, mm1 = hm1.split(':')
m1, d1, h1, mm1 = int(m1), int(d1), int(h1), int(mm1)

time = [h1, mm1]

tz1 = input()
hd1, md1 = map(int, tz1[1:].split(':'))
if (tz1[0] == '-'):
    time[0] += hd1
    time[1] += md1
else:
    time[0] -= hd1
    time[1] -= md1

city2 = input()
tz2 = input()
hd2, md2 = map(int, tz2[1:].split(':'))
if (tz2[0] == '+'):
    time[0] += hd2
    time[1] += md2
else:
    time[0] -= hd2
    time[1] -= md2

th, tm = map(int, input().split(':'))

time[0] += th
time[1] += tm

while time[1] < 0:
    time[1] += 60
    time[0] -= 1
while time[1] >= 60:
    time[1] -= 60
    time[0] += 1

print('Departs', city1, '%02d' % m1, '%02d' % d1, '%02d:%02d' % (h1, mm1))

if (time[0] >= 24):
    time[0] -= 24
    print('Arrives', city2, '%02d:%02d' % (time[0], time[1]), 'following day')
else:
    print('Arrives', city2, '%02d:%02d' % (time[0], time[1]), 'same day')






