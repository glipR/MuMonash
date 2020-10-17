n_types = int(input())

def bad():
    print('No')
    import sys
    sys.exit(0)

def good():
    print('Yes')
    import sys
    sys.exit(0)


mary_lower, mary_upper = list(map(int, input().split()))
marty_lower, marty_upper = list(map(int, input().split()))

free_pieces = 0
required_pieces = 0

for _ in range(n_types):
    # total number of pieces of this type
    k = int(input())

    if (k%2)==1:
        required_pieces += (k-1)//2
        free_pieces += 1
    else:
        required_pieces += k//2

mary = required_pieces
marty = required_pieces

mary_needed_to_lower_bound = max(mary_lower - mary, 0)
if mary_needed_to_lower_bound > free_pieces:
    #print(1)
    bad()

free_pieces -= mary_needed_to_lower_bound
mary += mary_needed_to_lower_bound

marty_needed_to_lower_bound = max(marty_lower - marty, 0)
if marty_needed_to_lower_bound > free_pieces:
    #print(2)
    bad()

free_pieces -= marty_needed_to_lower_bound
marty += marty_needed_to_lower_bound

if mary > mary_upper or marty > marty_upper:
    #print(3)
    bad()


#print(f'mary={mary}')
#print(f'marty={marty}')
#print(f'free_pieces={free_pieces}')
buffer_left = (mary_upper - mary) + (marty_upper - marty)

if free_pieces <= buffer_left:
    good()
else:
    #print(4)
    bad()
