t = int(input())

def popcount(x):
    #print(f'popcount called with x={x}')
    ans = 0
    while x:
        ans += x & 1
        x >>= 1
    return ans

for _ in range(t):
    k = int(input())
    
    print(f"MOV R1, R0, LSL #0")
    print(f"SUB R0, R0, R0, LSL #0")

    shifter = 30
    
    n_loops = 0
    
    overshot = False
    while k != 0:
        n_loops += 1
        #print(f'n_loops={n_loops}, cur k={k}, shifter={shifter}')
        if n_loops == 50:
            break
        
        if 2**shifter > k:
            shifter -= 1
        else:
            # either add or sub from here
            option_a = k - (2**shifter)
            option_b = -(k - (2**(shifter+1)))

            if option_b < 0:
                print(f"ADD R0, R0, R1, LSL #{shifter+1}")
                k -= 2**(shifter+1)
                continue

            flag = False
            op_size = 0
            if popcount(option_b) < popcount(option_a):
                op_size = shifter + 1
                overshot = not overshot
                flag = True
            else:
                op_size = shifter
            
            if overshot ^ flag:
                print(f"SUB R0, R0, R1, LSL #{op_size}")
                k -= 2**op_size
                k = abs(k)
            else:
                print(f"ADD R0, R0, R1, LSL #{op_size}")
                k -= 2**op_size
                k = abs(k)
    print("END")
