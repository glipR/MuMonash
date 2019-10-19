n = int(input())
nums = list(map(int, input().split()))

class Node:
    def __init__(self, number, index, depth=-1):
        self.number = number
        self.index = index
        self.depth = depth

sorted_nums = sorted([Node(nums[i], i) for i in range(len(nums))], key=lambda x: (x.number, -x.index))

class EndPoint:
    def __init__(self, index, start=True, depth=-1):
        self.index = index
        self.is_start = start
        self.is_end = not start
        self.depth = depth

    def __str__(self):
        return "({}, depth: {})".format(self.index, self.depth)

end_points = [EndPoint(0, True, 1), EndPoint(n, False, 1)]
marked = [False] * n

for x in nums:
    #print(list(map(str, end_points)))
    l = -1
    r = n
    break_point = -1
    while r - l > 1:
        mid = (l + r) // 2
        if x >= sorted_nums[mid].number:
            if x == sorted_nums[mid].number and marked[mid]:
                r = mid
            else:
                l = mid
        else:
            r = mid
    break_point = l
    marked[break_point] = True
    #print(marked)

    l = -1
    r = len(end_points)
    while r - l > 1:
        mid = (l + r) // 2
        if end_points[mid].index <= break_point:
            l = mid
        else:
            r = mid

    left_end = l
    right_end = r

    sorted_nums[break_point].depth = end_points[l].depth

    end_points[l].depth += 1
    end_points[r].depth += 1
    end_points.insert(r, EndPoint(break_point, False, end_points[l].depth))
    end_points.insert(r+1, EndPoint(break_point+1, True, end_points[l].depth))


sorted_nums.sort(key=lambda x: x.index)
for num in sorted_nums:
    print(num.depth, end=' ')
print()

