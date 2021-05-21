# Greedily assign people
# Store r_customers, for each restaurant, a list of people they are currently holding, in a heapq with least favourite customer on top
# Store p_pref, for each person, the current restaurant index they are consider (so 0 for 1st preference, etc)
# Place the first person in their first choice
# Generally:
# When trying to place person p, check if p_pref is not at capacity, or [p_pref]_customers[-1] is lesser ranked than p (We can swap them)
# If swapping, increment customers[-1]_pref by 1, and try to place them
# Otherwise, try to place the next person

# Note that each of these operations is log(N) time, and we do at most 1000000 of these operations, since sum of p_pref cannot exceed 1000000 and every time we increment by 1.
# Surprised noone got this
