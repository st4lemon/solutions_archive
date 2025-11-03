# Codeforces Round 965 #D: Determine Winning Islands in Race
# https://codeforces.com/contest/1998/problem/D
from collections import deque

def solve():
    N, M = map(int, input().split())

    adj = [[] for x in range(N)]

    for _ in range(M):
        x, y = map(int, input().split())
        x -= 1
        y -= 1
        adj[min(x, y)].append(max(x, y))

    # print(adj)

    sweep = [0 for x in range(N)]
    dist = [1e9 for x in range(N)]
    dist[0] = 0
    vis = [False for x in range(N)]

    q = deque()
    q.append((0, 0))

    while len(q) > 0:
        x, d = q.popleft()
        if vis[x]:
            continue
        vis[x] = True
        if x == N-1:
            continue
        if not vis[x+1]:
            dist[x+1] = min(dist[x+1], d+1)
            q.append((x+1, d+1))

        for a in adj[x]:
            # try taking bridge
            # bessie will move d+1 steps before you reach
            sweep[x+1] += 1
            sweep[max(x+1, a-(d+1))] -= 1
            if not vis[a]:
                dist[a] = min(dist[a], d+1)
                q.append((a, d+1))
    sum = 0
    for i in range(N-1):
        sum += sweep[i]
        if sum > 0:
            print(0, end='')
        else:
            print(1, end='')
    print()


T = int(input())
for _ in range(T):
    solve()
