from collections import deque

R, C, S = map(int, input().split())

grid = [input() for x in range(R)]

# find slots

slots = []
for row in range(R):
    last = -1
    for col in range(C):
        if last == -1:
            if grid[row][col] == '.':
                last = col
        else:
            if grid[row][col] == '#':
                if col - last >= 2:
                    slots.append((row, last, 0, col - last))
                last = -1
    if last != -1 and C - last >= 2:
        slots.append((row, last, 0, C - last))

for col in range(C):
    last = -1
    for row in range(R):
        if last == -1:
            if grid[row][col] == '.':
                last = row
        else:
            if grid[row][col] == '#':
                if row - last >= 2:
                    slots.append((last, col, 1, row - last))
                last = -1
    if last != -1 and R - last >= 2:
        slots.append((last, col, 1, R - last))

slots.sort()
N = len(slots)

rs = [[-1 for x in range(C)] for y in range(R)]
cs = [[-1 for x in range(C)] for y in range(R)]

for i in range(N):
    s = slots[i]
    for k in range(s[3]):
        x = s[0] + s[2]*k
        y = s[1] + (1 - s[2]) * k
        if s[2] == 0:
            rs[x][y] = i
        else:
            cs[x][y] = i

# for i in range(R):
#     for j in range(C):
#         print(rs[i][j], end=' ')
#     print()
# print()
# for i in range(R):
#     for j in range(C):
#         print(cs[i][j], end=' ')
#     print()
# print()

words = [[x for x in input().split()] for y in range(N)]

# set up constraints and graph

cstr = [0 for x in range(N)]

def setc(n, v):
    if cstr[n] == 3-v:
        print(0)
        exit(0)
    cstr[n] = v

adj = [set() for x in range(2*N)]

for i in range(R):
    for j in range(C):
        row = rs[i][j]
        col = cs[i][j]
        if row < 0 or col < 0:
            # no constraint
            continue
        rind = j - slots[row][1]
        cind = i - slots[col][0]
        # print(row, rind, col, cind)
        r = (words[row][0][rind], words[row][1][rind])
        c = (words[col][0][cind], words[col][1][cind])
        # print(i, j, r, c)

        # case 1: contradiction
        if r[0] not in c and r[1] not in c:
            print(0)
            exit(0)
        elif r[0] == r[1] and r[0] == c[0] and r[0] == c[1]:
            continue # no new conditions
        elif r[0] == r[1]:
            if r[0] == c[0]:
                setc(col, 1)
            else:  # r[0] == c[1]
                setc(col, 2)
        elif c[0] == c[1]:
            if c[0] == r[0]:
                setc(row, 1)
            else:
                setc(row, 2)
        elif r[0] == c[0] and r[1] == c[1]:
            # draw edge
            adj[2*row].add(2*col)
            adj[2*col].add(2*row)
            adj[2*row+1].add(2*col+1)
            adj[2*col+1].add(2*row+1)
        elif r[0] == c[1] and r[1] == c[0]:
            adj[2*row].add(2*col+1)
            adj[2*col].add(2*row+1)
            adj[2*row+1].add(2*col)
            adj[2*col+1].add(2*row)
        elif r[0] == c[0]:
            setc(row, 1)
            setc(col, 1)
        elif r[0] == c[1]:
            setc(row, 1)
            setc(col, 2)
        elif r[1] == c[0]:
            setc(row, 2)
            setc(col, 1)
        elif r[1] == c[1]:
            setc(row, 2)
            setc(col, 2)
#
# for i in range(2*N):
#     print(f"{i}:", end=' ')
#     for x in adj[i]:
#         print(x, end=' ')
#     print()
# check for component contradictions

def flood(n, c, arr):
    q = deque()
    q.append(n)
    arr[n] = c
    while len(q) > 0:
        x = q.popleft()
        for k in adj[x]:
            if arr[k] == 0:
                arr[k] = c
                q.append(k)


comp = [0 for x in range(2*N)]
nc = 0

for i in range(2*N):
    if comp[i] == 0:
        nc += 1
        flood(i, nc, comp)

for i in range(N):
    if comp[2*i] == comp[2*i+1]: # if there are contradictions
        print(0)
        exit(0)

# mark comps that have constraints
cmpcstr = set()

for i in range(N):
    if cstr[i] == 1:
        cmpcstr.add(comp[2*i])
    elif cstr[i] == 2:
        cmpcstr.add(comp[2*i+1])

for i in range(N):
    if comp[2*i] in cmpcstr and comp[2*i+1] in cmpcstr:
        # constraints contradict each other
        print(0)
        exit(0)


def binexp(n, k, m):
    if k == 0:
        return 1
    if k == 1:
        return n
    ret = binexp(n, k//2, m)
    ret *= ret
    if k % 2 == 1:
        ret *= n
    ret %= m
    return ret


print(binexp(2, nc // 2 - len(cmpcstr), 1000000007))

# print(comp)


""" 
3 4 4
....
.##.
....
ACCA BCCB
ACA BCB
ACA BCB
BCCA ACCB
"""