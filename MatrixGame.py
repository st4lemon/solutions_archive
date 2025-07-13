# https://codeforces.com/contest/2120/problem/D

MOD = 1000000007

def binexp(k, n):
    if n == 0:
        return 1
    ret = binexp(k, n // 2)
    ret **= 2
    if n % 2 == 1:
        ret *= k
    ret %= MOD
    return ret

def modinv(n):
    return binexp(n, MOD - 2)

def solve():
    A, B, K = map(int, input().split())
    L = ((A-1)*K + 1) % MOD
    R = (K * (B-1)) % MOD

    for i in range(A):
        R *= (L - i + MOD) % MOD
        R %= MOD
        R *= modinv(i+1)
        R %= MOD

    R += 1
    R %= MOD

    # each occurs once: K
    # number of permutations for a single coloring: (L choose A)
    # number for pigeonhole: K * (L choose A) * (B-1) + 1
    L %= MOD
    print(L, R)


T = int(input())
for _ in range(T):
    solve()


