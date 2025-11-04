N, E = map(int, input().split())

if N == 1:
    if E >= 1:
        print("infinity")
    else:
        print(0)
    exit(0)

# compute first layer

bn = [[0 for x in range(N)]]

last = [-1 for x in range(N)]
last[0] = 0
curr = 0
for i in range(3 * N, -1, -1):
    curr += (i + 1) % N
    curr %= N
    if last[curr] != -1:
        bn[0][last[curr] % N] = last[curr] - i
    last[curr] = i

# print(bn[0])

cnt = [bn[0].copy()]
brick = [[cnt[0][i] * (cnt[0][i] - 1) // 2 for i in range(N)]]
# binary lift until greater than E

while bn[-1][E % N] <= E:
    k = len(bn)
    bn.append([0 for x in range(N)])
    cnt.append([0 for x in range(N)])
    brick.append([0 for x in range(N)])
    for i in range(N):
        bn[k][i] = bn[k - 1][i] - 2 + bn[k - 1][(i - (bn[k - 1][i] - 2)) % N]
        cnt[k][i] = cnt[k - 1][i] + cnt[k - 1][(i - (bn[k - 1][i] - 2)) % N]
        brick[k][i] = brick[k - 1][i] + cnt[k - 1][(i - (bn[k - 1][i] - 2)) % N] * (bn[k - 1][i] - 2) + brick[k - 1][
            (i - (bn[k - 1][i] - 2)) % N]
    if bn[k][E % N] == bn[k - 1][E % N]:
        print("infinity")
        exit(0)
    # print(bn[k][E%N], bn[k-1][E%N])

# reconstruct path to E.

ans = 0
curr = E
for k in range(len(bn) - 1, -1, -1):
    if bn[k][curr % N] > curr:
        continue
    ans += cnt[k][curr % N] * curr - brick[k][curr % N]
    curr -= bn[k][curr % N]
    curr += 2

print(ans + (curr * (curr + 1) // 2))