# Max heap
import heapq

n, sx, sy = list(map(int, input().split()))
block_heights = list(sorted(list(map(int, input().split()))))

# print(block_heights)

def how_many_shaded(heights):
    # Try calculating the currently shaded blocks.
    current_block = -1
    shaded = 0
    for i in range(n-1,-1,-1):
        if current_block == -1:
            current_block = i
            continue
        # Is this block shaded by current block?
        horizontal_distance = current_block - i
        vertical_distance = heights[current_block] - heights[i]
        if sy / sx - 1e-9 <= vertical_distance / horizontal_distance:
            # Shaded
            print(i)
            shaded += 1
        else:
            # Not shaded
            current_block = i

    return shaded

def can_we_shade(n_blocks, heights):
    # print(n_blocks)
    """Is there an arrangement of heights SUCH THAT n_blocks are shaded"""
    not_shaded = n - n_blocks
    non_shaded_blocks = heights[-not_shaded:]
    non_shaded_blocks = [-(x - sy/sx) for x in non_shaded_blocks]
    heapq.heapify(non_shaded_blocks)
    # Make sure that the rest of the blocks can be shaded
    for i in range(n_blocks-1, -1, -1):
        # print(heights[i], non_shaded_blocks)
        # Go through all shaded blocks in decreasing size.
        elem = - heapq.heappop(non_shaded_blocks)
        if heights[i] <= elem + 1e-9:
            # Possible - update the locations
            elem = elem - sy / sx
            heapq.heappush(non_shaded_blocks, -elem)
        else:
            return False
    return True

# We want to find the maximum number of shaded blocks using binary search
lo = 0
hi = n
while hi - lo > 1:
    mid = (hi + lo) // 2
    # Can we shade mid blocks?
    if can_we_shade(mid, block_heights):
        lo = mid
    else:
        hi = mid

print(lo)
