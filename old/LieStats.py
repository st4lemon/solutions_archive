# Lies, Damned Lies, and Statistics (Petrozavodsk 2014-15, Petr Mitrichev Contest 12)
# https://codeforces.com/gym/101385/attachments

from math import sqrt


def solve(mean, sd, med):
    N = 9
    target = (2*N+1)*sd*sd
    while N > 0:
        minimum = (N+1)*((mean-med)**2) + N*(((N+1)/N*(mean-med))**2)
        maximum = (mean-med)**2 + N*mean*mean + N*(100-mean)*(100-mean)
        if not 0 <= (N+1)/N*(mean-med)+mean <= 100:
            minimum = 1e9
        maxsum = med + N*100
        targmean = (2*N+1)*mean
        # print(maxsum, targmean)
        # add N elements on each side, make as many 0 and as many 100 as possible.
        iters = 0
        while maxsum > targmean:
            if iters >= N:
                maximum = -1
                break
            diff = maxsum - targmean
            if diff < 100 - med:
                maxsum = targmean
                maximum -= (mean-100)**2
                maximum += (100-mean-diff)**2
                break
            else:
                maxsum -= 100-med
                maximum -= (mean-100)**2
                maximum += (mean-med)**2
            iters += 1
        iters = 0
        while maxsum < targmean:
            # print(iters, maxsum, targmean)
            if iters >= N:
                maximum = -1
                break
            diff = targmean - maxsum
            if diff < med:
                maxsum = targmean
                maximum -= (mean)**2
                maximum += (mean-diff)**2
                break
            else:
                maxsum += med
                maximum -= (mean)**2
                maximum += (mean-med)**2
            iters += 1
        # print(N, minimum, target, maximum)
        if minimum <= target <= maximum:
            break
        else:
            N -= 1
            target = (2*N+1)*sd*sd
    if N == 0:
        if mean == med and sd == 0:
            return [mean]
        else:
            return None

    # size of each side N is found
    # assuming they are in one block, move them as far apart as possible.
    arr = [0 for x in range(2*N+1)]
    arr[N] = med
    if mean < med:
        arr[0:N] = [(N+1)/N*(mean-med)+mean for x in range(N)]
        arr[N+1:2*N+1] = [med for x in range(N)]
    else:
        arr[N+1:2*N+1] = [(N+1)/N*(mean-med)+mean for x in range(N)]
        arr[0:N] = [med for x in range(N)]
    # move as far as you can outwards
    dist = min(arr[0], 100-arr[-1])
    # print(N*((mean-arr[0]+dist)**2 + (arr[-1]+dist-mean)**2) + (mean-med)**2, target)

    if N*((mean-arr[0]+dist)**2 + (arr[-1]+dist-mean)**2) + (mean-med)**2 >= target:
        low = 0
        high = dist
        while high - low > 1e-14:
            m = (low+high)/2
            # print(low, high, m)
            # print(N * ((mean - arr[0] + m) ** 2 + (arr[-1] + m - mean) ** 2) + (mean - med) ** 2)
            if N * ((mean - arr[0] + m) ** 2 + (arr[-1] + m - mean) ** 2) + (mean - med) ** 2 >= target:
                high = m
            else:
                low = m
        for i in range(N):
            arr[i] -= low
            arr[-(i+1)] += low
    else:
        def calc():
            return sum([(aa-mean)**2 for aa in arr])

        for i in range(N):
            arr[i] -= dist
            arr[-(i+1)] += dist
        currsd = calc()
        # print(currsd, target, arr)

        # move as many things to 100 as possible
        left = N+1
        right = 2*N
        while left < right and target-currsd > 1e-11:
            # print(left, right, arr[left], arr[right])
            # print(target, currsd, calc())
            dist = min(arr[left]-med, 100-arr[right])
            if 2 * dist * (arr[right]-arr[left] + dist) >= target - currsd:
                low = 0
                high = dist
                while high - low > 1e-14:
                    # print(high, low)
                    m = (low+high)/2
                    if 2 * m * (arr[right]-arr[left] + m) >= target - currsd:
                        high = m
                    else:
                        low = m
                arr[left] -= low
                arr[right] += high
                currsd = calc()
            else:
                currsd += 2 * dist * (arr[right]-arr[left] + dist)
                arr[left] -= dist
                arr[right] += dist
            if arr[left] == med:
                left += 1
            if arr[right] == 100:
                right -= 1

        left = 0
        right = N-1
        while left < right and target-currsd > 1e-11:
            # print(left, right, arr[left], arr[right])
            # print(target, currsd, calc())
            # print(arr)
            dist = min(arr[left], med - arr[right])
            if 2 * dist * (arr[right]-arr[left] + dist) >= target - currsd:
                # print(2 * dist * (arr[right]-arr[left] + dist))
                # print(arr)
                low = 0
                high = dist
                while high - low > 1e-14:
                    m = (low + high) / 2
                    # print(low, high, m)
                    # print(2 * m * (arr[right]-arr[left] + m))
                    if 2 * m * (arr[right]-arr[left] + m) >= target - currsd:
                        high = m
                    else:
                        low = m
                arr[left] -= low
                arr[right] += low
                currsd = calc()
            else:
                currsd += 2 * dist * (arr[right] - arr[left] + dist)
                arr[left] -= dist
                arr[right] += dist
            if arr[left] == 0:
                left += 1
            if arr[right] == med:
                right -= 1

    return arr


r = open("stats.in", "r")
w = open("stats.out", "w")

T = int(r.readline())
for _ in range(T):
    MEAN, SD, MED = map(int, r.readline().split())
    # print(MEAN, SD, MED)
    a = solve(MEAN, SD, MED)
    if a is None:
        w.write(f'{-1}\n')
        continue
    w.write(f'{len(a)} ')
    for aa in a:
        w.write(f'{aa} ')
    w.write('\n')
    # avg = sum(a)/len(a)
    # print(avg)
    # var = sum([(avg-aa)**2 for aa in a])/len(a)
    # print(var**0.5)
    # median = a[len(a)//2]
    # if abs(SD-var**0.5) > 1e-7 or abs(MEAN-avg) > 1e-7 or abs(MED-median) > 1e-7:
        # print(avg, var**0.5, median)
        # print(MEAN, SD, MED)
        # print()
    # print(a[len(a)//2])
    # print()

