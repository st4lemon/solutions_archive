// LeetCode #2209. Minimum White Tiles After Covering With Carpets
#include <bits/stdc++.h>
#define MIN -2000000000

using namespace std;

class Solution {
public:
    int minimumWhiteTiles(string floor, int numCarpets, int carpetLen) {

        int prefix[floor.length()+1];
        prefix[0] = 0;
        for(int i = 0; i<floor.length(); i++) {
            prefix[i+1] = prefix[i] + (floor[i]=='1'? 1 : 0);
        }

        int dp[numCarpets+1][floor.length()+1];
        for(int i = 0; i<=numCarpets; i++) {
            for(int j = 0; j<=floor.length(); j++) {
                dp[i][j] = MIN;
            }
        }
        dp[0][0] = 0;

        for(int i = 0; i<numCarpets; i++) {
            int best = 0;
            for(int j = carpetLen; j<=floor.length(); j++) {
                // update best
                best = max(best, dp[i][j-carpetLen]);
                // update current based on best
                dp[i+1][j] = best + prefix[j]-prefix[j-carpetLen];
            }
            for(int j = floor.length()-carpetLen + 1; j<floor.length(); j++) {
                best = max(best, dp[i][j]);
                dp[i+1][floor.length()] = max(dp[i+1][floor.length()], best+prefix[floor.length()]-prefix[j]);
            }
            dp[i+1][floor.length()] = max(dp[i+1][floor.length()], dp[i][floor.length()]);
        }

        int ans = 0;
        for(int i = 0; i<=floor.length(); i++) {
            ans = max(ans, dp[numCarpets][i]);
        }

        return prefix[floor.length()] - ans;

    }
};