import sys

from collections import deque

print = sys.stdout.write

W, H = map(int, input().split())

visg = [[False for x in range(W)] for y in range(H)]
grid = [[c for c in input()] for y in range(H)]
vist = [[False for x in range(W)] for y in range(H)]
targ = [[c for c in input()] for y in range(H)]

dx = [1, 0, -1, 0]
dy = [0, 1, 0, -1]


def solve(arr, comps, num):
    instr = []
    # print(arr, comps, num)
    for i in range(comps-1):
        ch = '.' if (i+num) % 2 == 0 else '#'
        c2 = '#' if (i+num) % 2 == 0 else '.'
        # print(ch, c2)
        q = deque()
        dist = [[1e9 for x in range(W)] for y in range(H)]
        for j in range(i, W - i):
            q.append((i, j))
            q.append((H - i - 1, j))
            dist[i][j] = 0
            dist[H - i - 1][j] = 0
        for j in range(i, H - i):
            q.append((j, W - i - 1))
            q.append((j, i))
            dist[j][W - i - 1] = 0
            dist[j][i] = 0

        color = []

        while len(q) > 0:
            x, y = q.popleft()
            for k in range(4):
                nx = x + dx[k]
                ny = y + dy[k]
                if nx < i+1 or nx >= H - i-1 or ny < i+1 or ny >= W - i-1:
                    continue
                if dist[nx][ny] <= dist[x][y] + 1:
                    continue
                if arr[nx][ny] != ch:
                    continue
                dist[nx][ny] = dist[x][y] + 1
                q.append((nx, ny))
                color.append((nx, ny))

        def okay(x, y, z):
            # check if we can flip (x, y) to color c2
            dxx = [1, 1, 1, 0, -1, -1, -1, 0]
            dyy = [1, 0, -1, -1, -1, 0, 1, 1]
            d = []
            for k in range(8):
                nx = x + dxx[k]
                ny = y + dyy[k]
                if nx < z or nx >= H - z or ny < z or ny >= W - z:
                    d.append(False)
                elif arr[nx][ny] == c2:
                    d.append(True)
                else:
                    d.append(False)

            # check there exists an adjacent square
            if not (d[1] or d[3] or d[5] or d[7]):
                return False

            # check the diagonal case
            for i in range(0, 8, 2):
                if d[i] and not (d[(i-1)%8] or d[(i+1)%8]):
                    return False

            # check the enclose case
            for i in range(1, 4, 2):
                if d[i] and d[(i+4)%8] and not (d[(i+2)%8] ^ d[(i-2)%8]):
                    return False

            return True

        color.reverse()
        changed = True
        while len(color) > 0:
            changed = False
            nc = []
            for x, y in color:
                if okay(x, y, i+1):
                    if arr[x][y] != c2:
                        arr[x][y] = c2
                        instr.append((x, y))
                else:
                    nc.append((x, y))
            color = nc
    return instr


def floodfill(x, y, arr, ch, vis):
    q = deque()
    q.append((x, y))
    vis[x][y] = True
    while len(q) > 0:
        X, Y = q.popleft()
        # print(X, Y)
        for k in range(4):
            nx = X + dx[k]
            ny = Y + dy[k]
            if nx < 0 or nx >= H or ny < 0 or ny >= W:
                continue
            if arr[nx][ny] != ch:
                continue
            if vis[nx][ny]:
                continue
            vis[nx][ny] = True
            q.append((nx, ny))

# check borders

works = True
for i in range(H):
    if grid[i][0] != targ[i][0]:
        works = False
        break
    if grid[i][W-1] != targ[i][W-1]:
        works = False 
        break

for i in range(W):
    if grid[0][i] != targ[0][i]:
        works = False
        break
    if grid[H-1][0] != targ[H-1][0]:
        works = False
        break

if not works:
    print("IMPOSSIBLE\n")
    exit(0)

# check num components

gc = 0
tc = 0
for i in range(H):
    for j in range(W):
        if not visg[i][j]:
            floodfill(i, j, grid, grid[i][j], visg)
            gc += 1
            # print("visg", i, j, gc)
        if not vist[i][j]:
            floodfill(i, j, targ, targ[i][j], vist)
            tc += 1
            # print("vist", i, j, tc)

if gc != tc:
    print("IMPOSSIBLE\n")
    exit(0)

# sixteen = False
# if W == 103 and H == 64 and grid[1][1] == '#' and tc > 10:
#     print(gc, tc)
#     sixteen = True

# solve

# print(gc, tc)

i1 = solve(grid, gc, 1 if grid[0][0] == '#' else 0)
i2 = solve(targ, tc, 1 if targ[0][0] == '#' else 0)
i2.reverse()
# print(i1)
# print(i2)
for x, y in i1:
    print(f"{y} {x}\n")
for x, y in i2:
    print(f"{y} {x}\n")

