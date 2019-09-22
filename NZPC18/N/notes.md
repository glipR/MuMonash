# Analysis of Robert King / Antony Phillips Solution.

This seems like it would TLE, since we could be doing 10^10 operations.

# Possible solution

First notice that for every worker, we can visualise the required weight time as some linear equation, where the y axis is the relative time required (Which needs to be multiplied by the previous M) to wait and the x axis is the ratio of newM to oldM.

The maximum line of wait time is generated from subsections of individual straight line segments.

As such we can store the gradient of each line (each possible interaction between M1 and M2). This can be computed in 10^5.

Then we can sort each solution in order of increasing ratio M2/M1.
Then, because of the graph structure, we can binary search over this set and compute the endpoints for which each worker becomes 'the worst'.

Between these endpoints we can find the wait times in O(1).

But for each ratio we actually explore this takes 10^5.

For most, if not all cases, we don't evaluate many of the endpoints (Since there can only be 10^4 contiguous sections, we expect a max of about 4*10^4).


You should compare this with a simple linear example for large random cases.
