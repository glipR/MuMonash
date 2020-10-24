from decimal import *
import decimal
import math
w, h, a, b, m, c = list(map(int, input().split()))

tile_horizontal = math.ceil(w / a)
tile_vertical = math.ceil(h / b)

getcontext().prec = 128
res = (Decimal(tile_horizontal * 1e-6) * Decimal(tile_vertical * 1e-6)) / Decimal(10)
mult = 0
while res < Decimal(1 / 100):
    res *= Decimal(10)
    mult += 1
actual_val = list(str(res)[2:16 - mult])
if int(actual_val[-1]) >= 5:
    for x in range(len(actual_val)-2, -1, -1):
        if actual_val[x] == '9':
            actual_val[x] = '0'
            continue
        else:
            actual_val[x] = str(int(actual_val[x]) + 1)
            break
actual_val = actual_val[:-1]
if actual_val[-1] != '0':
    for x in range(len(actual_val)-2, -1, -1):
        if actual_val[x] == '9':
            actual_val[x] = '0'
            continue
        else:
            actual_val[x] = str(int(actual_val[x]) + 1)
            break
actual_val = actual_val[:-1]
total = list("0") + actual_val
current = Decimal(0)
for x in range(len(total)):
    current += Decimal(total[-(x+1)])
    current /= Decimal(10)
for x in range(mult):
    current /= Decimal(10)
current /= Decimal(1e6)
current *= Decimal(m)
cut = 0
if w % a != 0:
    cut += h
if h % b != 0:
    cut += w
cut_cost = Decimal(1e-19)
cut_cost *= Decimal(cut)
cut_cost *= Decimal(c)
current += cut_cost
mult = 0
while current < Decimal(1 / 100):
    current *= Decimal(10)
    mult += 1
cur_val = list(str(current)[2:22-mult])
if int(cur_val[-1]) >= 5:
    for x in range(len(cur_val)-2, -1, -1):
        if cur_val[x] == '9':
            cur_val[x] = '0'
            continue
        else:
            cur_val[x] = str(int(cur_val[x]) + 1)
            break
del cur_val[-1]
while cur_val[0] == "0":
    del cur_val[0]
print("".join(cur_val))
