# Bit implementation heavy, but use sqrt-decomp.
# Store the state of the table at each sqrt interval - taking into account both the distance, as well as operations committed.
# Then, we can get to all required positions in n*sqrt(n) time, which is just within bounds.
# For each of these saved intervals, compute the partial sum of elements, so we can binary search to find how many are above x_i
# Then move to the desired location in sqrt(n) time, updating the number of elements above as you move through.

# n * sqrt(n) * log(n)
