# Reduced Row echelon form of some (r, c) matrix A, in place.
def rref(A):
    rows = len(A)
    cols = len(A[0])
    # Search down the rows, find the largest in each column,
    # and make it the only row with that column.
    r = 0
    for c in range(cols):
        if r >= rows:
            break
        # Find the row with maximum A[row][c]
        maxr = r
        for r2 in range(r+1, rows):
            if abs(A[r2][c]) > abs(A[maxr][c]):
                maxr = r2
        if abs(matrix[maxr][c]) < EPS:
            continue # Nothing for this column.
        # Swap it up to r
        A[maxr], A[r] = A[r], A[maxr]
        # Divide to make the column 1.
        s = 1 / A[r][c]
        A[r] = [A[r][x] * s for x in range(cols)]
        # Remove this column from every other row
        for i in range(rows):
            if i != r:
                for j in range(cols):
                    # This zeros the c column.
                    A[i][j] -= A[i][c] * A[r][j]
        r += 1
