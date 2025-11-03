# Jumbled Primes (OCPC Fall 2023)
# https://codeforces.com/gym/105214/problem/J
from math import gcd, lcm, log10
from random import randrange, shuffle, seed


def solve(arr):
    def r():
        return randrange(1, 101, 1)

    def r2():
        a, b = r(), r()
        while a == b:
            a, b = r(), r()
        return min(a, b), max(a, b)

    def r3(arrr):
        n = len(arrr)
        a, b = 0, 0
        while a == b:
            a, b = randrange(0, n, 1), randrange(0, n, 1)
        return min(arrr[a], arrr[b]), max(arrr[a], arrr[b])

    def r4(arrr):
        n = len(arrr)
        a = randrange(0, n, 1)
        return arrr[a]

    cache = [[0 for x in range(101)] for y in range(101)]  # to prevent requerying
    best = [1 for x in range(101)]  # what we know so far, take lcm of results
    prime = [True for x in range(101)]  # 0 initially assume everything is prime, then change if proven otherwise.

    def query(a, b):
        if a > b:
            a, b = b, a
        if cache[a][b] == 0:
            print(f'? {a} {b}', flush=True)
            cache[a][b] = int(input())
            # cache[a][b] = gcd(arr[a-1], arr[b-1])
            # print("query:", a, b, f"({arr[a-1]}, {arr[b-1]})")
            # print("result:", cache[a][b])
            cache[0][0] += 1
            best[a] = lcm(best[a], cache[a][b])
            best[b] = lcm(best[b], cache[a][b])
        return cache[a][b]

    # find numbers with gcd 5, 6, 7
    gc5 = -1
    gc6 = -1
    gc7 = -1
    while gc5 == -1 or gc6 == -1 or gc7 == -1:
        a, b = r2()
        while a == b:
            a, b = r2()
        res = query(a, b)
        if res % 5 == 0 and gc5 == -1:
            gc5 = a
            if res % 6 == 0 and gc6 == -1:
                gc6 = b
            elif res % 7 == 0 and gc7 == -1:
                gc7 = b
        elif res % 6 == 0 and gc6 == -1:
            gc6 = a
            if res % 7 == 0 and gc7 == -1:
                gc7 = b
        elif res % 7 == 0 and gc7 == -1:
            gc7 = a
    # print(gc5, gc6, gc7)

    # classify every other number (use sets?)
    bin2 = []
    bin3 = []
    bin5 = []
    bin7 = []
    composite = []
    bigprime = []

    for i in range(1, 101):
        b2 = b3 = b5 = b7 = False
        if i == gc6:
            b2 = True
            b3 = True
        else:
            res = query(i, gc6)
            b2 = res % 2 == 0
            b3 = res % 3 == 0

        if b2 and b3:
            # composite.append(i)
            prime[i] = False
            continue

        if i == gc5:
            b5 = True
        else:
            res = query(i, gc5)
            b5 = res % 5 == 0

        if (b2 and b5) or (b3 and b5):
            # composite.append(i)
            prime[i] = False
            continue

        if i == gc7:
            b7 = True
        else:
            res = query(i, gc7)
            b7 = res % 7 == 0

        if (b2 and b7) or (b3 and b7) or (b5 and b7):
            # composite.append(i)
            prime[i] = False
            continue

        if b2:
            bin2.append(i)
        elif b3:
            bin3.append(i)
        elif b5:
            bin5.append(i)
        elif b7:
            bin7.append(i)
        else:
            bigprime.append(i)
            prime[i] = True

    primes = {}
    pcount = {}

    # determine prime powers
    # for 2 and 3: sample each list randomly to find an elem with gcd = p^2
    # then, filter bin2 with bigprimes:
    #   for elem in bin2:
    #     if gcd(elem, p^2) % p^2 == 0:
    #       it is composite
    # otherwise proceed as normal

    # print(bin2)
    # print([arr[i-1] for i in bin2])
    g4 = -1
    while g4 == -1:
        a, b = r3(bin2)  # get two random values from 2 set
        if query(a, b) % 4 == 0:
            g4 = a
            prime[a] = False
            prime[b] = False
            break

    # then filter through all big primes, add to primes list

    for curr in bin2:
        if curr == g4:
            continue
        if query(curr, g4) % 4 == 0:
            # composite.append(curr)
            prime[curr] = False
            continue
        # if not prime[curr]:
        #    continue
        prim = True
        for bp in bigprime:
            if prime[bp] and (best[bp] > 10):  # it is prime and we have identified it
                maxc = log10(100/best[bp])/log10(2)
                if bp not in pcount:
                    pcount[bp] = 0
                if pcount[bp]+1 > maxc:
                    continue
            res = query(curr, bp)
            if res > 1:
                # composite.append(curr)
                primes[res] = bp
                if bp not in pcount:
                    pcount[bp] = 0
                pcount[bp] += 1
                prime[curr] = False
                prim = False
                break
        if prim:
            prime[curr] = True
            for c2 in bin2:
                if c2 == curr:
                    continue
                prime[c2] = False

    # print(primes)
            # break
            # maybe go all the way through on bin2 so you can identify all primes, this way you know for sure which ones to skip later.

    # print(bin3)
    # print([arr[i-1] for i in bin3])
    g9 = -1
    while g9 == -1:
        a, b = r3(bin3)
        if query(a, b) % 9 == 0:
            g9 = a
            prime[a] = False
            prime[b] = False
            break

    for p in pcount:
        pcount[p] = 0
    # print(pcount)
    # print(bigprime)
    # print([arr[i-1] for i in bigprime])


    for curr in bin3:
        if curr == g9:
            continue
        if not prime[curr]:
            continue
        if query(curr, g9) % 9 == 0:
            # composite.append(curr)
            prime[curr] = False
            continue
        prim = True
        for p in primes:
            bp = primes[p]
            maxc = log10(100/p)/log10(3)
            if bp not in pcount:
                pcount[bp] = 0
            if pcount[bp]+1 > maxc:
                continue
            res = query(curr, bp)
            if res > 1:
                # composite.append(curr)
                if not bp in pcount:
                    pcount[bp] = 0
                pcount[bp] += 1
                prime[curr] = False
                prim = False
                break
        if prim:
            prime[curr] = True
            for c3 in bin3:
                if c3 == curr:
                    continue
                prime[c3] = False
            break
    # print("done")

    for p in pcount:
        pcount[p] = 0
    # for 5 and 7:
    # hard to differentiate between p and p^2
    # maybe do primelist first?
    #   5 25 55 65 85 95 : 5 5^2 5*11 5*13 5*17 5*19
    #   7 49 77 91       : 7 7^2 7*11 7*13
    # this then narrows it down to p and p^2.
    #   any number that is a multiple of p^2 must have best % p == 0

    #   for 5: 25, 50, 75, 100 (50 and 100 have been marked by 2 already)
    #   gcd = 10: 10, 20, 40, 50, 70, 80, 100
    #   2*7/2 ops expected. in 7 ops you cna find
    #   find something in gcd 10
    cand5 = []
    for curr in bin5:
        # do primelist first
        if not prime[curr]:
            continue
        prim = True
        for p in primes:
            bp = primes[p]
            maxc = log10(100/p)/log10(5)
            # any prime small enough can be here
            if bp not in pcount:
                pcount = 0
            if pcount[bp]+1 > maxc:
                continue
            res = query(curr, bp)
            if res > 1:
                if not bp in pcount:
                    pcount[bp] = 0
                pcount[bp] += 1
                prime[curr] = False
                prim = False
                break
        if prim:
            prime[curr] = False
            cand5.append(curr)

    if len(cand5) == 1:
        prime[cand5[0]] = True
    else:
        prime[cand5[0]] = True
        prime[cand5[1]] = True
        div10 = []
        for i in range(1, 101):
            if best[i] % 10 == 0:
                div10.append(i)
        # print("div10:", div10)
        # print([arr[i-1] for i in div10])
        g25 = -1
        while g25 == -1:
            a = r4(cand5)
            b = r4(div10)
            while a == b:
                a = r4(cand5)
                b = r4(div10)
            if query(a, b) % 25 == 0:
                g25 = a
                break
        prime[g25] = False
        # filter between cand5s and [best[i] = 10]

    # bin7 = [7, 49, 77, 91]
    # for 7: 49, 98
    # gcd = 14: 14, 28, 56, 98
    # 2*4 = 8 ops max
    for p in pcount:
        pcount[p] = 0

    cand7 = []
    for curr in bin7:
        if not prime[curr]:
            continue
        prim = True
        for p in primes:
            bp = primes[p]
            maxc = log10(100/p)/log10(7)
            if bp not in pcount:
                pcount[bp] = 0
            if pcount[bp]+1 > maxc:
                continue
            res = query(curr, bp)
            if res > 1:
                if not bp in pcount:
                    pcount[bp] = 0
                pcount[bp] += 1
                prime[curr] = False
                prim = False
                break
        if prim:
            prime[curr] = False
            cand7.append(curr)

    if len(cand7) == 1:
        prime[cand7[0]] = True
    else:
        prime[cand7[0]] = True
        prime[cand7[1]] = True
        div14 = []
        for i in range(1, 101):
            if best[i] % 14 == 0:
                div14.append(i)
        # print("div14:", div14)
        # print([arr[i - 1] for i in div14])
        g49 = -1
        while g49 == -1:
            a = r4(cand7)
            b = r4(div14)
            while a == b:
                a = r4(cand7)
                b = r4(div14)
            if query(a, b) % 49 == 0:
                g49 = a
                break
        prime[g49] = False
    # then, randomly select 2.


    # compare each bin with list of big primes

    """
    # print("bins:")
    g4 = -1
    for curr in bin2: # cast out composites by comparing with primes
        # can confirm a number arr[i-1] is a prime if:
        #   prime[i] = True
        #   best[i] > 10
        # print("curr:", arr[curr-1], best[curr], prime[curr])
        if best[curr] % 4 == 0:
            if g4 == -1:
                g4 = curr
            prime[curr] = False
        elif g4 != -1:
            if query(curr, g4) % 4 == 0:
                prime[curr] = False
        if not prime[curr]:
            continue
        prim = True
        for bp in bigprime:
            # cast out prime if:
            # no more left
            # too big
            if prime[bp] and (best[bp] > 10):
                # is a prime
                maxc = log10(100/best[bp])/log10(2)
                if bp not in pcount:
                    pcount[bp] = 0
                if pcount[bp]+1 > maxc: # if the number of times bp has been matched exceeds max k such that 2^k*bp <= 100, then it is used up.
                    continue
            res = query(curr, bp)
            if res > 1:
                composite.append(curr)
                primes[res] = bp
                if not bp in pcount:
                    pcount[bp] = 0
                pcount[bp] += 1
                prime[curr] = False
                prim = False
                break
        if prim:
            pow2.append(curr)

    rem = set()
    for m2 in pow2:
        if m2 == g4:
            break
        if best[m2] % 4 == 0:
            rem.add(m2)
            prime[m2] = False
        if query(m2, g4) % 4 == 0:
            rem.add(m2)
            prime[m2] = False
    for r in rem:
        pow3.remove(r)

    # print(pow2)
    # print([arr[i-1] for i in pow2])
    # print([best[i] for i in pow2])
    # print(primes)
    for p in primes:
        pcount[primes[p]] = 0

    # print("starting 3")
    g9 = -1
    for curr in bin3:
        # print("curr:", arr[curr-1], best[curr], prime[curr])
        if best[curr] % 9 == 0:
            if g9 == -1:
                g9 = curr
            prime[curr] = False
        elif g9 != -1:
            if query(curr, g9) % 9 == 0:
                prime[curr] = False
        if not prime[curr]:
            continue
        prim = True
        # print('made bp')
        for p in primes:
            bp = primes[p]
            # cast out prime if:
            # no more left
            # too big

            # is a prime
            # print("bp:", bp, p, pcount[bp])
            if prime[bp] and (best[bp] > 10):
                maxc = log10(100/best[bp])/log10(3)
                if not bp in pcount:
                    pcount[bp] = 0
                if pcount[bp]+1 > maxc: # if the number of times bp has been matched exceeds max k such that 2^k*bp <= 100, then it is used up.
                    continue
            res = query(curr, bp)
            if res > 1:
                if res % 9 == 0:
                    g9 = curr
                composite.append(curr)
                primes[res] = bp
                if bp not in pcount:
                    pcount[bp] = 0
                pcount[bp] += 1
                prime[curr] = False
                prim = False
                break
        if prim:
            pow3.append(curr)

    if g9 == -1:
        # all thats remaining is prime powers, compare them
        pass
    else:
        rem = set()
        for m3 in pow3:
            if m3 == g9:
                break
            if query(m3, g9) % 9 == 0:
                rem.add(m3)
                prime[m3] = False
        for r in rem:
            pow3.remove(r)

    # print(pow3)
    # print([arr[i-1] for i in pow3])
    # print(bin3)
    # print([arr[i-1] for i in bin3])
    # print([best[i] for i in pow3])
    """
    # print(primes)
    # print(gc5, gc6, gc7)
    # print(arr[gc5-1], arr[gc6-1], arr[gc7-1])

    # determine prime powers:


    # for 5 and 7: differentiate p^2 from p
    # print()
    # print([arr[i-1] for i in bin2])
    # print([arr[i-1] for i in bin3])
    # print([arr[i-1] for i in bin5])
    # print([arr[i-1] for i in bin7])
    # print([arr[i-1] for i in bigprime])

    # for i in range(1, 101):
        # pass
        # print("fin:", arr[i-1], "b:", best[i], prime[i])
    return cache[0][0], prime


cases = 1000
trueprimes = set()
trueprimes.add(2)
trueprimes.add(3)
trueprimes.add(5)
trueprimes.add(7)
for p in range(11, 101, 2):
    works = True
    for curr in trueprimes:
        if p%curr == 0:
            works = False
            break
    if works:
        trueprimes.add(p)
trueprimes.add(1)
# print(trueprimes)

arr = [i+1 for i in range(100)]
moves = 0
for _ in range(cases):
    # if _ % 1000 == 0:
        # print(_)
    # weird = []
    shuffle(arr)
    cnt, ans = solve(arr)
    # print()
    print('!', end=' ')
    for x in range(100):
        if ans[x+1]:
            print(1, end='')
            pass
        else:
            print(0, end='')
            pass
        # print(arr[x], arr[x] in trueprimes, ans[x+1])
        # if (arr[x] in trueprimes) ^ ans[x+1]:
            # weird.append(x)
    print(flush=True)
    # if not len(weird) == 0:
        # print(weird)
        # print([(arr[i], ans[i+1]) for i in weird])
    # print(cnt)
    # moves += cnt
# print("average:", moves/cases)
