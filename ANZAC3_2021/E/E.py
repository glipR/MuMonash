import cmath
p = 1#int(input())

def det(c1, c2):
    return (c1.conjugate() * c2).imag

def collision(a, b, c, d):
    ab = b-a
    dc = c-d
    ac = c-a
    s = det(ac,dc) / det(ab,dc)
    return a + s * ab

for case in range(p):
    n = int(input())
    points = [list(map(float, input().split())) for _ in range(n)]
    # for each of these points, we will find the collision point and normal vector.
    sides = []
    front_y = None
    for point in points:
        radius, a, b, c, d = point[0], complex(*point[1:3]), complex(*point[3:5]), complex(*point[5:7]), complex(*point[7:9])
        # Intersection
        centre = collision(a, b, c, d)
        normal = ((a-b)/abs(a-b)) + ((d-c)/abs(d-c))
        normal = normal / abs(normal)
        actual_collision = centre - normal * radius
        if abs(normal - complex(0, -1)) < 1e-8:
            front_y = actual_collision
        else:
            sides.append((actual_collision, normal))

    # Now to determine the positions.
    # Q1: Do I know the radius of the semi-circles?
    r = None
    # print(front_y, sides)
    if front_y is not None and sides:
        s_col = sides[0][0]
        s_nrm = sides[0][1]
        distance = abs(s_col.real - front_y.real) / 2
        cur_pos = (s_col.real + front_y.real) / 2
        if s_col.real > s_nrm.real:
            sign = -1
        else:
            sign = 1
        while distance > 1e-8:
            c = collision(complex(cur_pos, front_y.imag), complex(cur_pos, front_y.imag+1), s_col, s_col - s_nrm)
            d1, d2 = abs(c - complex(cur_pos, front_y.imag)), abs(c - s_col)
            if d1 > d2:
                cur_pos += distance * sign
            else:
                cur_pos -= distance * sign
            distance /= 2
        c = collision(complex(cur_pos, front_y.imag), complex(cur_pos, front_y.imag+1), s_col, s_col - s_nrm)
        r = abs(c - complex(cur_pos, front_y.imag))
    left = []
    right = []
    for c, n in sides:
        if n.real > 0:
            right.append((c, n))
        else:
            left.append((c, n))
    if len(left) >= 2:
        c1, n1 = left[0]
        c2, n2 = left[1]
        c = collision(c1, c1 - n1, c2, c2 - n2)
        r = abs(c - c1)
    elif len(right) >= 2:
        c1, n1 = right[0]
        c2, n2 = right[1]
        c = collision(c1, c1 - n1, c2, c2 - n2)
        r = abs(c - c1)
    # I suspect this can be done with two different sides too :(
    if r is None:
        # We don't know anything / can't get anything
        import sys
        print("unknown unknown unknown unknown")
        sys.exit(0)
    m_x, m_y, w = None, None, None
    l_c, r_c = None, None
    # TODO: Look at each of the sides to get semicircle centres
    for col, norm in sides:
        if norm.real > 0:
            r_c = col - norm * r
        else:
            l_c = col - norm * r
    if l_c is not None and r_c is not None:
        m_x = (l_c.real + r_c.real) / 2
        w = r_c.real - l_c.real
    if l_c is not None:
        m_y = l_c.imag
    if r_c is not None:
        m_y = r_c.imag
    print(" ".join([
        "unknown" if m_x is None else f"{m_x:.1f}",
        "unknown" if m_y is None else f"{m_y:.1f}",
        "unknown" if w is None else f"{w:.1f}",
        "unknown" if r is None else f"{r:.1f}",
    ]))

    


