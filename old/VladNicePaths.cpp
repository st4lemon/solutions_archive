// codeforces 863 problem G2: Vlad and the Nice Paths
#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

vector<int> clors[5005];

// C++ program to do modular division
#include<iostream>
using namespace std;

// C++ function for extended Euclidean Algorithm
long long gcdExtended(long long a, long long b, long long *x, long long *y);

// Function to find modulo inverse of b. It returns
// -1 when inverse doesn't
long long modInverse(long long b, long long m)
{
    long long x, y; // used in extended GCD algorithm
    long long g = gcdExtended(b, m, &x, &y);

    // Return -1 if b and m are not co-prime
    if (g != 1)
        return -1;

    // m is added to handle negative x
    return (x%m + m) % m;
}

// Function to compute a/b under modulo m
long long modDivide(long long a, long long b, long long m)
{
    a = a % m;
    long long inv = modInverse(b, m);
    return (inv * a) % m;
}

// C function for extended Euclidean Algorithm (used to
// find modular inverse.
long long gcdExtended(long long a, long long b, long long *x, long long *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }

    long long x1, y1; // To store results of recursive call
    long long gcd = gcdExtended(b%a, a, &x1, &y1);

    // Update x and y using results of recursive
    // call
    *x = y1 - (b/a) * x1;
    *y = x1;

    return gcd;
}

//this code is contributed by khushboogoyal499
// modular division from geeksforgeeks.com



void solve() {

    int N, K;
    cin >> N >> K;

    int color[N];
    int cnt[N];
    for(int i = 0; i<N; i++) {
        clors[i].clear();
        cin >> color[i];
        color[i]--;
    }

    for(int i = 0; i<N; i++) {
        cnt[i] = clors[color[i]].size();
        clors[color[i]].push_back(i);
    }

    // K is given to us lmao
    // we can do O[N] transition
    // for each dp[N]:
    //    find the other endpoint of the range of K locations of that color
    //    iterate from there to the end and find the greatest number (can be further optimized to provide O(1) tbh)
    //    keep track of the count alongside the DP state (prioritize the sequence length over amount)

    // TODO: use combinatoric functions to account for multiple permutations of a single color
    // ex:
    // 5 2
    // 1 1 2 2 2
    //
    // currently outputs 2, should output 3 because it doesn't account for the case of the first and third 2 being taken


    long long amount[N];
    int dp[N];

    for(int i = 0; i<N; i++) {
        dp[i] = 0;
        amount[i] = 0;
        if(cnt[i]<K-1) continue;
        int loc = clors[color[i]][cnt[i]-K+1]-1;
        dp[i] = K;
        amount[i] = 0;
        long long multiplier = 1;
        int nextCol = cnt[i]-K;
        for(int j = loc; j>=0; j--) {
            //cout << dp[i] << " " << amount[i] << " ---- " << j << " " << multiplier << " ----- " << i << " " << cnt[i] << " " << nextCol << endl;
            if(dp[j]+K>dp[i]) {
                dp[i] = dp[j]+K;
                amount[i] = amount[j]*multiplier;
                amount[i] %= MOD;
            }
            else if(dp[j]+K==dp[i]) {
                amount[i] += amount[j]*multiplier;
                amount[i] %= MOD;
            }

            if(nextCol>=0) {
                if(clors[color[i]][nextCol]==j) {
                    multiplier *= cnt[i]-nextCol;
                    multiplier %= MOD;
                    multiplier = modDivide(multiplier, cnt[i]-nextCol-K+1, MOD);
                    nextCol--;
                }
            }
        }
        if(dp[i]==K && amount[i]==0) amount[i] = multiplier;
    }

    int ans = 0;
    long long amt = 1;
    for(int i = 0; i<N; i++) {
        //cout << dp[i] << " " << amount[i] << endl;
        if(dp[i]>ans) {
            ans = dp[i];
            amt = amount[i];
        }
        else if(dp[i]==ans) {
            amt += amount[i];
            amt %= MOD;
        }
    }

    cout << amt << endl;

}

int main() {

    int T;
    cin >> T;

    for(int i = 0; i<T; i++) solve();

}
