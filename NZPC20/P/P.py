import math


def LCM(a, b):
    return (a * b) // math.gcd(a,b)


def is_weight(obj):
    return isinstance(obj, Weight)


class Thing:
    def __init__(self, X):
        self.weight = None
        self.parent = None
        self.id = X

        self.min_add = None


class Arm(Thing):
    def __init__(self, X):
        super().__init__(X)
        self.left = None
        self.right = None
        self.dL = None
        self.dR = None

    def all_left(self):
        return self.left.weight * self.dL

    def all_right(self):
        return self.right.weight * self.dR

    def is_leaf(self):
        return is_weight(self.left) and is_weight(self.right)

    def solve(self):
        if self.left.min_add is None:
            self.left.solve()
        if self.right.min_add is None:
            self.right.solve()

##################################################################################
        while self.all_left() != self.all_right():

            # print(type(self.left), self.left.id)
            # print(type(self.right), self.right.id)
            # print(self.left.weight, self.right.weight)
            # print(self.left.min_add, self.right.min_add)
            # input()

            if self.all_left() < self.all_right():
                min_add = self.left.min_add * self.dL
                amount = (self.all_right() - self.all_left()) // min_add
                if self.all_left() + min_add * amount < self.all_right():
                    amount += 1
                self.left.weight += amount * self.left.min_add

            if self.all_right() < self.all_left():
                min_add = self.right.min_add * self.dR
                amount = (self.all_left() - self.all_right()) // min_add
                if self.all_right() + min_add * amount < self.all_left():
                    amount += 1
                self.right.weight += amount * self.right.min_add
####################################################################################

        self.weight = self.left.weight + self.right.weight
        mins_comply = LCM(self.left.min_add, self.right.min_add)
        self.min_add = LCM(mins_comply, (self.dL + self.dR)//math.gcd(self.dL, self.dR))


class Weight(Thing):
    def __init__(self, X):
        super().__init__(X)
        self.weight = None

    def solve(self):
        if self.weight is None:
            self.weight = 1
        self.min_add = 1


def get_arm(x):
    if arms_map[x] is None:
        arms_map[x] = Arm(x)
    return arms_map[x]


def get_weight(x):
    if weights_map[x] is None:
        weights_map[x] = Weight(x)
    return weights_map[x]


n = int(input())
CASE = 1
while n != 0:

    arms_map = [None] * (n + 1)
    weights_map = [None] * (n * 2 + 1)

    for i in range(n):
        dL, dR, tL, tR, nL, nR = input().split()
        arm = get_arm(i + 1)
        arm.dL, arm.dR = int(dL), int(dR)

        if tL == 'W':
            arm.left = get_weight(int(nL))
        else:
            arm.left = get_arm(int(nL))
        if tR == 'W':
            arm.right = get_weight(int(nR))
        else:
            arm.right = get_arm(int(nR))

        arm.left.parent = arm.right.parent = arm

    m, w = list(map(int, input().split()))
    weights_map[m].weight = w

    answer = None
    for arm in arms_map:
        if arm is None:
            continue
        if arm.parent is None:
            arm.solve()
            answer = arm.weight
            break
    print("Case {}: {}".format(CASE, answer))

    CASE += 1
    n = int(input())
