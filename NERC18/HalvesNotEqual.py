def solve():
    N = int(input())
    pref = [0 for x in range(10001)]
    pref[0] = N

    arr = []
    s = input().split()
    larg = 0
    for i in range(N):
        arr.append((int(s[i]), i))
        larg = max(larg, int(s[i])*2)

    for a, b in arr:
        # print(a, b)
        pref[a] -= 1
        pref[larg - a] += 1
    arr.sort()

    S = 2 * int(input())
    total = [0 for x in range(N)]
    for i in range(10001):
        if i > 0:
            pref[i] += pref[i - 1]
        # print(pref[i])
        if pref[i] >= S:
            for k in range(pref[i]):
                total[arr[N - k - 1][1]] += S / pref[i]
            break

        for k in range(pref[i]):
            total[arr[N - k - 1][1]] += 1
        S -= pref[i]
        # print(total, S)

    for a in total:
        print(a / 2)

     #print(pref[:15])


solve()