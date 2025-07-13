/*

https://codeforces.com/gym/103098/problem/A
2020-2021 Winter Petrozavodsk Camp, UPC Contest #A: Adjacent Rooks

You are given T (1 <= T <= 5000) test cases. In each test case, count the number of ways to place N (1 <= 1000) rooks on an NxN chessboard such that no two rooks are in the same row or column and there are exactly K (<= N-1) pairs of rooks that are diagonally adjacent. Print your answer modulo 10^9 + 7.


Solution:
Naively, the immediate answer I think of is using dp, where dp[i][j] = number of ways to place i rooks on an i-by-i chessboard with j diagonally adjacent pairs. When we transition from i rooks to i+1 rooks, we can imagine creating a new row in between two other rows on the length-i chessboard (or creating a new row at the edges), and placing a new rook on the far right column of that new row. If the row happens to split up two previously adjacent rooks, then we must decrement the number of adjacent pairs by 1; thus for each transition we know that there are two possible transitions which add an adjacent pair (next to the rook placed in the previous column), and k possible transitions which delete an adjacent pair (if the new row divides the old pair). 

  0X00          0X00          0X000
  X000                        0000X
  00X0  ===>    X000   ===>   X0000         
  000X          00X0          00X00
                000X          000X0
        (This shows an example of choosing a row to add, note that it splits a pair)

However, there is one extra case: what if the previously rightmost rook is part of an adjacent pair? 

  X00        X00        X000
  00X  ===>  00X  ===>  00X0
  0X0                   000X
             0X0        0X00

Then, there is some overlap betwee the cases where we add and subtract a pair, which we must handle differently. 

The solution is to have two dp arrays that represent these two kinds of board states. 

A[i][j] = number of ways to place i rooks such that there are j diagonal adjacencies, and the rightmost rook does not form a pair
B[i][j] = number of ways to place i rooks such that there are j diagonal adjacencies, and the rightmost rook forms a pair

It is easy to precompute this dp table ahead of time, so we compute both 1000x1000 tables and then process each test case by summing A[N][K] + B[N][K]

*/

#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007

typedef long long ll;


int main() {
    int T;
    cin >> T;

    int MAXN = 1000;

    vector<vector<ll>> A(MAXN+1, vector<ll>(MAXN, 0));
    vector<vector<ll>> B(MAXN+1, vector<ll>(MAXN, 0));
    A[1][0] = 1;
    B[2][1] = 2;

    for(int i = 2; i<MAXN; i++) {
        for(int k = 0; k<i; k++) {
            A[i][k] %= MOD;
            B[i][k] %= MOD;

            B[i+1][k+1] += 2*A[i][k] + B[i][k];
            B[i+1][k] += B[i][k];
            if(k > 0) A[i+1][k-1] += k*A[i][k] + (k-1)*B[i][k];
            A[i+1][k] += (i-k-1)*A[i][k] + (i-k)*B[i][k];
        }
    }

    for(int k = 0; k<MAXN; k++) {
        A[MAXN][k] %= MOD;
        B[MAXN][k] %= MOD;
    }

    for(int i = 0; i<T; i++) {
        int N, K;
        cin >> N >> K;
        cout << (A[N][K] + B[N][K]) % MOD << endl;
    }

}
