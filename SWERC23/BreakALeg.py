
from math import atan2

N = int(input())

pts = []

for i in range(N):
    a, b = map(int, input().split())
    pts.append((a, b))


def cross(a, b):
    # print(a, b, a[0]*b[1] - a[1]*b[0])
    return a[0]*b[1] - a[1]*b[0]


def add(a, b):
    return a[0] + b[0], a[1] + b[1]


def scalar_mult(a, b):
    return a * b[0], a * b[1]


def sub(a, b):
    return a[0] - b[0], a[1] - b[1]


def mid(a, b, c):  # returns 3*midpoint
    return b[0]+a[0]+c[0], b[1]+a[1]+c[1]


def area(a, b, c):  # returns 2*area
    return cross(sub(b, a), sub(c, a))


total_area = 0  # 2 times actual area
total_center = (0, 0)  # 6 times actual center * area

for i in range(1, N-1):
    a = area(pts[0], pts[i], pts[i+1])
    c = mid(pts[0], pts[i], pts[i+1])
    total_area += a
    total_center = add(total_center, scalar_mult(a, c))

# print(total_area)
# print(total_center)

for i in range(N):
    pts[i] = scalar_mult(total_area*3, pts[i])

if pts.count(total_center) > 0:
    pts.remove(total_center)
    N -= 1

# print(pts)

# sort pts by angle?

pts.sort(key=lambda x: atan2(total_center[1] - x[1], total_center[0] - x[0]))

# print(pts)


ans = N * (N-1) * (N-2) // 6  # 3 choose 6

for i in range(N):
    # find last one to the left/on center dot
    low = 0
    high = N-1
    while low < high:
        m = (low + high + 1) // 2
        md = (m + i) % N
        # print(low, high, mid)
        if cross(sub(total_center, pts[i]), sub(pts[md], pts[i])) <= 0:
            low = m
        else:
            high = m - 1
    ans -= low * (low-1) // 2
    # (i, ": ", low,  ans)

print(ans)


