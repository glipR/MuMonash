from collections import defaultdict

n, k = list(map(int, input().split()))
community = input()
raised = input()

seen = defaultdict(lambda: False)
raised_first = defaultdict(lambda: None)
available = defaultdict(lambda: 4)

bad = False
for i in range(n):
    if not seen[community[i]]:
        seen[community[i]] = True
        if raised[i] == "y":
            raised_first[community[i]] = True
        else:
            raised_first[community[i]] = False
    else:
        if raised[i] != "y":
            bad = True
    available[community[i]] -= 1

count = defaultdict(lambda: 0)


cards = "23456789XJQKA"

for card in cards:
    if raised_first[card]:
        # We need at least one.
        count[card] += 1
        available[card] -= 1
        if available[card] < 0:
            bad = True

current = sum(count.values())

if current > k:
    bad = True

# Those with less available give more score
weighted = sorted([
    (available[cards[i]], i, cards[i])
    for i in range(len(cards))
])

card_index = 0
while current < k:
    if card_index == len(weighted):
        bad = True
        break
    if available[weighted[card_index][2]] > 0 and raised_first[weighted[card_index][2]] != False:
        available[weighted[card_index][2]] -= 1
        count[weighted[card_index][2]] += 1
        current += 1
    else:
        card_index += 1
if current < k:
    bad = True

if bad:
    print("impossible")
else:
    c = ""
    for card in cards:
        c = c + (card * count[card])
    print(c)
