/*

https://codeforces.com/contest/2049/problem/D
Codeforces Round 994 #D: Shift+Esc

You are given a grid with N rows and M columns (1 <= N, M <= 200) and an integer K (1 <= K <= 10^9). Every cell has an integer written in it. You can only move down or right, and you want to move from (1, 1) to (N, M). Before you begin moving, you can do the following operation any number of times:
 - Cyclically shift a row to the left by 1.

Let X be the number of times you perform the shift operation, and Y be the sum of the numbers on the tiles you step on. Your score is K*X + Y. Minimize your total score. 



Solution:
We can solve this with DP: let our dp state be dp[i][j] = min cost to move from (1, 1) to (i, j). With the shift moves, this becomes a bit more difficult; however, for our calculations it is equivalent to assume that we shift the row right before we enter it (since we are not allowed to move up or left, this is the same as shifting the rows ahead of time). Our transition from row i to row i+1 will be to move down immediately and move right however many squares we choose. This covers all possible paths we can take.

Given a location (i, j) and a target location (i+1, j+k-1), we can try all possible shift distances to see which one takes the least cost. Howevever, this is too slow (N^2 states, N target locations, N shift distances = O(N^4)). If we are able to somehow query for the best shift distance + interval of length k combination, that would be nice. This turns out to be possible with a smart use of segment trees. 

We first reorder some variables; first consider a single row i and an interval size k (which quantifies how far we move to the right in the next row). Suppose for now we only care about moving from (i, 0) to (i+1, k-1). It is straightforward to calculate the cost of all possible length-k intervals + their shift costs from (i, 0); we take a sliding window prefix sum of size k and add K for each unit we move the starting point past 0 (which represents the shift cost to use this interval from (i, 0). Then, say we want to move from (i, 1) to (i+1, k). It turns out that these computations are mostly the same; indeed, all intervals starting on or after (i+1, 1) cost K less to use from (i, 1), and the single interval starting before (i+1, 1) cost (M-1)*K more (since we now need to shift it all the way around). As we move further, the pattern becomes that when moving from (i, j) to (i, j+1), all costs are K less than before, except for the interval starting from (i+1, j) which costs M*(K-1) more.

Thus, for a given interval size we can precompute the cost to move k units from (i, 0) for all possible shifts, and do a -K range update and a +M*K point update to the whole range of costs to get the costs starting from (i, 1), and so on. Querying the minimum value in this range gives us the best possible cost to travel from (i, j) down one row and right k-1 squares. Both these operations can be done with a segment tree (I omitted the range update and just added a -j*K to cover for it). 

*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAXL 1e18

vector<ll> tree(800);

void build(vector<ll>& arr, int ind, int a, int b) {
    if(a == b) {
        tree[ind] = arr[a];
        return;
    }
    int m = (a+b)/2;
    build(arr, 2*ind, a, m);
    build(arr, 2*ind+1, m+1, b);
    tree[ind] = min(tree[2*ind], tree[2*ind+1]);
}

void update(ll val, int idx, int ind, int a, int b) {
    if(idx < a || idx > b) {
        return;
    }
    if(a == b && a == idx) {
        tree[ind] += val;
        return;
    }
    int m = (a+b)/2;
    update(val, idx, 2*ind, a, m);
    update(val, idx, 2*ind+1, m+1, b);
    tree[ind] = min(tree[2*ind], tree[2*ind+1]);
}

ll query(int left, int right, int ind, int a, int b) {
    if(right < a || left > b || a > b) {
        return MAXL;
    }
    if(left <= a && right >= b) {
        // cout << "query " << left << " " << right << ": " << a << " " << b << " " << tree[ind] << endl;
        return tree[ind];
    }
    int m = (a+b)/2;
    ll ret = min(query(left, right, 2*ind, a, m), query(left, right, 2*ind+1, m+1, b));
    // cout << "query " << left << " " << right << ": " << a << " " << b << " " << ret << endl;
    return ret;
}


void solve() {

    ll N, M, K;
    cin >> N >> M >> K;

    vector<vector<ll>> grid(N, vector<ll>(M));
    for(int i = 0; i<N; i++) {
        for(int j = 0; j<M; j++) {
            cin >> grid[i][j];
        }
    }

    vector<vector<ll>> dp(N+1, vector<ll>(M, 1e18)); // dp[i][j] = i-th row, index j
    dp[0][0] = 0;

    for(int i = 0; i<N; i++) {
        // transition from row i to row i+1
        for(int k = 1; k<=M; k++) { // interval size
            ll curr = 0;
            for(int j = 0; j<k; j++) {
                curr += grid[i][j];
            }
            vector<ll> arr(M);
            for(int j = 0; j<M; j++) {
                arr[j] = curr;
                curr -= grid[i][j];
                curr += grid[i][(j+k)%M] + K;
            }

            build(arr, 1, 0, M-1); // intervals of size k
            // with 0, +K, +2K, +3K, ...
            for(int j = 0; j+k<=M; j++) {
                if(dp[i][j] == MAXL) continue;
                dp[i+1][j+k-1] = min(dp[i+1][j+k-1], dp[i][j] + query(0, M-1, 1, 0, M-1) - j*K);
                update(M*K, j, 1, 0, M-1);
            }

        }
    }

    cout << dp[N][M-1] << endl;
//
//    for(int i = 0; i<=N; i++) {
//        for(int j = 0; j<N; j++) {
//            if(dp[i][j] == MAXL) continue;
//            cout << dp[i][j] << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;

}


int main() {

    /*
     * idea: dp for each row, build downwards?
     * dp[i][j] = dp[i-1][k] + best interval of size (j-k+1) for k <= j
     * for each row:
     *   for each interval size:
     *      put them all into a segment tree, along with shift differences from i = 0
     *      transition by adding m*k from some element, then subtracting k to all elements.
     *        eg: [0, 1] costs 21 from i = 0, but it costs 21+(m-1)*k from i = 1.
     *
     */

    int T;
    cin >> T;

    for(int i = 0; i<T; i++) solve();


}
