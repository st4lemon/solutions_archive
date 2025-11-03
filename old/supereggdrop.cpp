// LeetCode #887. Super Egg Drop
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int dp[101][10001] = {0};
/*
    int superEggDrop(int k, int n) {
        if(dp[k][n]>0) return dp[k][n];
        cout << k << " " << n << endl;
        if(k==1) return dp[k][n] = n;
        if(k>=log2(n+1)) return dp[k][n] = ceil(log2(n+1));
        int best = 2000000000;
        for(int i = 1; i<=n; i++) {
            int temp = max(superEggDrop(k, i-1), superEggDrop(k-1, n-i));
            if(temp <= best) best = temp;
            else break;
        }
        return dp[k][n] = best+1;
    }
*/
/*
 * state: dp[k][n] = best number of moves with K eggs and N floors remaining
 * dp[1][n] = n;
 * dp[k][n] = ceil(log2(n+1)) when 2^k > n+1;
 * otherwise:
 * dp[k][n] = max (i = 1 to N) {
 *     max(dp[k][i-1], dp[k-1][N-i])
 * }
 *
 * build DP bottom up
 * for each k, instead of iterating over all N for transitions, maintain a monotonic vector of pairs
 * <n-index, dp[k][n-index]> greatest n-index for each dp value
 * dp value is strictly increasing as n-index increasing, but there are dupes (this will speed things up)
 * from k=2 onwards, there are many duplicates, with the amount of duplicates increasing per row.
 * solution is O(KN^2) which is too slow (K=100, N = 10^4) but the optimization reduces the case space by a very large amount
 *      due to the presence of duplicates, allowing it to pass.
 *
 * faster way to do this would be binary searching for the point where broken egg & intact egg cases are closest together
 *      both cases are monotonic, but in opposite directions. imagine two lines on a graph, and the intersection is the best spot.
 * this gives O(KN log N) with no further optimizations
 * adding the additional optimization above with the monotonic vector will further improve the runtime, but this is unneccesary.
 */

    int superEggDrop(int k, int n) {
        for(int i = 0; i<=n; i++) {
            dp[1][i] = i;
        }
        for(int i = 2; i<=k; i++) {
            vector<pair<int, int>> v;
            // do j = 1 real quick, insert pair in
            dp[i][1] = max(dp[i][0], dp[i-1][0])+1;
            v.push_back({1, dp[i][1]});
            for(int j = 2; j<=n; j++) {
                int best = 2000000000;
                for(pair<int, int> a : v) {
                    int ind = a.first;
                    int val = a.second;
                    //cout << val << " ";
                    best = min(best, max(dp[i-1][j-ind-1], val));
                }
                //cout << endl;
                dp[i][j] = best + 1;
                while(v.size()!=0 && v.back().second >= dp[i][j]) v.pop_back();
                v.push_back({j, dp[i][j]});
            }
        }
        return dp[k][n];
    }

    void printDP(int k, int n) {
        for(int i = 1; i<=k; i++) {
            for(int j = 1; j<=n; j++) {
                cout << dp[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {

    cout << "start" << endl;
    Solution s;

    cout << s.superEggDrop(6, 10000) << endl;

    s.printDP(3, 14);

}